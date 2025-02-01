#include <stdio.h>
#include <pthread.h>



void* leibniz(void*arg){
	
}

int main(){
	int threadnum,iterations;
	printf("Enter the number of iterations: ");
	scanf("%d",&iterations);
	printf("Enter the number of threads to make: ");
	scanf("%d",&threadnum);
	if(threadnum==0 || iterations==0){
		printf("Number of threads and iterations must be greater than 0.\n");
		return 1;
	}
	return 0;
}