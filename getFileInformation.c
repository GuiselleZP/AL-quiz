#include <stdio.h>

int main(int argc, char** argv){
    printf("Excecutable name: %s\n", argv[0]);

    printf("This is %s() from %s, line %d\n", __FUNCTION__,__FILE__, __LINE__);
    return 0;
}
