#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <process.h>
#include <windows.h>
#define LIMITCOUNT 1000000000

CONSOLE_SCREEN_BUFFER_INFO curInfo;

void gotoxy(int x, int y);
int Manager_Input(short *arr, int *timeTaken_Sort_Arr, int *stat);
void Manager_SortSelector(int *stat);
void Manager_Sort(short *arr, short *arr_cpy, int *timeTaken_Sort_Arr, int *stat);
void Sort_Bubble(short *arr, int count);
void Sort_Selection(short *arr, int count);
void Sort_Insertion(short *arr, int count);
void Sort_Merge(short *arr, int left, int right, short* sorted);
void Merge(short *arr, int left, int mid, int right, short *sorted);
void Sort_Quick(short *arr, int left, int right);
int partition(short *arr, int left, int right);
void Sort_Heap(short *arr);
void Swap(short *a,short *b);
int Calc_Time(int start, int end);
const char *Calc_ReqMem(int count, int *stat);
const char *Calc_Comma000(int count);
int ArrCount(short *arr);
void ArrCpy(short *arr, short *arr_cpy);
void PrintDisplay(short *arr, int *timeTaken_Sort_Arr, int *stat);

void main() 
{	
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	srand(time(NULL));	
	
	unsigned int count = 0, stat[5] = { 1, 1, 1, 1, 1 };
	int timeTaken_Sort_Arr[5];		
	short *arr = (short *)malloc(sizeof(short) * 1);
	arr[0] = -1;	
	
	while (1) 
	{		
		while (count == 0)
		{
			count = Manager_Input(arr, timeTaken_Sort_Arr, stat);
			
			if (count == 0) 
			{
				arr[0] = -1;
				Manager_SortSelector(stat);
			}			
		}
		arr = realloc(arr, sizeof(short) * count);
		short *arr_cpy = (short *)malloc(sizeof(short) * count);
			
		printf("\n\n   난수 섞는중...\n\n");
		for (int i = 0; i < count; i++)
		{
			arr[i] = rand();
		}
		system("cls");

		Manager_Sort(arr, arr_cpy, timeTaken_Sort_Arr, stat);
		
		printf("\n\n   결과 정리중...\n\n");
		ArrCpy(arr_cpy, arr);
		free(arr_cpy);
		system("cls");
		
		PrintDisplay(arr, timeTaken_Sort_Arr, stat);
		
		count = 0;
	}				
}
int Manager_Input(short *arr, int *timeTaken_Sort_Arr, int *stat) 
{
	unsigned int count = 0;
	int select = 0;
	char count_s[14] = "0";
	
	while (select != 27) 
	{
		system("cls");
		
		if (arr[0] != -1 )
		{
			PrintDisplay(arr, timeTaken_Sort_Arr, stat);			
		}	
				
		printf("\n\n   [ ESC ] 활성/비활성 정렬 선택\n\n\n");
		printf("   생성 할 수의 개수 입력 ▶ ");
		printf("%s", count_s);
		printf("\n\n     요구되는 메모리 용량 ▷ %s\n\n", Calc_ReqMem(count, stat));
		
//		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
//		gotoxy(curInfo.dwCursorPosition.X, curInfo.dwCursorPosition.Y);
		
		select = getch();	
				
		if (select == 27) 
		{
			count = 0;
		}
		else if (count == 0 && select == 13) 
		{
			select = 0;
		}
		else if (select == 13) 
		{
			select = 27;
		}		
		else if ((select == 8) || ((select >= 48) && (select <= 57)))
		{
			if (select == 8) 
			{
				count /= 10;
				strcpy(count_s, itoa(count, count_s, 10));					
			}
			else 
			{
				if (count >= (LIMITCOUNT / 10)) 
				{
					count = LIMITCOUNT;
					strcpy(count_s, itoa(count, count_s, 10));	
				}
				else 
				{
					count = (count * 10) + (select - 48);		
					strcpy(count_s, itoa(count, count_s, 10));						
				}
			}
		}
		
		if (count > 999) 
		{
			strcpy(count_s, Calc_Comma000(count));
		}           
		else 
		{
			strcpy(count_s, itoa(count, count_s, 10));				
		}
	}
	
	system("cls");
		
	return count;
}
void Manager_SortSelector(int *stat) 
{
	int select = 0;
	
	while(select != 27) 
	{
		printf("\n\n   상태\n\n");
		
		for (int i = 0; i < 5; i++) 
		{
			if (stat[i] == 1) 
			{
				printf("    ▣    ");
			} 
			else if (stat[i] == 0)
			{
				printf("    □    ");
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
		
		printf("\n         뒤로 [ ESC ]\n\n");
		
		select = getch();
		
		switch (select - 48)
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
}
void Manager_Sort(short *arr, short *arr_cpy, int *timeTaken_Sort_Arr, int *stat) 
{
	int start, end;
	
	for (int i = 0; i < 5; i++) 
	{			
		if (stat[i] == 1)
		{
			printf("\n\n   난수 복사중...\n\n");
			ArrCpy(arr, arr_cpy);
			system("cls");
			start = clock();			
					
			switch (i)
			{
				case 0 :
					printf("\n\n   버블 정렬 계산 중...\n\n");	
					Sort_Bubble(arr_cpy, ArrCount(arr));
					break;
				case 1 :
					printf("\n\n   선택 정렬 계산 중...\n\n");
					Sort_Selection(arr_cpy, ArrCount(arr));
					break;
				case 2 :
					printf("\n\n   삽입 정렬 계산 중...\n\n");
					Sort_Insertion(arr_cpy, ArrCount(arr));
					break;
				case 3 :
					printf("\n\n   병합 정렬 계산 중...\n\n");
					short *sorted = (short *)malloc(sizeof(short) * ArrCount(arr));
					Sort_Merge(arr_cpy, 0, ArrCount(arr) - 1, sorted);
					free(sorted);
					break;
				case 4 :
					printf("\n\n   퀵 정렬 계산 중...\n\n");
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
const char *Calc_ReqMem(int count_Int, int *stat)
{
	static char count_s[16];
	
	float count = (float)count_Int;
	int stack = 0;
	
	int multiplier = 4;
	
	if (stat[3] == 1) 
	{
		multiplier = 6;
	}
	
	if ((count * multiplier) > 1023) 
	{
			count /= 1024;
			count *= multiplier;

		while ((count / 1024) >= 1) 
		{
			count /= 1024;
			stack++;
		}
		
		sprintf(count_s, "%.2f", count);
		switch (stack) 
		{
			case 0 :
				strcat(count_s , " KiB");
				break;
			case 1 :
				strcat(count_s , " MiB");
				break;
			case 2 :
				strcat(count_s , " GiB");
				break;
		}
	}
	else 
	{		
		strcpy(count_s, itoa((count * multiplier), count_s, 10));	
		strcat(count_s, " Byte");
	}

	return count_s;
}
const char *Calc_Comma000(int count) 
{
	static char count_s[14];
	
	unsigned int temp_count = count;	
	char temp_count_s[4] = "";
	int dot_count = 0;
	strcpy(count_s, "");
		
	while ((temp_count / 1000) != 0) 
	{
		temp_count /= 1000;
		dot_count++;
	}
			
	temp_count = count;
	
	for (int i = dot_count; i > 0; i--) 
	{
		temp_count /= pow(1000, i);
		temp_count %= 1000;
		
		if (temp_count == 0) 
		{
			strcat(count_s, "000");						
		}
		else 
		{
			if ((strlen(itoa(temp_count, temp_count_s, 10)) < 3) && (i != dot_count))
			{
				int zeroCount = 3 - strlen(itoa(temp_count, temp_count_s, 10));
				
				for (int j = 0; j < zeroCount; j++) 
				{
					strcat(count_s, "0");		
				}
				
				strcat(count_s, itoa(temp_count, temp_count_s, 10));
			}
			else 
			{
				strcat(count_s, itoa(temp_count, temp_count_s, 10));						
			}			
		}
		
		strcat(count_s, ",");
		temp_count = count;
	}
	
	if ((temp_count % 1000) == 0) 
	{
		strcat(count_s, "000");
	}
	else 
	{
		int zeroCount = 3 - strlen(itoa(temp_count % 1000, temp_count_s, 10));
		
		for (int i = 0; i < zeroCount; i++)
		{
			strcat(count_s, "0");
		}	
		strcat(count_s, itoa(temp_count % 1000, temp_count_s, 10));			
	}
	
	return count_s;
}
void Sort_Bubble(short *arr, int count)
{	
	for (int i = 0; i < count; i++) 
	{
		for (int j = 0; j < count - 1; j++) 
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}	
	}
}
void Sort_Selection(short *arr, int count)
{
	for (int i = 0; i < count; i++) 
	{
		int minIndex = i;
		
		for (int j = i + 1; j < count; j++) 
		{
			if (arr[minIndex] > arr[j]) 
			{
				minIndex = j;
			}
		}
		
		if (minIndex != i) 
		{
			int temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
		}
	}
}
void Sort_Insertion(short *arr, int count) 
{
	for (int i = 1; i < count; i++) 
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
void Sort_Merge(short *arr, int left, int right, short *sorted)
{
	int mid;
	
	if(left<right)
	{
	mid = (left+right)/2;
	Sort_Merge(arr, left, mid, sorted);
	Sort_Merge(arr, mid+1, right, sorted);
	Merge(arr, left, mid, right, sorted);
	}
}
void Merge(short *arr, int left, int mid, int right, short *sorted)
{
	int i, j, k, l;
	i = left;
	j = mid+1;
	k = left;

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
}
void Sort_Quick(short *arr, int left, int right)
{
  if (left < right)
  {
    int p = partition(arr, left, right);

    Sort_Quick(arr, left, p - 1);
    Sort_Quick(arr, p + 1, right);
  }
}
int partition(short *arr, int left, int right)
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
void Sort_Heap(short *arr) 
{
	
}
void Swap(short *a, short *b)
{
	short temp = *a;
	*a = *b;
	*b = temp;
}
int ArrCount(short *arr) 
{
	return (_msize(arr) / sizeof(arr[0]));
}
void ArrCpy(short *arr, short *arr_cpy) 
{
	for (int i = 0; i < ArrCount(arr); i++)
	{
		arr_cpy[i] = arr[i];
	}
}
void PrintDisplay(short *arr, int *timeTaken_Sort_Arr, int *stat)
{
	int line = 0;
	

	
/*	printf("------------------------------------------------------------------------------------------------------------------------\n");	
		
	for (int j = 0; j < ArrCount(arr); j++) 
	{
		printf("%6d", arr[j]);
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
	
	printf("------------------------------------------------------------------------------------------------------------------------\n"); 	 */
	
	printf("\n\n   %s 개의 정렬 결과\n\n", Calc_Comma000(ArrCount(arr)));
	
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
			printf(" : %6d ms\n", timeTaken_Sort_Arr[i]);			
		}
		else 
		{
			printf(" :        ms\n");		
		}
	}
}
void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} 
