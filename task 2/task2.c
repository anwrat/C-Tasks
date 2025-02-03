#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int start, end;
    double value;
} Threadvar;

void* leibniz(void* arg) {
    Threadvar* var = (Threadvar*)arg;
    double sum = 0;
    for (int i = var->start; i < var->end; i++) {
        sum += pow(-1, i) / (2 * i + 1);
    }
    var->value = sum;
    return NULL;
}

int main() {
    int threadnum, iterations;
    printf("Enter the number of iterations: ");
    scanf("%d", &iterations);
    printf("Enter the number of threads to make: ");
    scanf("%d", &threadnum);
    if (threadnum <= 0 || iterations <= 0) {
        printf("Number of threads and iterations must be greater than 0.\n");
        return 1;
    }
    Threadvar* thread_data = malloc(threadnum * sizeof(Threadvar));
    pthread_t* threads = malloc(threadnum * sizeof(pthread_t));
    int base_slice = iterations / threadnum;
    int remainder = iterations % threadnum;
    int start = 0;
    for (int i = 0; i < threadnum; i++) {
        thread_data[i].start = start;
        thread_data[i].end = start + base_slice;
        if (i < remainder) {
    		thread_data[i].end += 1;
		}
        start = thread_data[i].end; 
    }
    for (int i = 0; i < threadnum; i++) {
        pthread_create(&threads[i], NULL, leibniz, &thread_data[i]);
    }
    double pi = 0;
    for (int i = 0; i < threadnum; i++) {
        pthread_join(threads[i], NULL);
        pi += thread_data[i].value;
    }
    pi *= 4;
    printf("Using %d iterations and %d threads\nValue of Pi: %lf\n", iterations, threadnum, pi);
    free(thread_data);
    free(threads);
    return 0;
}
