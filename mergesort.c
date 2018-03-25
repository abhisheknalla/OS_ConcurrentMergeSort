#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

void mergeSort(int a[], int l, int h);
void merge(int a[], int l, int mid, int r);

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n)
{
    int i, j, minimum_index;
		for (i = 0; i < n-1; i++)
    {
        minimum_index = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[minimum_index])
            minimum_index = j;
        swap(&arr[minimum_index], &arr[i]);
    }
}

int main()
{
	int shm_id;
	key_t key = IPC_PRIVATE;
	int *sharedArray;
	int length;
	printf("Enter size of input array\n");
	scanf("%d",&length);
	size_t SHM_size = sizeof(int)*length;
	if ((shm_id = shmget(key, SHM_size, IPC_CREAT | 0666)) < 0)
	{
		perror("shmget failed");
		exit(1);
	}
	if ((sharedArray = shmat(shm_id, NULL, 0)) == (int *) -1)
	{
		perror("shmat failed");
		exit(1);
	}
	int i,j;
	printf("Enter the input elements\n");
	for(i=0; i<SHM_size/4; i++)
	{
		scanf("%d",&sharedArray[i]);
	}
	mergeSort(sharedArray, 0, length-1);
	printf("The sorted array is:\n");
	for(i=0; i<SHM_size/4; i++)
	{
		printf("%d ",sharedArray[i]);
	}
	printf("\n");
	if (shmdt(sharedArray) == -1)
	{
		perror("shmdt failed");
		exit(1);
	}
	if (shmctl(shm_id, IPC_RMID, NULL) == -1)
	{
		perror("shmctl failed");
		exit(1);
	}
	return 0;
}

void merge(int a[], int l, int mid, int r)
{
	int i=l, k=mid+1, m=0;
	int count=r-l+1;
	int new[count];
	while (i<=mid && k<=r)
	{
		if (a[i]<a[k])
			new[m++]=a[i++];
		else if (a[k]<a[i])
			new[m++]=a[k++];
		else if (a[i]==a[k])
		{
			new[m++]=a[i++];
			new[m++]=a[k++];
		}
	}

	while (i<=mid)
		new[m++]=a[i++];

	while (k<=r)
		new[m++]=a[k++];

	int arr_count = l;
	for (i=0; i<count; i++,l++)
		a[l] = new[i];
}



void mergeSort(int a[], int l, int h)
{
	int i, len = (h-l+1);
	if (len<=5)
	{
		selectionSort(a+l, len);
		return;
	}

	pid_t lpid,rpid;
	lpid = fork();
	if (lpid<0)
	{
		perror("Left Child not created\n");
		exit(-1);
	}
	else if (lpid==0)
	{
		mergeSort(a,l,l+len/2-1);
		exit(0);
	}
	else
	{
		rpid = fork();
		if (rpid<0)
		{
			perror("Right Child not created\n");
			exit(-1);
		}
		else if(rpid==0)
		{
			mergeSort(a,l+len/2,h);
			exit(0);
		}
	}

	int status;

	waitpid(lpid, &status, 0);
	waitpid(rpid, &status, 0);

	merge(a, l, l+len/2-1, h);
}
