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
    int N = 0, n = 0, nd = 0, d = 0, l = 0, k = 0, tmp = 0;
    double start = 0;
    fscanf(fin, "%d", &N);
    int* arr = malloc(sizeof(int));
    int* arrd = malloc(sizeof(int));
    for(int i = 0; i < N; i++){
        fscanf(fin, "%d", &n);
        free(arr);
        free(arrd);
        arrd = malloc(sizeof(int));
        arr = malloc(sizeof(int) * n);
        for(int j = 0; j < n; j++){
            fscanf(fin, "%d", &arr[j]);
        }
        for(int j = 0; j < n; j++){
            fprintf(fout, "%d ", arr[j]);
        }
        fprintf(fout, "\n");
        d = 0;
        l = 0;
        nd = 0;
        start = getTime();
        while(1){
            if(l % 2 == 0){
                d = 9 * (int)pow(2, l) - 9 * (int)pow(2, l / 2) + 1;
            }
            else{
                d = 8 * (int)pow(2, l) - 6 * (int)pow(2, (l+1) / 2) + 1;
            }
            if(d * 3 >= n)
                break;
            arrd = realloc(arrd, ++nd * sizeof(int));
            arrd[l++] = d;
        }
        k = 0;
        for(int s = nd - 1; s >= 0; s--){
            for(int j = 0; j < n - arrd[s]; j++){
                k = j;
                while(k >= 0 && arr[k] > arr[k + arrd[s]]){
                    swap(&arr[k], &arr[k + arrd[s]]);
                    k -= arrd[s];
                }
            }
        }
        start = 1000 * (getTime() - start);
        for(int j = 0; j < n; j++){
            fprintf(fout, "%d ", arr[j]);
        }
        fprintf(fout, "\n");
        fprintf(fout, "%lf\n-\n", start);
    }
    free(arr);
    free(arrd);
    fclose(fin);
    fclose(fout);
    return 0;
}