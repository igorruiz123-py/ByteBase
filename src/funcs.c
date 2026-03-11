#include "funcs.h"

int ValidateNameFormat(Registry *temp){

    for (int i = 0; temp->name[i] != '\0'; i++){
        
        if (temp->name[i] <= '9' && temp->name[i] >= '0'){
            printf(RED "Error (Bad Name Format).\n" RESET);
            return 0;
        }
    }
    
    return 1;
}

int ValidateAgeFormat(Registry *temp){

    // 19 (EXEMPLO)
    // 18 - 80
    // len -> 2

    for (int i = 0; temp->age[i] != '\0'; i++){

        if (temp->age[i] > '9' || temp->age[i] < '0'){
            printf(RED "Error (Bad Age Format).\n" RESET);
            return 0;
        }
    }

    int num = strtol(temp->age, NULL, 10);

    if (num <= 18 || num >= 80){
        printf(RED "Error (Bad Age format).\n" RESET);
        return 0;
    }

    return 1;

}

int ValidateRgFormat(Registry *temp){

    // 53613957-4 (EXEMPLO)
    // len -> 10
    //    5      3      6       1      3       9       5      7       -         4
    //  rg[0]  rg[1]   rg[2]  rg[3]  rg[4]   rg[5]   rg[6]  rg[7]    rg[8]    rg[9]

    if (strlen(temp->rg) != 10 || temp->rg[8] != '-'){
        printf(RED "Error (Bad RG Format). \n" RESET);
            return 0;
        }

    char buff1[64];
    char buff2[64];
    int a = 0;
    int b = 0;

    for (int i = 0; temp->rg[i] != '\0'; i++){

        if (temp->rg[i] == '-'){
            buff1[a++] = temp->rg[i];
        }
        else {
            buff2[b++] = temp->rg[i];
        }

    }

    buff2[b] = '\0';

    for (int j = 0; buff2[j] != '\0'; j++){
        
        if (buff2[j] > '9' || buff2[j] < '0'){
            printf(RED "Error (Bad RG Format). \n" RESET);
            return 0;
        }
    }

    return 1;

}

int ValidateCpfFormat(Registry *temp){

    // 448.339.220-85 (EXEMPLO)
    // len -> 14
    //    4      4         8       .      3        3        9      .          2         2       0         -         8        5
    //  cpf[0]  cpf[1]   cpf[2] cpf[3]  cpf[4]   cpf[5]   cpf[6]  cpf[7]    cpf[8]    cpf[9]  cpf[10]   cpf[11]   cpf[12]  cpf[13]

    if (strlen(temp->cpf) != 14){
        printf(RED "Error (Bad CPF Format).\n" RESET);
            return 0;
        }

    if (temp->cpf[3] != '.' || temp->cpf[7] != '.' || temp->cpf[11] != '-'){
        printf(RED "Error (Bad CPF Format).\n" RESET);
            return 0;
        }

    char buff1[64];
    char buff2[64];

    int a = 0;
    int b = 0;

    for (int i = 0; temp->cpf[i] != '\0'; i++){

        if (temp->cpf[i] == '.' || temp->cpf[i] == '-'){
            buff1[a++] = temp->cpf[i];
        }

        else {
            buff2[b++] = temp->cpf[i];
        }
    }

    buff2[b] = '\0';

    for (int j = 0; buff2[j] != '\0'; j++){

        if (buff2[j] < '0' || buff2[j] > '9'){
            printf(RED "Error (Bad CPF Format).\n" RESET);
            return 0;
        }
    }

    return 1;

}



void FreeRegistry(Registry *temp){

    free(temp->name);
    free(temp->age);
    free(temp->rg);
    free(temp->cpf);
    free(temp);
}

