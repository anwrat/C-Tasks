#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main(){
	//Appending all 3 files to one
//	appendtofile("PrimeData1.txt");
//	appendtofile("PrimeData2.txt");
//	appendtofile("PrimeData3.txt");
	return 0;
}