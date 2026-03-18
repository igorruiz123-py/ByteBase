#!/bin/bash

DIR="output/bin"

RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
RESET="\e[0m"

if test -d "$DIR"; then

    printf "${RED} [ERROR] the directory 'output/bin' already exists. ${RESET} \n"

else

    printf "${YELLOW} [INFO] setting environment up... ${RESET} \n"
    mkdir -p $DIR
    printf "${GREEN} [OK] environment ready. ${RESET} \n"

fi
