#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int checkprime(int n){
	if(n<2) return 0;
	for(int i=2;i<=sqrt(num);i++){
		if(num%i==0) return 0;
	}
	return 1;
}

int main(){
	FILE *f1=fopen("PrimeData1.txt","r");
	FILE *f2=fopen("PrimeData2.txt","r");
	FILE *f3=fopen("PrimeData3.txt","r");
	FILE *prime=fopen("AllPrimeNumbers.txt",a);
	if(file==NULL){
		printf("Error opening file combinedLR\n");
		return 1;
	}
	char num[100];
	int n,total;
	while(fgets(num,sizeof(num),file)!=NULL){
		n=atoi(num);
	}
	return 0;
}