die() {
    echo "First param: ${1}"
    if [[ ${2} ]]; then
        echo "Second param defined: ${2}"
    else
        echo "Second param not defined"
    fi
}


if [[ ! $# -eq 1 ]]; then
    die "error: one comand line arg is required"
    exit 1
fi
die "Message1"
die "Message2" 3
