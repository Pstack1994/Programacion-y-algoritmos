#include <stdio.h>
#include <string.h>
int main (int argc, char *argv[]){
    if(argv < 2){
        return -1;
    }

    int i= atoi(argv[1]);
    unsigned char s=i;

    if(s>=90){
        printf("no pasaras!\n");
        return -1;
    }
char src_string[]="hola hola hola hola hola hola hola hola hola hola hola hola hola hola";
char dest_string[90];
memcpy(dest_string,src_string,i);
printf("%s\n",dest_string);
return 0;
}
