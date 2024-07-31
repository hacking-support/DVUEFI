#!/bin/bash
set -euo pipefail

# 1: bugged-file
# 2: guid
# o. /tmp/{guid}.bin/file.ffs

thisdir=$(dirname -- "$0")


guid="${2}"
prefix="${3:-.}"

echo "extracting guid:" \'${guid}\' "from:" \'"${1}"\'
${thisdir}/uefiextract "${1}" "${guid}" -o "${prefix}/${guid}.bin" -m file
