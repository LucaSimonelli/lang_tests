#!/bin/bash
set -eou pipefail

if [[ ! -z ${1+x} && -n $1 ]] ; then
    echo "set ${LUCA}"
else
    echo "unset";
fi
