#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	int start,end;
}ThreadArgs;

int *numbers,*primes,prime_count=0;
pthread_mutex_t mutex;

void appendtofile(char fpath[]){
	FILE *fp1,*flr;
	fp1=fopen(fpath,"r");
	if (fp1 == NULL) {
        printf("Error opening file %s\n", fpath);
        return;
    }
	flr=fopen("combinedPrimeData.txt","a");
	if (flr == NULL) {
        printf("Error opening output file combinedLR.txt\n");
        fclose(fp1); 
        return;
    }
	char ch;
	while((ch=fgetc(fp1))!=EOF){
		fputc(ch,flr);
	}
	printf("\nSuccessfully appended!!");
	fclose(fp1);
	fclose(flr);
}

int checkprime(int n){
	if(n<2) return 0;
	for(int i=2;i<=sqrt(n);i++){
		if(n%i==0) return 0;
	}
	return 1;
}

void *primechecker(void *arg){
	ThreadArgs *args=(ThreadArgs*)arg;
	for(int i=args->start;i<args->end;i++){
		if(checkprime(numbers[i])){
			pthread_mutex_lock(&mutex);
			primes[prime_count++]=numbers[i];
			pthread_mutex_unlock(&mutex);
		}
	}
}

int main(){
	//Appending all 3 files to one
//	appendtofile("PrimeData1.txt");
//	appendtofile("PrimeData2.txt");
//	appendtofile("PrimeData3.txt");
	FILE *file=fopen("combinedPrimeData.txt","r");
	if(file==NULL){
		printf("Error opening file combinedLR\n");
		return 1;
	}
	char num[100];
	int total_numbers=0,temp,threadnum;
	//Checking total numbers in the file
	while(fscanf(file,"%d",&temp)==1){
		total_numbers++;		
	}
	//Resetting the file pointer
	rewind(file);
	numbers = (int *)malloc(total_numbers * sizeof(int));
    primes = (int *)malloc(total_numbers * sizeof(int));
	//For storing all numbers in an array
	int x=0;
	while (fscanf(file, "%d", &numbers[x]) == 1) {
        x++;
    }
    fclose(file);
	printf("Enter the number of threads to use: ");
	scanf("%d",&threadnum);
	pthread_mutex_init(&mutex, NULL);
	pthread_t* threads = malloc(threadnum * sizeof(pthread_t));
	ThreadArgs *args = malloc(threadnum * sizeof(ThreadArgs));
	int base_slice = total_numbers/ threadnum;
    int remainder = total_numbers % threadnum;
    int start = 0;
    for (int i = 0; i < threadnum; i++) {
        args[i].start = start;
        args[i].end = start + base_slice;
        if (i < remainder) {
    		args[i].end += 1;
		}
        start = args[i].end; 
    }
    for (int i = 0; i < threadnum; i++) {
        pthread_create(&threads[i], NULL, primechecker, &args[i]);
    }
    for (int i = 0; i < threadnum; i++) {
        pthread_join(threads[i], NULL);
    }
	FILE *output = fopen("primes_output.txt", "w");
    fprintf(output, "Total primes: %d\n", prime_count);
    for (int i = 0; i < prime_count; i++) {
        fprintf(output, "%d\n", primes[i]);
    }
    printf("Total numbers in the files: %d",total_numbers);
    printf("\nPrime numbers in the files: %d",prime_count);
    printf("\nPrime numbers written to file successfully!!");
    fclose(output);
    free(numbers);
    free(primes);
    free(threads);
    free(args);
    pthread_mutex_destroy(&mutex);
	return 0;
}