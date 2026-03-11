#include "funcs.h"

int main(int argc, char *argv[]){

    if (argc == 10){

        if (strcmp(argv[1], "INSERT") == 0 && strcmp(argv[2], "-name") == 0 && strcmp(argv[4], "-age") == 0 && strcmp(argv[6], "-rg") == 0 &&
            strcmp(argv[8], "-cpf") == 0){

                FILE *db = fopen("db.bin", "a+b");

                if (db == NULL){
                    perror("fopen");
                    return EXIT_FAILURE;
                }

                Registry *user = malloc(sizeof(Registry));

                if (user == NULL){
                    perror("malloc");
                    fclose(db);
                    return EXIT_FAILURE;
                }

                user->name = malloc(strlen(argv[3]) + 1);
                user->age = malloc(strlen(argv[5]) + 1);
                user->rg = malloc(strlen(argv[7]) + 1);
                user->cpf = malloc(strlen(argv[9]) + 1);

                if (user->name == NULL || user->age == NULL || user->rg == NULL || user->cpf == NULL){
                    FreeRegistry(user);
                    fclose(db);
                    return EXIT_FAILURE;
                }

                strcpy(user->name, argv[3]);
                strcpy(user->age, argv[5]);
                strcpy(user->rg, argv[7]);
                strcpy(user->cpf, argv[9]);

                user->id = GetNextId(db);

                fseek(db, 0, SEEK_END);

                if (ValidateNameFormat(user) == 1 && ValidateAgeFormat(user) == 1 && ValidateRgFormat(user) == 1 &&
                    ValidateCpfFormat(user) == 1){

                        AddRegistry(db, user);
                        FreeRegistry(user);
                        fclose(db);
                        printf("Registry Inserted Success. \n");
                        return EXIT_SUCCESS;
                    }

                else {
                    FreeRegistry(user);
                    fclose(db);
                    return EXIT_FAILURE;
                }

            }

            else {
                printf(RED "Error (Invalid Syntax).\n" RESET);
                return EXIT_FAILURE;
            }
    }

    else if (argc == 9){

        if (strcmp(argv[1], "UPDATE") == 0 && strcmp(argv[2], "-option") == 0 && strcmp(argv[4], "WHERE") == 0 &&
                strcmp(argv[5], "-id") == 0 && strcmp(argv[7], "-newcontent") == 0){

                unsigned int id = strtoul(argv[6], NULL, 10);

                UpDateRegistry("db.bin", id, argv[3], argv[8]);

                return EXIT_SUCCESS;

            }

        else {
                printf(RED "Error (Invalid Syntax).\n" RESET);
                return EXIT_FAILURE;
            }
    }

    else if (argc == 7){

        if (strcmp(argv[1], "SELECT") == 0 && strcmp(argv[2], "-option") == 0 && strcmp(argv[4], "WHERE") == 0 && strcmp(argv[5], "-id") == 0){

            FILE *db = fopen("db.bin", "rb");

            if (db == NULL){
                perror("fopen");
                return EXIT_FAILURE;
            }

            unsigned int id = strtoul(argv[6], NULL, 10);

            SelectRegistry(db, argv[3], id);

            fclose(db);

            return EXIT_SUCCESS;

        }

        else {
            printf(RED "Error (Invalid Syntax).\n" RESET);
            return EXIT_FAILURE;
        }
    }

    else if (argc == 5){

        if (strcmp(argv[1], "DELETE") == 0 && strcmp(argv[2], "WHERE") == 0 && strcmp(argv[3], "-id") == 0){

            unsigned int id = strtoul(argv[4], NULL, 10);

            DeleteRegistry("db.bin", id);

            return EXIT_SUCCESS;
        }

        else {
            printf(RED "Error (Invalid Syntax).\n" RESET);
            return EXIT_FAILURE;
        }
    }

    else if (argc == 3){

        if (strcmp(argv[1], "GET") == 0 && strcmp(argv[2], "-actives") == 0){

            FILE *db = fopen("db.bin", "rb");

            if (db == NULL){
                perror("fopen");
                return EXIT_FAILURE;
            }

            GetRecordNumber(db);
            fclose(db);
            return EXIT_SUCCESS;
        }

        else {
            printf(RED "Error (Invalid Syntax).\n" RESET);
            return EXIT_FAILURE;
        }
    }

    else {

        printf(RED "Error (Unknown Command).\n" RESET);
        return EXIT_FAILURE;
    }

    return 0;
}