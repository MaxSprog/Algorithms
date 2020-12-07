#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

double getTime() {
  LARGE_INTEGER freq, val;
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&val);
  return (double)val.QuadPart / (double)freq.QuadPart;
}

void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}



int main(){
    FILE* fin = fopen("in.txt", "r");
    FILE* fout = fopen("out.txt", "w");
    int N = 0, n = 0;
    double start = 0;
    fscanf(fin, "%d", &N);
    int* arr = malloc(sizeof(int));
    for(int i = 0; i < N; i++){
        fscanf(fin, "%d", &n);
        free(arr);
        arr = malloc(sizeof(int) * n);
        for(int j = 0; j < n; j++){
            fscanf(fin, "%d", &arr[j]);
        }
        for(int j = 0; j < n; j++){
            fprintf(fout, "%d ", arr[j]);
        }
        fprintf(fout, "\n");
        start = getTime();
        for(int k = n - 1; k >= 0; k--){
            for(int j = (k + 1) / 2 - 1; j >= 0; j--){
                if(2 * j + 1 <= k){
                    if(arr[j] < arr[2*j + 1]){
                        swap(&arr[j], &arr[2*j + 1]);
                    }
                }
                if(2 * j + 2 <= k){
                    if(arr[j] < arr[2*j + 2]){
                        swap(&arr[j], &arr[2*j + 2]);
                    }
                }
            }
            swap(&arr[0], &arr[k]);
        }
        start = 1000 * (getTime() - start);
        for(int j = 0; j < n; j++){
            fprintf(fout, "%d ", arr[j]);
        }
        fprintf(fout, "\n");
        fprintf(fout, "%lf\n-\n", start);
    }
    free(arr);
    fclose(fin);
    fclose(fout);
    return 0;
}