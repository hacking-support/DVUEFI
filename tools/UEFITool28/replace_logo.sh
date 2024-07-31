#!/bin/bash

set -euo pipefail

logo="7BB28B99-61BB-11D5-9A5D-0090273FC14D"


UEFIReplace/UEFIReplace "${1}" "${logo}" 19 "${2}" -o "${3}"
