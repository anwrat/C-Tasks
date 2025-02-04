#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "lodepng.h"

unsigned char* input_image,*output_image;
unsigned int h,w;

typedef struct{
	int start,stop;
}ThreadArgs;

void *gaussian_blur(void *arg){
	ThreadArgs *args=(ThreadArgs*)arg;
	for (int y = args->start; y < args->stop; y++) {
        for (int x = 0; x < w; x++) {
            double r = 0, g = 0, b = 0,a=0;
            int count = 0;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int nx = x + kx;
                    int ny = y + ky;
                    if (nx >= 0 && ny >= 0 && nx < w && ny < h) {
                        int index = 4 * (ny * w + nx);
                        r += input_image[index];
                        g += input_image[index + 1];
                        b += input_image[index + 2];
                        a += input_image[index + 3];
                        count++;
                    }
                }
            }
            int index = 4 * (y * w + x);
            output_image[index] = (unsigned char)(r / count);
            output_image[index + 1] = (unsigned char)(g / count);
            output_image[index + 2] = (unsigned char)(b / count);
            output_image[index + 3] = (unsigned char)(a / count);
        }
    }
}

int main(){
	char *input="mario.png",*output="GaussianMario.png";
	int threadnum;
	if (lodepng_decode32_file(&input_image,&w,&h, input)) {
        printf("Error loading image file %s\n", input);
        return 1;
    }
	printf("The image is of size %d x %d",w,h);
	printf("\nFor Gaussian Blur:");
    output_image=(unsigned char*)malloc(4*w*h);
    if (!output_image) {
        printf("Error allocating memory for output image\n");
        free(input_image);
        return 1;
    }
    printf("\nEnter the number of threads: ");
    scanf("%d",&threadnum);
    pthread_t* threads = malloc(threadnum * sizeof(pthread_t));
	ThreadArgs *args = malloc(threadnum * sizeof(ThreadArgs));
	int rows_per_thread=h/threadnum;
	for(int i=0;i<threadnum;i++){
		args[i].start=i*rows_per_thread;
		if (i == threadnum - 1) {
            args[i].stop = h;
        } else {
            args[i].stop = (i + 1) * rows_per_thread;
        }
        pthread_create(&threads[i], NULL, gaussian_blur, &args[i]);
	}
	for (int i = 0; i < threadnum; i++) {
        pthread_join(threads[i], NULL);
    }
    lodepng_encode32_file(output, output_image, w, h);
    free(input_image);
    free(output_image);
    free(threads);
    free(args);
	return 0;
}