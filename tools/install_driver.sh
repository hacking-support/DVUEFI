#!/bin/bash

set -euo pipefail

thisdir=$(dirname -- "$0")
prefix=$(mktemp -d)

build="${1}"
driver_guid="${2}"
base="${3}"
output_rom="${4}"

${thisdir}/UEFIToolNew/extract_file.sh "${build}" "${driver_guid}" "${prefix}"
${thisdir}/UEFITool28/insert_dxe.sh "${base}" "${prefix}/${driver_guid}.bin/file.ffs" "${output_rom}"
