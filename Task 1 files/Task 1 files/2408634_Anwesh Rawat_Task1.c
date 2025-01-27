#include <stdio.h>

void appendtofile(char fpath[]){
	FILE *fp1,*flr;
	fp1=fopen(fpath,"r");
	if (fp1 == NULL) {
        printf("Error opening file %s\n", fpath);
        return;
    }
	flr=fopen("combinedLR.txt","a");
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
}

int main(){
	//Appending all 4 files to one
//	appendtofile("datasetLR1.txt");
//	appendtofile("datasetLR2.txt");
//	appendtofile("datasetLR3.txt");
//	appendtofile("datasetLR4.txt");
	return 0;
}