/* uefireplace.cpp

Copyright (c) 2017, mxxxc. All rights reserved.
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

*/

#include "uefireplace.h"
#include <iostream>

UEFIInsert::UEFIInsert(QObject *parent) :
    QObject(parent)
{
    ffsEngine = new FfsEngine(this);
    model = ffsEngine->treeModel();
}

UEFIInsert::~UEFIInsert()
{
    delete ffsEngine;
}

UINT8 UEFIInsert::insert(const QString & inPath, const QByteArray & guid, const UINT8 sectionType, const QString & contentPath, const QString & outPath, bool insert_after)
{
    QFileInfo fileInfo = QFileInfo(inPath);
    if (!fileInfo.exists())
        return ERR_FILE_OPEN;

    fileInfo = QFileInfo(contentPath);
    if (!fileInfo.exists())
        return ERR_FILE_OPEN;

    QFile inputFile;
    inputFile.setFileName(inPath);

    if (!inputFile.open(QFile::ReadOnly))
        return ERR_FILE_READ;

    QByteArray buffer = inputFile.readAll();
    inputFile.close();

    UINT8 result = ffsEngine->parseImageFile(buffer);
    if (result)
        return result;

    QFile contentFile;
    contentFile.setFileName(contentPath);

    if (!contentFile.open(QFile::ReadOnly))
        return ERR_FILE_READ;

    QByteArray contents = contentFile.readAll();
    contentFile.close();

    result = insertInFile(model->index(0, 0), guid, sectionType, contents,
        insert_after ? CREATE_MODE_AFTER : CREATE_MODE_BEFORE);
    if (result)
        return result;

    QByteArray reconstructed;
    result = ffsEngine->reconstructImageFile(reconstructed);
    if (result)
        return result;
    if (reconstructed == buffer)
        return ERR_NOTHING_TO_PATCH;

    QFile outputFile;
    outputFile.setFileName(outPath);
    if (!outputFile.open(QFile::WriteOnly))
        return ERR_FILE_WRITE;

    outputFile.resize(0);
    outputFile.write(reconstructed);
    outputFile.close();

    return ERR_SUCCESS;
}

UINT8 UEFIInsert::insertInFile(const QModelIndex & index, const QByteArray & guid, const UINT8 sectionType, const QByteArray & newData, const UINT8 mode)
{
    if (!model || !index.isValid())
        return ERR_INVALID_PARAMETER;

    bool patched = false;
    QModelIndex fileIndex = index;
    QByteArray fileGuid = model->header(fileIndex).left(sizeof(EFI_GUID));

    bool guidMatch = fileGuid == guid;

    if (guidMatch && model->action(index) != Actions::Insert) {
        UINT8 result = ffsEngine->insert(index, newData, mode);
        std::cout << "Target GUID found: " << qPrintable(guid.toHex()) << std::endl;
        if (mode == CREATE_MODE_AFTER) {
            std::cout << "Inserting after..." << std::endl;
        } else if (mode == CREATE_MODE_BEFORE){
            std::cout << "Inserting before..." << std::endl;
        }
        if (result != ERR_NOTHING_TO_PATCH)
            return result;
        patched = result == ERR_SUCCESS;
    }

    // Recurse to children
    if (model->rowCount(index) > 0) {
        for (int i = 0; i < model->rowCount(index); i++) {
            UINT8 result = insertInFile(index.child(i, 0), guid, sectionType, newData, mode);
            // We patched something!  Returns `ERR_SUCCESS` if all other children didn't error out
            if (result == ERR_SUCCESS) {
                patched = true;
                return result;
            } else if (result != ERR_NOTHING_TO_PATCH) { // error
                return result;
            }
        }
    }

    // Success. Did we patch anything?
    return patched ? ERR_SUCCESS : ERR_NOTHING_TO_PATCH;
}
