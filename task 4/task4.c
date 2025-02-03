#include <stdio.h>
#include <pthread.h>
#include "lodepng.h"

int main(){
	//Create a copy of array for applying gaussian blur
	unsigned char* image;
	unsigned int h,w,x,y;
	lodepng_decode32_file(&image,&w,&h,"mario.png");
	printf("The image is of size %d x %d",w,h);
	printf("\nFor Gaussian Blur:");
	printf("\nEnter the x-coordinate of the pixel: ");
	scanf("%d",&x);
	printf("\nEnter the y-coordinate of the pixel: ");
	scanf("%d",&y);
	if (x > w || y > h) {
        printf("Number of pixels to change cannot exceed image dimensions.\n");
        return 1;
    }
	return 0;
}