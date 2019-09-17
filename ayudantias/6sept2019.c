#include <stdio.h>

int f(int(*g)(int, int), int n, int *arr);
int g(int a, int b);

int main(){

    //problema 1
    int numero=1<<31;
    printf("%d", numero);
    printf("\nSuma= %d", numero+numero);

    //problema 2
    int b=~b;
    printf("\nb= %d", b);
    return 0;
}

int f(int(*g)(int, int), int n , int *arr){
    int ans=arr[0];

    for(int i=1; i<n;i++){
       ans= g(ans,arr[i]);
    }

    return ans;
}

int g(int a, int b){
    return (a<b)? a:b;
}
