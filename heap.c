//Name: Hetvi Bagdai
//Entry number: 2023CSB1123

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void readFile(const char* fn, int** Arr, int* n) {
    FILE* f = fopen(fn, "r");
    if (!f) {
        printf("File error.\n");
        exit(1);
    }

    int tmp;
    *n = 0;
    while (fscanf(f, "%d", &tmp) != EOF) {
        (*n)++;
    }

    *Arr = (int*)malloc((*n) * sizeof(int));
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < *n; i++) {
        fscanf(f, "%d", &((*Arr)[i]));
    }

    fclose(f);
}

void readInput(int** Arr, int* n) {
    printf("Please input an integer array with space-separator and press Enter when done:\n");

    size_t bs = 1024, len = 0;
    char* buf = (char*)malloc(bs * sizeof(char));
    if (!buf) {
        printf("Memory error.\n");
        exit(1);
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        buf[len++] = ch;
        if (len == bs) {
            bs *= 2;
            buf = (char*)realloc(buf, bs * sizeof(char));
            if (!buf) {
                printf("Memory error.\n");
                exit(1);
            }
        }
    }
    buf[len] = '\0';

    char* bcopy = strdup(buf);
    if (!bcopy) {
        printf("Memory error.\n");
        free(buf);
        exit(1);
    }

    char* tok = strtok(bcopy, " ");
    *n = 0;
    while (tok) {
        (*n)++;
        tok = strtok(NULL, " ");
    }

    *Arr = (int*)malloc((*n) * sizeof(int));
    if (!*Arr) {
        printf("Memory error.\n");
        free(bcopy);
        free(buf);
        exit(1);
    }

    tok = strtok(buf, " ");
    for (int i = 0; i < *n; i++) {
        (*Arr)[i] = atoi(tok);
        tok = strtok(NULL, " ");
    }

    free(buf);
    free(bcopy);
}

void function1(int* Arr, int n, int** CIarr) {
    *CIarr = (int*)malloc(n * sizeof(int));
    (*CIarr)[0] = Arr[0];
    for (int i = 1; i < n; i++) {
        (*CIarr)[i] = (*CIarr)[i-1] + Arr[i];
    }
}

void queryFunction1(int* CIarr, int* Arr, int n) {
    clock_t start, end;
    double t;

    //query 1

    start = clock();
    Arr[1] += 5;
    function1(Arr, n, &CIarr);
    end = clock();
    t = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The time taken for query 1 by function 1 is %f seconds\n", t);
    printf("The incremented value of the first index element is %d\n", Arr[1]);

    // Query 2
    start = clock();
    int sum = CIarr[n-6];
    end = clock();
    t = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The time taken for query 2 by function 1 is %f seconds\n", t);
    printf("The sum of first n-5 elements is %d\n", sum);
}

//update fenwik tree
void updateBIT(int* BItree, int n, int idx, int val) {
    idx++;
    while (idx <= n) {
        BItree[idx] += val;
        idx += idx & (-idx);
    }
}

//build fenwik tree
int* function2(int* Arr, int n) {
    int* BItree = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        BItree[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        updateBIT(BItree, n, i, Arr[i]);
    }
    return BItree;
}

// sum in fenwik tree
int queryBIT(int* BItree, int idx) {
    int sum = 0;
    idx++;
    while (idx > 0) {
        sum += BItree[idx];
        idx -= idx & (-idx);
    }
    return sum;
}

//queries on fenwik tree
void queryFunction2(int* BItree, int* Arr, int n) {
    clock_t start, end;
    double t;

    // Query 1
    start = clock();
    updateBIT(BItree, n, 0, 5);
    end = clock();
    t = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The time taken for query 1 by function 2 is %f seconds\n", t);
    printf("The incremented value of the first index element is %d\n", Arr[1] + 5);

    // Query 2
    start = clock();
    int sum = queryBIT(BItree, n-6);
    end = clock();
    t = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The time taken for query 2 by function 2 is %f seconds\n", t);
    printf("The sum of first n-5 elements is %d\n", sum);
}


int main() {
    char ch;
    int *Arr = NULL, n;
    int *CIarr = NULL, *BItree = NULL;

    printf("Please enter a choice: a or b\n");
    scanf(" %c", &ch);
    getchar();  

    if (ch == 'a') {
        readFile("ExampleFile.txt", &Arr, &n); 
    } else if (ch == 'b') {
        readInput(&Arr, &n);
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    printf("The array size is %d\n", n);

   
    Arr[0] = 0;


    printf("By function 1:\n");
    function1(Arr, n, &CIarr);
    queryFunction1(CIarr, Arr, n);

    printf("By function 2:\n");
    BItree = function2(Arr, n);
    queryFunction2(BItree, Arr, n);


    free(Arr);
    free(CIarr);
    free(BItree);

    return 0;
}
