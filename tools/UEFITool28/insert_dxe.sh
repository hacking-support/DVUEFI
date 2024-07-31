#!/bin/bash
set -euo pipefail

thisdir=$(dirname -- "$0")

# 1. VMWare file
# 2. /tmp/{guid}.bin/file.ffs
# o output.ROM

fat="961578FE-B6B7-44C3-AF35-6BC705CD2B1F"
dxe_file_type=7

echo "inserting into:" \'${1}\'
${thisdir}/UEFIInsert/UEFIInsert "${1}" "${fat}" "${dxe_file_type}" "${2}" -o "${3}"
