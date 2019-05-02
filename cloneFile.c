#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void error(const char *s);
void functionDirectory(char *archive); 
int compareFormats(char *tempFile, char *formatFile);
int getFileNumber(char *tempFile);
void copyFile(char *nameFile, char *format, int number);

void error(const char *s){
    perror(s);
    exit(EXIT_FAILURE);
}

int compareFormats(char *tempFile, char *formatFile){
    int lengthTempFile  = 0,
        lengthFormat    = 0,
        auxiliar        = 0,
        count           = 0,
        j               = 0,
        i               = 0;

    lengthTempFile = strlen(tempFile);
    lengthFormat = strlen(formatFile);
    auxiliar = lengthTempFile - lengthFormat;

    if(auxiliar > 0){
        for(i = auxiliar; i < lengthTempFile; i++, j++){
            if(tempFile[i] == formatFile[j]){
                count ++;
            }else{
                break;
            }
        }

        if(count == lengthFormat){
            return 0;
        }
    }
    return 1;
}

int getFileNumber(char *tempFile){
    int number  = 0;

    while(tempFile = strpbrk(tempFile, "0123456789")){
        number = number * 10 + *tempFile++ - '0';       
    }

    return number + 1;
}

void copyFile(char *nameFile, char *format, int number){
    FILE *fl,
         *auxfl;
    char *tempNumber,
         *tempName,
         *newName,
         character;

    tempNumber = malloc(sizeof(number));
    tempName = malloc(sizeof(nameFile) + sizeof(format));
    newName = malloc(sizeof(nameFile) + sizeof(tempNumber) + sizeof(format));
    sprintf(tempNumber, "%d", number); 

    strcat(tempName, nameFile);
    strcat(tempName, format);

    strcat(newName, nameFile);
    strcat(newName, tempNumber);
    strcat(newName, format);

    fl = fopen(tempName, "r");
    if(fl == NULL){
        error("Error fopen 1 in function copyFile");
    }
    
    auxfl = fopen(newName, "w+");
    if(auxfl == NULL){
        error("Error fopen 2 in function copyFile");
    }

    while((character = fgetc(fl)) != EOF){
        fputc(character, auxfl);
    }

    fclose(auxfl);
    fclose(fl);
}

int main(){
    DIR *dir; 
    struct dirent *ent;
    char *formatFile,
         *nameFile,
         *tempFile,
         *file,
         *auxfl;
    int lengthNameFile  = 0,
        number          = 0,
        aux             = 0,
        i               = 0;

    file = strdup( __FILE__);
    
    while((auxfl = strsep(&file, ".")) != NULL){
        if(i == 0){
            nameFile = auxfl;
        }else{
            formatFile = malloc(sizeof(auxfl) + 1);
            strcat(formatFile, ".");
            strcat(formatFile, auxfl);
        }
        i++;
    }

    lengthNameFile = strlen(nameFile);

    dir = opendir(".");
    if(dir == NULL){
        error("Error opendir in function main");
    }

    while((ent = readdir(dir)) != NULL){
        if(compareFormats(ent -> d_name, formatFile) == 0){
            tempFile = ent -> d_name;
            if((strncmp(tempFile, nameFile, lengthNameFile)) == 0){
                number = getFileNumber(tempFile); 
                if(number > aux){
                    aux = number;
                }
            } 
        }
    }

    if(aux > 0){
        copyFile(nameFile, formatFile, number);
    }

    closedir(dir);
    free(file);
    free(nameFile);
    free(formatFile);
    return 0;
}
