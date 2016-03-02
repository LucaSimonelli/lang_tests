die() {
    echo "First param: ${1}"
    if [[ ${2} ]]; then
        echo "Second param defined: ${2}"
    else
        echo "Second param not defined"
    fi
}

die "Message1"
die "Message2" 3