void AddRegistry(FILE *file, Registry *user){

    // id tem tamanho fixo, então se grava direto no arquivo
    unsigned int nameLen = strlen(user->name) + 1;
    unsigned int ageLen = strlen(user->age) + 1;
    unsigned int rgLen = strlen(user->rg) + 1;
    unsigned int cpfLen = strlen(user->cpf) + 1;

    // gravando id fixo
    fwrite(&user->id, sizeof(unsigned int), 1, file);

    // gravando tamanho dos dados dinâmicos primeiro
    fwrite(&nameLen, sizeof(unsigned int), 1, file);
    fwrite(&ageLen, sizeof(unsigned int), 1, file);
    fwrite(&rgLen, sizeof(unsigned int), 1, file);
    fwrite(&cpfLen, sizeof(unsigned int), 1, file);

    // gravando os dados propriamente dito
    fwrite(user->name, sizeof(char), nameLen, file);
    fwrite(user->age, sizeof(char), ageLen, file);
    fwrite(user->rg, sizeof(char), rgLen, file);
    fwrite(user->cpf, sizeof(char), cpfLen, file);
}


Registry *ReadBin(FILE *file){

    unsigned int id;
    unsigned int nameLen;
    unsigned int ageLen;
    unsigned int rgLen;
    unsigned int cpfLen;

    // lendo id fixo
    if (fread(&id, sizeof(unsigned int), 1, file) != 1){
        return NULL;
    }

    // lendo tamanho dos dados
    if (fread(&nameLen, sizeof(unsigned int), 1 , file) != 1){
        return NULL;
    }

    if (fread(&ageLen, sizeof(unsigned int), 1 , file) != 1){
        return NULL;
    }

    if (fread(&rgLen, sizeof(unsigned int), 1 , file) != 1){
        return NULL;
    }

    if (fread(&cpfLen, sizeof(unsigned int), 1 , file) != 1){
        return NULL;
    }

    // alocando memória para os dados vindo da struct
    Registry *temp = malloc(sizeof(Registry));

    if (temp == NULL){
        perror("malloc");
        return NULL;
    }

    temp->id = id;
    temp->name = malloc(nameLen);
    temp->age = malloc(ageLen);
    temp->rg = malloc(rgLen);
    temp->cpf = malloc(cpfLen);

    // lendo os dados das structs 
    if (temp->name == NULL || temp->age == NULL || temp->rg == NULL || temp->cpf == NULL){
        perror("malloc");
        FreeRegistry(temp);
        return NULL;
    }

    if (fread(temp->name, sizeof(char), nameLen, file) != nameLen){
        FreeRegistry(temp);
        return NULL;
    }

    if (fread(temp->age, sizeof(char), ageLen, file) != ageLen){
        FreeRegistry(temp);
        return NULL;
    }

    if (fread(temp->rg, sizeof(char), rgLen, file) != rgLen){
        FreeRegistry(temp);
        return NULL;
    }

    if (fread(temp->cpf, sizeof(char), cpfLen, file) != cpfLen){
        FreeRegistry(temp);
        return NULL;
    }

    return temp;

}

unsigned int GetNextId(FILE *file){

    rewind(file); 

    Registry *temp;
    unsigned int lastId = 0;

    while ((temp = ReadBin(file)) != NULL) {
        lastId = temp->id;
        FreeRegistry(temp);
    }

    return lastId + 1;
}

Registry *FindById(FILE *file, unsigned int targetId){

    rewind(file);

    Registry *temp;

    while ((temp = ReadBin(file)) != NULL){

        if (temp->id == targetId){
            return temp;
        }

        FreeRegistry(temp);
    }

    return NULL;
}


