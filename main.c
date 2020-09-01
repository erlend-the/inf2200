  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define NUM 9
#define ROWS 3
#define COLS 3
#define ITERATIONS 10
#define LOWER 0
#define UPPER 100

// Declaring that assembly function is provided elsewhere
extern void asm_function(int arr1[ROWS*COLS], int arr2[ROWS*COLS]);

// This should be the C equivalent to the assembly implementation
void c_function(int arr1[ROWS*COLS], int arr2[ROWS*COLS]) {
	int i, j, k;
	int res[ROWS*COLS];
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			for (k = 0; k < ROWS; k++) {
				arr1[i * COLS +k] * arr2[k * COLS + j];
			}
		}
	}
}

int main(int argc, char **argv) {
    
    clock_t start_time, end_time;
    double time = 0; 
    int i; 

	
	/* Start here */
	if (argc < 3) {
		fprintf(stderr, "Missing input.\n");
		printf("arg1: \t1 - C function\n\t2 - asm function \narg2: \tNum iterations");
		return 0;
	}

	int chosenFunc = atoi(argv[1]);
	int iterations = atoi(argv[2]);

	int i, j, k;
	for (i = 0; i < iterations; i++) {
		int arr1[ROWS*COLS];
		int arr2[ROWS*COLS];
	
		for (i = 0; i < NUM; i++) {
			int num = (rand() % (UPPER - LOWER + 1)) + LOWER;
			int num2 = (rand() % (UPPER - LOWER + 1)) + LOWER;
			arr1[i] = num;
			arr2[i] = num2;
		}
		
		if (chosenFunc == 1) {
            start_time = clock();
			c_function(arr1, arr2);
            end_time = clock();
		}
		else if (chosenFunc == 2) {
            start_time = clock();
			asm_function(arr1, arr2);
            end_time = clock(); 
		}	
        
        time += (double)(end_time - start_time) / CLOCKS_PER_SEC;
	}	
    return time / iterations;
}
