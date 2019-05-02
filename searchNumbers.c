#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getNumbers(char *array);


int getNumbers(char *array){
    int numbers = 0;
    while(array = strpbrk(array, "0123456789")){
        numbers = numbers * 10 + *array++ - '0';
    }
    return numbers;
}

int main()
{
    char *array;
    array = malloc(sizeof(char));

    printf("Insert the alphanumeric array:\n");
    scanf("%s", array);
    printf("Numbers: %d\n", getNumbers(array));

    return 0;
}


