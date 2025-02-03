#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
	for(int i=2;i<=sqrt(num);i++){
		if(num%i==0) return 0;
	}
	return 1;
}

int main(){
	//Appending all 3 files to one
//	appendtofile("PrimeData1.txt");
//	appendtofile("PrimeData2.txt");
//	appendtofile("PrimeData3.txt");
	FILE *file=fopen("combinedPrimeData.txt","r");
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