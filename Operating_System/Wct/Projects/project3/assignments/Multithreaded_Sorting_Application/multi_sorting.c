#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int* array;
int* result;
int n,mid;

typedef struct {
   int start;
   int end;
}parameters_sort;

typedef struct {
    int lstart;
    int lend;
    int rstart;
    int rend;
}parameters_merge;

void* sort(void *);
void* merge(void *);

int main (int argc, char* argv[]) {

    pthread_t sort1,sort2,mge;
    pthread_attr_t attr;

    /* initialization */
    pthread_attr_init(&attr);

    n = argc - 1;
    mid = n / 2;
    array = (int *)malloc(n * sizeof(int));
    result = (int*) malloc(n * sizeof(int));

    for(int i = 0; i < n; ++i) {
        array[i] = atoi(argv[i + 1]);
        printf("%d ", array[i]);
    }
    printf("\n");

    parameters_sort* arrl = (parameters_sort *) malloc(sizeof(parameters_sort));
    arrl -> start = 0;
    arrl -> end = mid;
    parameters_sort* arrh = (parameters_sort *) malloc(sizeof(parameters_sort));
    arrh -> start = mid + 1;
    arrh -> end = n - 1;
    parameters_merge* arre = (parameters_merge *) malloc(sizeof(parameters_merge));
    arre -> lstart = 0;
    arre -> lend = mid;
    arre -> rstart = mid + 1;
    arre -> rend = n - 1;

    /* create threads */
    pthread_create(&sort1, &attr, sort, arrl);
    pthread_create(&sort2, &attr, sort, arrh);
    pthread_join(sort1, NULL);
    pthread_join(sort2, NULL);
    pthread_create(&mge, &attr, merge, arre);
    pthread_join(mge, NULL);


    for(int i = 0;i < n;++i) {
       printf("%d ", result[i]);
    }
    printf("\n");


    free(array);
    free(result);
    free(arrl);
    free(arrh);
    free(arre);

    return 0;

}

/* Bubble sort */
void *sort(void *arg) {
    int flag;
    int tmp;

    parameters_sort *arr = (parameters_sort *) arg;

    for(int i = arr -> end - 1;i >= arr -> start; --i) {
        flag = 1;
        for(int j = arr -> start;j <= i;++j) {
            if(array[j] > array[j + 1]) {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1]  = tmp;
                flag = 0;
	        }
	    }
        if(flag) break;
    }
    return NULL;

}


void *merge(void *arg) {
    parameters_merge *arr = (parameters_merge *) arg;

    int pos1 = arr -> lstart;
    int pos2 = arr -> rstart;
    int pos = 0;

    while(pos1 <= arr -> lend && pos2 <= arr -> rend) {
        if(array[pos1] < array[pos2]) {
            result[pos] = array[pos1];
            ++pos;
            ++pos1;
        }
        else {
            result[pos] = array[pos2];
            ++pos;
            ++pos2;
        }
    }
    while(pos1 <= arr -> lend) {
        result[pos] = array[pos1];
        ++pos1;
        ++pos;
    }
    while(pos2 <= arr -> rend) {
        result[pos] = array[pos2];
        ++pos2;
        ++pos;
    }
    return NULL;

}