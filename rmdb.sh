#!/bin/bash

RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
RESET="\e[0m"

DB="output/bin/db.bin"

if test -e $DB; then

    printf "${YELLOW} [INFO] removing 'db.bin'... ${RESET} \n"
    rm -f $DB
    printf "${GREEN} [OK] 'db.bin' removed. ${RESET} \n"

else 

    printf "${RED} [ERROR] no such file of 'output/bin/db.bin' found. ${RESET} \n"

fi