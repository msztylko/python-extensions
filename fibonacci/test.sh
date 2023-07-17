#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'
trap "kill 0" SIGINT


if [[ "$#" < 1 ]]; then
    echo "Usage: ./test.sh cmd" >&2
    exit 1
fi

diff <(cat cases_35.txt | eval "(time $@)") cases_35.txt
