#!/bin/bash

RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
RESET="\e[0m"

DIR="output/bin"

FILES=("main.o" "funcs.o" "bytebase")

found=0

for file in "${FILES[@]}"; do
    path="$DIR/$file"

    if test -f "$path"; then
        if [ "$found" -eq 0 ]; then
            printf "${YELLOW} [INFO] removing files... ${RESET} \n"
            found=1
        fi

        printf "${YELLOW} [INFO] removing '$file'... ${RESET} \n"
        rm -f "$path"
    fi
done

if [ "$found" -eq 1 ]; then
    printf "${GREEN} [OK] files removed. ${RESET} \n"
else
    printf "${RED} [ERROR] no such file found. ${RED} \n"
fi