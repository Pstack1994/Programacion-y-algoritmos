#include <stdio.h>

int main(){
    float z=1;
    unsigned int iz=*(unsigned int*)&z;

    fprintf(stderr, "diff inv: %x \n", iz);
    return 0;
}
