#!/bin/bash

set -euo pipefail

thisdir=$(dirname -- "$0")

build="${1}"
driver_guid="${2}"
base="${3}"
output_rom="${4}"

extracted=$(mktemp -d)
extract_file="${extracted}/${driver_guid}.ffs"

uefiextract=${thisdir}/UEFITool/uefiextract
uefiinsert=${thisdir}/UEFITool28/insert_dxe.sh

if ! test -f ${uefiextract}; then
    echo "UEFIExtract not found: make sure to build it first"
    exit 1
fi

if ! test -f ${uefiinsert}; then
    echo "UEFIInsert not found: make sure to build it first"
    exit 1
fi

${uefiextract} "${build}" "${driver_guid}" -o ${extract_file} -m file
${uefiinsert} "${base}" "${extract_file}/file.ffs" "${output_rom}"
