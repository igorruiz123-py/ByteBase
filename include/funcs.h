#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define RED "\033[31m"
#define RESET "\033[0m"

typedef struct{
    
    unsigned int id;
    char *name;
    char *age;
    char *rg;
    char *cpf;

} Registry;

int ValidateNameFormat(Registry *temp);

int ValidateAgeFormat(Registry *temp);

int ValidateRgFormat(Registry *temp);

int ValidateCpfFormat(Registry *temp);

void FreeRegistry(Registry *temp);

void AddRegistry(FILE *file, Registry *user);

Registry *ReadBin(FILE *file);

unsigned int GetNextId(FILE *file);

Registry *FindById(FILE *file, unsigned int targetId);

void SelectRegistry(FILE *file, char *option, unsigned int id);

void DeleteRegistry(const char *filename, unsigned int targetID);

void GetRecordNumber(FILE *file);

void UpDateRegistry(char *filename, unsigned int id, char *option, char *newcontent);

#endif