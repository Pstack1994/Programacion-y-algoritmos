#include <stdio.h>

int main(){
    double z=2564;
    unsigned long int iz=*(unsigned long int*)&z;
    unsigned long int corrimiento;

    for(int i= sizeof(double)*sizeof(void*)-1;i>=0;i--){

        corrimiento=iz>>i;
        corrimiento=corrimiento & 1;
        corrimiento ==1 ? printf("%u ", 1) : printf("%u ", 0);
    }
    printf("\n");
    fprintf(stderr, "diff inv: %x \n", iz);
    return 0;

}
