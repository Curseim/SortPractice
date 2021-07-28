#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <process.h>
#include <windows.h>

int Manager_Input();
void Manager_SortSelector(int *stat);
void Manager_Sort(int *arr, int *arr_cpy, int *timeTaken_Sort_Arr, int *stat);
void Sort_Bubble(int *arr);
void Sort_Selection(int *arr);
void Sort_Insertion(int *arr);
void Sort_Merge(int *arr, int left, int right);
void Merge(int *arr, int left, int mid, int right);
void Sort_Quick(int *arr, int left, int right);
int partition(int *arr, int left, int right);
void Swap(int *a,int *b);
int Calc_Time(int start, int end);
int ArrCount(int *arr);
void ArrCpy(int *arr, int *arr_cpy);
void PrintDisplay(int *arr, int *timeTaken_Sort_Arr, int *stat);

void main() 
{
	srand(time(NULL));	
	
	int count, stat[5] = { 1, 1, 1, 1, 1 };
	int timeTaken_Sort_Arr[5];	
	
	while (1) 
	{
		while (count == 0) 
		{
			count = Manager_Input();
			
			if (count == 0) 
			{
				Manager_SortSelector(stat);
			}			
		}
		
		int *arr = (int *)malloc(sizeof(int) * count);
		int *arr_cpy = (int *)malloc(sizeof(int) * count);
			
		for (int i = 0; i < count; i++)
		{
			arr[i] = rand() % 1000 + 1;
		}
	
		Manager_Sort(arr, arr_cpy, timeTaken_Sort_Arr, stat);
		PrintDisplay(arr_cpy, timeTaken_Sort_Arr, stat);		
		
		count = 0;
		free(arr);
		free(arr_cpy);
	}				
}
int Manager_Input() 
{
	int count;
	
	printf("\n\n   [ 0 ] 활성/비활성 정렬 선택\n\n");
	printf("   생성 할 수의 개수 입력 > ");
	scanf("%d", &count);
	system("cls");	
	
	return count;
}
void Manager_SortSelector(int *stat) 
{
	int select;
	
	printf("\n\n   상태\n\n");
	
	for (int i = 0; i < 5; i++) 
	{
		if (stat[i] == 1) 
		{
			printf("    O    ");
		} 
		else if (stat[i] == 0)
		{
			printf("    X    ");
		}
		
		switch (i) 
		{
			case 0 :
				printf("버블 [ 1 ]\n");
				break;
			case 1 :
				printf("선택 [ 2 ]\n");	
				break;	
			case 2 :
				printf("삽입 [ 3 ]\n");	
				break;	
			case 3 :
				printf("병합 [ 4 ]\n");	
				break;	
			case 4 :
				printf("  퀵 [ 5 ]\n");	
				break;					
		}		
	}
	printf("\n         뒤로 [ 0 ]\n");
	printf("\n              > ");
	scanf("%d", &select);
	
	switch (select) 
	{						
		case 1 :
			stat[0] = !stat[0];
			break;
		case 2 :
			stat[1] = !stat[1];
			break;				
		case 3 :
			stat[2] = !stat[2];
			break;				
		case 4 :
			stat[3] = !stat[3];
			break;				
		case 5 :
			stat[4] = !stat[4];
			break;											
	}
	
	system("cls");	
}
void Manager_Sort(int *arr, int *arr_cpy, int *timeTaken_Sort_Arr, int *stat) 
{
	int start, end;
	
	for (int i = 0; i < 5; i++) 
	{			
		if (stat[i] == 1)
		{
			ArrCpy(arr, arr_cpy);
			start = clock();			
					
			switch (i)
			{
				case 0 :
					printf("\n\n버블 정렬 계산 중...\n\n");	
					Sort_Bubble(arr_cpy);
					break;
				case 1 :
					printf("\n\n선택 정렬 계산 중...\n\n");
					Sort_Selection(arr_cpy);
					break;
				case 2 :
					printf("\n\n삽입 정렬 계산 중...\n\n");
					Sort_Insertion(arr_cpy);
					break;
				case 3 :
					printf("\n\n병합 정렬 계산 중...\n\n");
					Sort_Merge(arr_cpy, 0, ArrCount(arr) - 1);
					break;
				case 4 :
					printf("\n\n  퀵 정렬 계산 중...\n\n");
					Sort_Quick(arr_cpy, 0, ArrCount(arr) - 1);
					break;				
			}
			end = clock();
			timeTaken_Sort_Arr[i] = Calc_Time(start, end);		
			system("cls");			
		}	
	}			
}
int Calc_Time(int start, int end)
{
	return end - start;
}
void Sort_Bubble(int *arr)
{
	for (int i = 0; i < ArrCount(arr); i++) 
	{
		for (int j = 0; j < ArrCount(arr) - 1; j++) 
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
			}
		}	
	}
}
void Sort_Selection(int *arr)
{
	for (int i = 0; i < ArrCount(arr); i++) 
	{
		int minIndex = i;
		
		for (int j = i + 1; j < ArrCount(arr); j++) 
		{
			if (arr[minIndex] > arr[j]) 
			{
				minIndex = j;
			}
		}
		
		if (minIndex != i) 
		{
			Swap(&arr[i], &arr[minIndex]);
		}
	}
}
void Sort_Insertion(int *arr) 
{
	for (int i = 1; i < ArrCount(arr); i++) 
	{
		int temp = arr[i];
		int order = 0;
		while (arr[i] < arr[i - order - 1] && order < i) 
		{
			order++;
		}
		for (int j = 0; j < order; j++) 
		{
			arr[i - j] = arr[i - j - 1];
		}
		arr[i - order] = temp;
	}
}
void Sort_Merge(int *arr, int left, int right)
{
	int mid;
	
	if(left<right)
	{
	mid = (left+right)/2;
	Sort_Merge(arr, left, mid);
	Sort_Merge(arr, mid+1, right);
	Merge(arr, left, mid, right);
	}
}
void Merge(int *arr, int left, int mid, int right)
{
	int i, j, k, l;
	i = left;
	j = mid+1;
	k = left;
	
	int *sorted = (int *)malloc(sizeof(int) * ArrCount(arr));
	

	while(i<=mid && j<=right)
	{
		if(arr[i]<=arr[j]) 
		{
			sorted[k++] = arr[i++];		
		}
		else 
		{
			sorted[k++] = arr[j++];		
		}
	}

	if(i>mid)
	{
		for(l=j; l<=right; l++) 
		{
			sorted[k++] = arr[l];		
		}
	}

	else
	{
		for(l=i; l<=mid; l++) 
		{
			sorted[k++] = arr[l];		
		}
	}	

	for(l=left; l<=right; l++)
	{
		arr[l] = sorted[l];
	}
	
	free(sorted); 
}
void Sort_Quick(int *arr, int left, int right)
{
  if (left < right)
  {
    int p = partition(arr, left, right);

    Sort_Quick(arr, left, p - 1);
    Sort_Quick(arr, p + 1, right);
  }
}
int partition(int *arr, int left, int right)
{
	int pivot = arr[right];
	int i = (left - 1);
	
	for (int j = left; j <= (right - 1); j++) 
	{			
		if (arr[j] <= pivot) 
		{
			i++;
			Swap(&arr[i], &arr[j]);
		}
	}
	Swap(&arr[i + 1], &arr[right]);
	return (i + 1);
}
void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int ArrCount(int *arr) 
{
	return (_msize(arr) / sizeof(arr[0]));
}
void ArrCpy(int *arr, int *arr_cpy) 
{
	for (int i = 0; i < ArrCount(arr); i++)
	{
		arr_cpy[i] = arr[i];
	}
}
void PrintDisplay(int *arr, int *timeTaken_Sort_Arr, int *stat)
{
	int line = 0;
	
/*	printf("----------------------------------------------------------------------------------------------------\n");
		
	for (int j = 0; j < ArrCount(arr); j++) 
	{
		printf("%5d", arr[j]);
		line++;
		
		if (line >= 20) 
		{
			printf("\n");
			line = 0;
		}
	}
	if (line != 0) 
	{
		printf("\n");
	}
	
	printf("----------------------------------------------------------------------------------------------------\n"); 	*/
	
	printf("\n\n   %d 개의 정렬 결과\n\n", (_msize(arr) / sizeof(arr[0])));
	
	for (int i = 0; i < 5; i++)
	{
		switch (i) 
		{
			case 0 :
				printf("   버블 정렬");
				break;
			case 1 :
				printf("   선택 정렬");
				break; 
			case 2 :
				printf("   삽입 정렬");
				break;
			case 3 :
				printf("   병합 정렬");
				break;
			case 4 :
				printf("     퀵 정렬");
				break;
		}
		if (stat[i] == 1) 
		{
			printf(" : %5d ms\n", timeTaken_Sort_Arr[i]);			
		}
		else 
		{
			printf(" :       ms\n");		
		}
	}

}