void SelectRegistry(FILE *file, char *option, unsigned int id){

    for (int i = 0; option[i] != '\0'; i++){

        // se encontrar digitos na string retorna 0
        if (option[i] >= '0' && option[i] <= '9'){
            printf(RED "Error (Invalid Options For SELECT).\n" RESET);
            return;
        }
    }

    Registry *user;

    // bytebase SELECT "all" WHERE id = 0
    // irá selecionar todos os dados de todos os registros
    if (strcmp(option, "all") == 0 && id == 0){

        while ((user = ReadBin(file)) != NULL){

            printf("ID: %d \n", user->id);
            printf("Name: %s \n", user->name);
            printf("Age: %s \n", user->age);
            printf("RG: %s \n", user->rg);
            printf("CPF: %s \n", user->cpf);
            printf("-------------------------------\n");

            FreeRegistry(user);
        }

        return;
    }    

    // bytebase SELECT "all" WHERE id = 1
    // irá selecionar todos os dados do usuário com id = 1
    if (strcmp(option, "all") == 0){

        user = FindById(file, id);

        if (user == NULL){
            printf(RED "Error (ID Not Found For SELECT).\n" RESET);
            return;
        }

        printf("ID: %u\n", user->id);
        printf("Name: %s\n", user->name);
        printf("Age: %s\n", user->age);
        printf("RG: %s\n", user->rg);
        printf("CPF: %s\n", user->cpf);

        FreeRegistry(user);
        return;
    }

    if (strlen(option) <= 4){

        // bytebase SELECT "option (apenas 1 opção)" WHERE id = 0
        // irá selecionar a opção selecionada de todos os usuários
        if (strcmp(option, "name") == 0 && id == 0){
            
            while ((user = ReadBin(file)) != NULL){
                printf("Name: %s \n", user->name);
                printf("-------------------------------\n");
                FreeRegistry(user);
            }

            return;
        }

        else if (strcmp(option, "age") == 0 && id == 0){
            
            while ((user = ReadBin(file)) != NULL){
                printf("Age: %s \n", user->age);
                printf("-------------------------------\n");
                FreeRegistry(user);
            }
            
            return;
        }

        else if (strcmp(option, "rg") == 0 && id == 0){
            
            while ((user = ReadBin(file)) != NULL){
                printf("RG: %s \n", user->rg);
                printf("-------------------------------\n");
                FreeRegistry(user);
            }
            
            return;
        }

        else if (strcmp(option, "cpf") == 0 && id == 0){
            
            while ((user = ReadBin(file)) != NULL){
                printf("CPF: %s \n", user->cpf);
                printf("-------------------------------\n");
                FreeRegistry(user);
            }
            
            return;
        }

        // bytebase SELECT "name" WHERE id = 1
        // irá selecionar apenas o dado "name" do usuário com id = 1

        user = FindById(file, id);

        if (user == NULL) {
            printf(RED "Error (ID Not Found For SELECT).\n" RESET);
            return;
        }

        if (strcmp(option, "name") == 0){
            printf("Name: %s \n", user->name);
        }

        else if (strcmp(option, "age") == 0){
            printf("Age: %s \n", user->age);
        }

        else if (strcmp(option, "rg") == 0){
            printf("RG: %s \n", user->rg);
        }

        else if (strcmp(option, "cpf") == 0){
            printf("CPF: %s \n", user->cpf);
        }

        else{
            printf(RED "Error (Invalid Options For SELECT).\n" RESET);
            return;
        }

        FreeRegistry(user);

        }


    else if (strlen(option) > 4){

        // bytebase SELECT <options EX: (name,age...)> WHERE id = 0

        if (id == 0){

            bool has_name = false;
            bool has_age = false;
            bool has_rg = false;
            bool has_cpf = false;

            char buffer[256];
            strcpy(buffer, option);

            char *token = strtok(buffer, ",");

            while (token != NULL){

                if (strcmp(token, "name") == 0){
                    if (has_name == true){
                        printf(RED "Error (Multiple 'name' Options). \n" RESET);
                        return;
                    }

                    has_name = true;

                }

                else if (strcmp(token, "age") == 0){
                    if (has_age == true){
                        printf(RED "Error (Multiple 'age' Options). \n" RESET);
                        return;
                    }

                    has_age = true;
                }

                else if (strcmp(token, "rg") == 0){
                    if (has_rg == true){
                        printf(RED "Error (Multiple'rg' Options). \n" RESET);
                        return;
                    }

                    has_rg = true;
                }

                else if (strcmp(token, "cpf") == 0){
                    if (has_cpf == true){
                        printf(RED "Error (Multiple 'cpf' Options). \n" RESET);
                        return;
                    }

                    has_cpf = true;
                }

                else {
                    printf(RED "Error (Invalid Options For SELECT).\n" RESET);
                    return;
                }

                token = strtok(NULL, ",");
            }

            rewind(file);

            while ((user = ReadBin(file)) != NULL){

                if (has_name) printf("Name: %s\n", user->name);
                if (has_age)  printf("Age: %s\n", user->age);
                if (has_rg)   printf("RG: %s\n", user->rg);
                if (has_cpf)  printf("CPF: %s\n", user->cpf);

                printf("-------------------------------\n");

                FreeRegistry(user);
            }

            return;

        }

    // bytebase SELECT <options EX: (name,age...)> WHERE id = "index" (DIFERENTE DE 0)
    // poderá introduzir varias opções no comando de consulta

        user = FindById(file, id);

        if (user == NULL) {
            printf(RED "Error (ID Not Found For SELECT).\n" RESET);
            return;
        }

        bool has_name = false;
        bool has_age = false;
        bool has_rg = false;
        bool has_cpf = false;

        char buffer[256];
        strcpy(buffer, option);

        char *token = strtok(buffer, ",");

        while (token != NULL){

            if (strcmp(token, "name") == 0){
                if (has_name == true){
                    printf(RED "Error (Multiple 'name' Options). \n" RESET);
                    return;
                }

                has_name = true;

            }

            else if (strcmp(token, "age") == 0){
                if (has_age == true){
                    printf(RED "Error (Multiple 'age' Options). \n" RESET);
                    return;
                }

                has_age = true;
            }

            else if (strcmp(token, "rg") == 0){
                if (has_rg == true){
                    printf(RED "Error (Multiple'rg' Options). \n" RESET);
                    return;
                }

                has_rg = true;
            }

            else if (strcmp(token, "cpf") == 0){
                if (has_cpf == true){
                    printf(RED "Error (Multiple 'cpf' Options). \n" RESET);
                    return;
                }

                has_cpf = true;
            }

            else {
                printf(RED "Error (Invalid Options For SELECT).\n" RESET);
                return;
            }

            token = strtok(NULL, ",");
        }

        if (has_name) printf("Name: %s\n", user->name);
        if (has_age)  printf("Age: %s\n", user->age);
        if (has_rg)   printf("RG: %s\n", user->rg);
        if (has_cpf)  printf("CPF: %s\n", user->cpf);

        FreeRegistry(user);

    }

}

