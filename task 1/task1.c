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
	fclose(fp1);
	fclose(flr);
}

int main(){
	//Appending all 4 files to one
//	appendtofile("datasetLR1.txt");
//	appendtofile("datasetLR2.txt");
//	appendtofile("datasetLR3.txt");
//	appendtofile("datasetLR4.txt");
	FILE *file=fopen("combinedLR.txt","r");
	if(file==NULL){
		printf("Error opening file combinedLR\n");
		return 1;
	}
	int x,y,n=0;
	double a,b;
	char line[150];
	double sum_x=0,sum_y=0,sum_xy=0,sum_x2=0,sum_y2=0;
	while(fgets(line,sizeof(line),file)!=NULL){
		char *token=strtok(line,",");
		if(token!=NULL){
			x=atoi(token);
		}
		token=strtok(NULL,",");
		if(token!=NULL){
			y=atoi(token);
		}
		sum_x+=x;
		sum_y+=y;
		sum_xy+=x*y;
		sum_x2+=x*x;
		sum_y2+=y*y;
		n++;
	}
	double denominator=(n*sum_x2)-(sum_x*sum_x);
	a=((sum_y*sum_x2)-(sum_x*sum_xy))/denominator;
	b=((n*sum_xy)-(sum_x*sum_y))/denominator;
	printf("\nThe value of a is: %lf",a);
	printf("\nThe value of b is %lf",b);
	printf("\nSummation of x: %.2f\n", sum_x);
    printf("Summation of y: %.2f\n", sum_y);
    printf("Summation of xy: %.2f\n", sum_xy);
    printf("Summation of x^2: %.2f\n", sum_x2);
    printf("Summation of y^2: %.2f\n", sum_y2);
    printf("The number of pairs are:%d\n ",n);
    printf("The general equation of the line is: y = %lfx + %lf\n", b, a);
    double input,output;
    printf("Enter the value of x: ");
    scanf("%lf",&input);
    output=input*a+b;
    printf("The predicted value of y is %lf",output);
    fclose(file);
	return 0;
}