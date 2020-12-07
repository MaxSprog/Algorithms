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

int pivot(int *arr, int l, int h)
{
    int p = arr[(l + h)/2];
    int lb = l-1;
    int hb = h+1;
    while(1){
        do{
            lb++;
        } while(arr[lb] < p);
        do{
            hb--;
        } while(arr[hb] > p);
        if(lb >= hb)
            return hb;
        swap(&arr[lb], &arr[hb]);
    }
}

void quick(int* arr, int l, int h, int depth){
    if(l >= h){
        return;
    }
    if(depth <= 0){
        for(int k = h; k >= l; k--){
            for(int j = (k + 1) / 2 - 1; j >= l; j--){
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
            swap(&arr[l], &arr[k]);
        }
    }
    int hb = pivot(arr, l, h);
    quick(arr, l, hb, depth - 1);
    quick(arr, hb + 1, h, depth - 1);
}

int main(){
    FILE* fin = fopen("in.txt", "r");
    FILE* fout = fopen("out.txt", "w");
    int N = 0, n = 0, depth;
    double start = 0;
    fscanf(fin, "%d", &N);
    int* arr = malloc(sizeof(int));
    for(int i = 0; i < N; i++){
        fscanf(fin, "%d", &n);
        depth = (int)floor(2 * log(n));
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
        quick(arr, 0, n - 1, depth);
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