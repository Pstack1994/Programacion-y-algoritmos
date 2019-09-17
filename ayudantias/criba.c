#include <stdio.h>


#define N 100000


typedef long long ll;


int main() {

        int crib[N];
        int cantidad=0;

        crib[0] = crib[1] = 0;

        for(int i=2; i<N; i++)
                crib[i] = 1;


        for(int i=2; i<N; i++)
                if(crib[i])
                        for(ll j=(ll)i*i; j<N; j+=i)
                                crib[j] = 0;

        printf("Primos entre 1 y 100:\n");

        for(int i=0; i<100; i++)
                if(crib[i])
                        printf("%d\n", i);

        for(int i=0; i<N;i++){
                if(crib[i]){
                        cantidad++;
                }
        }
        printf("cantidad: %d", cantidad);
        int primos[cantidad];

        for(int i=0, j=0; i<N;i++){
                if(crib[i]){
                        primos[j++]=i;
                }
                printf("%d", primos[i]);
        }



        return 0;

}
