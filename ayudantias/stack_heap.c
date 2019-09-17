#include <stdio.h>
#include <stdlib.h>


int main() {

	printf("solo variables\n");

	int a, b, c;

	printf("&a: %p\n&b: %p\n&c: %p\n", &a, &b, &c);
	printf("%ld\n", &b-&a);
	printf("%ld\n", &c-&b);

	printf("\nsolo variables en un loop\n");

	for(int i=0; i<5; i++) {

		int d, e;
		printf("&d: %p\n&e: %p\n", &d, &e);

		if(1 == 1) {

			int f;
			printf("&f: %p\n", &f);

		}

		int g;
		printf("&g: %p\n", &g);

		printf("\n");

	}

	printf("solo variables en un loop, 2da parte\n");

	int t = 5;
	int *m[t];

	for(int i=0; i<t; i++) {

		m[i] = (int*)malloc(sizeof(int));
		printf("&m[%d]: %p\n", i, &m[i]);
		printf("m[%d]: %p\n", i, m[i]);

	}

	printf("\n");

	for(int i=0; i<t; i++)
		free(m[i]);

	printf("solo variables en un loop, 3ra parte\n");

	for(int i=0; i<t; i++) {

		m[i] = (int*)malloc(sizeof(int));
		printf("&m[%d]: %p\n", i, &m[i]);
		printf("m[%d]: %p\n", i, m[i]);

	}

	printf("\n");

	for(int i=0; i<t; i++)
		free(m[i]);

	return 0;

}