void DeleteRegistry(const char *filename, unsigned int targetID){

    FILE *db = fopen(filename, "rb");
    if (db == NULL){
        perror("fopen");
        return;
    }

    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL){
        perror("fopen");
        fclose(db);
        return;
    }

    Registry *user;
    int found = 0;

    while ((user = ReadBin(db)) != NULL){

        if (user->id == targetID){
            found = 1;  // marca que encontrou o ID
        }
        else{
            AddRegistry(temp, user);  // copia para o novo arquivo
        }

        FreeRegistry(user);
    }

    fclose(db);
    fclose(temp);

    if (!found){
        printf(RED "Error (ID Not Found For DELETE).\n" RESET);
        remove("temp.bin");
        return;
    }

    remove(filename);
    rename("temp.bin", filename);

    printf("Registry Deleted Success. \n");

}

void GetRecordNumber(FILE *file){

    Registry *user;

    int counter = 0;
    bool found = true;

    while ((user = ReadBin(file)) != NULL){
        
        if (user->id){
            counter++;
        }
        
        else {
            found = false;            
        }

        FreeRegistry(user);
    }

    if (found = true){
        printf("Users Active: %d \n", counter);
    }

    else {
        printf("There are no Users Active. \n");    
    }
}

void UpDateRegistry(char *filename, unsigned int id, char *option, char *newcontent){

    if (strlen(option) > 4){
        printf(RED "Error (Invalid Option For UPDATE).\n" RESET);
        return;
    }

    FILE *db = fopen(filename, "rb");
    if (db == NULL){
        perror("fopen");
        return;
    }

    FILE *tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL){
        perror("fopen");
        fclose(db);
        return;
    }

    Registry *user;
    int found = 0;

    bool is_name = false;
    bool is_age = false;
    bool is_rg = false;
    bool is_cpf = false;

    if (strcmp(option, "name") == 0){
        is_name = true;
    }

    else if (strcmp(option, "age") == 0){
        is_age = true;
    }

    else if (strcmp(option, "rg") == 0){
        is_rg = true;
    }

    else if (strcmp(option, "cpf") == 0){
        is_cpf = true;
    }

    else {
        printf(RED "Error (Invalid Option For UPDATE).\n" RESET);
        fclose(db);
        fclose(tempFile);
        remove("temp.bin");
        return;
    }

    while ((user = ReadBin(db)) != NULL){

        if (user->id == id){
            found = 1;

            if (is_name){

                Registry temp = {0};
                temp.name = newcontent;

                if (!ValidateNameFormat(&temp)){
                    FreeRegistry(user);
                    fclose(db);
                    fclose(tempFile);
                    remove("temp.bin");
                    return;
                }

                free(user->name);
                user->name = malloc(strlen(newcontent) + 1);

                if (user->name == NULL){
                    perror("malloc");
                    FreeRegistry(user);
                    fclose(db);
                    fclose(tempFile);
                    remove("temp.bin");
                    return;
                }

                strcpy(user->name, newcontent);
            }

            else if (is_age){

                Registry temp = {0};
                temp.age = newcontent;

                if (!ValidateAgeFormat(&temp)){
                    FreeRegistry(user);
                    fclose(db);
                    fclose(tempFile);
                    remove("temp.bin");
                    return;
                }

                free(user->age);
                user->age = malloc(strlen(newcontent) + 1);

                if (user->age == NULL){
                    perror("malloc");
                    FreeRegistry(user);
                    fclose(db);
                    fclose(tempFile);
                    remove("temp.bin");
                    return;
                }

                strcpy(user->age, newcontent);
            }

            else if (is_rg){

                Registry temp = {0};
                temp.rg = newcontent;

                if (!ValidateRgFormat(&temp)){
                    FreeRegistry(user);
                    fclose(db);
                    fclose(tempFile);
                    remove("temp.bin");
                    return;
                }

                free(user->rg);
                user->rg = malloc(strlen(newcontent) + 1);

                if (user->rg == NULL){
                    perror("malloc");
                    FreeRegistry(user);
                    fclose(db);
                    fclose(tempFile);
                    remove("temp.bin");
                    return;
                }

                strcpy(user->rg, newcontent);
            }

            else if (is_cpf){

                Registry temp = {0};
                temp.cpf = newcontent;

                if (!ValidateCpfFormat(&temp)){
                    FreeRegistry(user);
                    fclose(db);
                    fclose(tempFile);
                    remove("temp.bin");
                    return;
                }

                free(user->cpf);
                user->cpf = malloc(strlen(newcontent) + 1);

                if (user->cpf == NULL){
                    perror("malloc");
                    FreeRegistry(user);
                    fclose(db);
                    fclose(tempFile);
                    remove("temp.bin");
                    return;
                }

                strcpy(user->cpf, newcontent);
            }
        }

        AddRegistry(tempFile, user);
        FreeRegistry(user);

    }

    fclose(db);
    fclose(tempFile);

    if (!found){
        printf(RED "Error (ID Not Found For UPDATE).\n" RESET);
        remove("temp.bin");
        return;
    }

    remove(filename);
    rename("temp.bin", filename);

    printf("Registry Updated Success.\n");


}