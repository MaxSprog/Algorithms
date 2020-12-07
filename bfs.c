#include<stdio.h>
#include <stdlib.h>
#include <limits.h>

struct list{
    int val;
    struct list *next;
};

int length(struct list *head){
    int cnt = 0;
    while (head != NULL){
        head = head->next;
        cnt++;
    }
    return cnt;
}

struct list *insert(struct list *head, int val, int ind){
    int n = length(head);
    if(ind > n){
        ind = n;
    }
    if(ind < 0){
        if(ind == -1){
            ind = n;
        }
        else{
            ind = 0;
        }
    }
    if (head == NULL){
        head = (struct list*)malloc(sizeof(struct list));
        head->val = val;
        head->next = NULL;
        return head;
    }
    else if(ind < n){
        if(ind == 0){
            struct list *h = (struct list*)malloc(sizeof(struct list));
            h->val = val;
            struct list *temp = head;
            h->next = temp;
            return h;
        }
        else{
            struct list *temp, *lt, *rt;
            rt = head;
            for (int i = 0; i < ind; i++){
                lt=rt;
                rt=rt->next;
            }
            temp = (struct list*)malloc(sizeof(struct list));
            temp->val = val;
            lt->next = temp;
            lt = temp;
            lt->next = rt;
            return head;
        }
    }
    struct list *temp = head;
    struct list *h = (struct list*)malloc(sizeof(struct list));
    
    h->val = val;
    h->next = NULL;
    for(int i = 0; i < ind && temp->next != NULL; i++)
        temp = temp->next;
    temp->next = h;
    return head;
}

struct list *deleteElement(struct list *head, int val){
    struct list *temp = head;
    if (temp->val == val){
        head = temp->next;
        free(temp);
        return head;
    }
    while(temp->next->val != val && temp->next->next != NULL){
        temp = temp->next;
    }
    if(temp->next == NULL)
        return head;
    struct list *nxtemp = temp->next->next;
    free(temp->next);
    temp->next = nxtemp;
    return head;
}

void freeList(struct list *head){
    struct list *temp = head;
    while(head != NULL){
        head = head->next;
        free(temp);
        temp = head;
    }
}

int in(struct list* list, int val){
    if(list == NULL || list->next == NULL){
        return 0;
    }
    while(list->next->val != val && list->next->next != NULL){
        list = list->next;
    }
    if(list->next->val == val){
        return 1;
    }
    return 0;
}

int main(){
    struct list *queue = NULL;
    struct list* seen = NULL;
    int n = 0, start = 0, end = 0, len = 0, P = 0, flag = 1;
    FILE* fin = fopen("inbfs.txt", "r");
    FILE* fout = fopen("outbfs.txt", "w");
    int** adj;
    int* dist;
    for(int p = 0; p < 5; p++){
        fscanf(fin, "%d %d %d", &n, &start, &end);
        adj = malloc(sizeof(int*) * n);
        dist = malloc(sizeof(int) * n);
        for(int i = 0; i < n; i++){
            adj[i] = malloc(sizeof(int) * n);
            dist[i] = INT_MAX;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                fscanf(fin, "%d", &adj[i][j]);
            }
        }
        dist[start] = 0;
        seen = NULL;
        queue = NULL;
        queue = insert(queue, start, -1);
        P = 0;
        while(queue != NULL){
            P = queue->val;
            queue = deleteElement(queue, P);
            if(!in(seen, P)){
                seen = insert(seen, P, -1);
                if(P == end){
                    flag = 0;
                    break;
                }
                for(int j = 0; j < n; j++){
                    if(adj[P][j] == 1 && !in(seen, j)){
                        queue = insert(queue, j, -1);
                        if(dist[j] > dist[P] + 1){
                            dist[j] = dist[P] + 1;
                        }
                    }
                }
            }
        }
        if(flag){
            fprintf(fout, "-1\n");
        }
        else{
            fprintf(fout, "%d\n", dist[end]);
            flag = 1;
        }
        free(dist);
        freeList(queue);
        freeList(seen);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}