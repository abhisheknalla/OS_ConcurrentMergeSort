#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NOTHREADS 2

int a[10005];

typedef struct node {
    int i;
    int j;
}NODE;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int n)
{
    int i, j, minimum_index;
    for (i = 0; i < n -1 ; i++)
    {
        minimum_index = i;
        for (j = i+1; j < n ; j++)
          if (a[j] < a[minimum_index])
            minimum_index = j;
        swap(&a[minimum_index], &a[i]);
    }
}

void merge(int i, int j)
{
        int mid = (i+j)/2;
        int ai = i;
        int bi = mid+1;
        int new[j-i+1], k = 0;
        while(ai <= mid && bi <= j) {
                if (a[ai] > a[bi])
                        new[k++] = a[bi++];
                else
                        new[k++] = a[ai++];
        }

        while(ai <= mid) {
                new[k++] = a[ai++];
        }

        while(bi <= j) {
                new[k++] = a[bi++];
        }

        for (ai = 0; ai < (j-i+1) ; ai++)
                a[i+ai] = new[ai];

}

void *mergesort(void *a)
{

        NODE *p = (NODE *)a;
        NODE n1, n2;
        int mid = (p->i+p->j)/2;
        pthread_t tid1, tid2;
        int ret;

        n1.i = p->i;
        n1.j = mid;

        n2.i = mid+1;
        n2.j = p->j;

        if (p->i >= p->j) return 0;
      /*  if (p->j - p->i <=5)
        {
          selectionSort(p->j - p->i);
          return 0;
        }*/

        ret = pthread_create(&tid1, NULL, mergesort, &n1);
        if (ret) {
                printf("unable to create thread\n");
                exit(1);
        }

        ret = pthread_create(&tid2, NULL, mergesort, &n2);
        if (ret) {
                printf("unable to create thread\n");
                exit(1);
        }

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        merge(p->i, p->j);
        pthread_exit(NULL);
}

int main()
{
        int i;
        NODE m;
        m.i = 0;
        pthread_t tid;

        int ret;
        int n;
        scanf("%d",&n);
        for(i=0;i<n;i++)scanf("%d",&a[i]);
        m.j = n-1;
        ret=pthread_create(&tid, NULL, mergesort, &m);
        if (ret) {
                printf("unable to create thread\n");
                exit(1);
        }

        pthread_join(tid, NULL);

        for (i = 0; i < n; i++)
                        printf ("%d ", a[i]);

        printf ("\n");
        return 0;
}
