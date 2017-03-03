#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// 정렬이 완료되었는 지 체크하기 위한 변수 TRUE, FALSE 전처리.
#define TRUE 1
#define FALSE 0
// 함수 정의.
int partition(int [], int, int);
void quickSort(int[], int, int);
void swap(int[], int, int);
void checkSort(int[], int);
void printArray(int[], int);

/*   Randomized-Partition
parameter a : array to be sorted
parameter p, r :index of start, end point in array */
// 랜덤하게 부분화하여 기준점을 찾는 함수.
// 항상 pivot 값을 반복할 때마다 오른쪽으로 이동시켜서 pivot을 얻음.
int partition(int a[], int p, int r) {
   int pivot = rand() % (r - p + 1); // 랜덤한 수에서 처음과 끝의 차이를 나눈 나머지를 pivot으로 정하여 초기화.
   pivot += p; // pivot 변수에 처음 인덱스를 더해줌.
   swap(a, r, pivot); // pivot과 끝의 값 swap.
   pivot = r; // 끝 인덱스를 pivot으로 설정.
   int i = p - 1; // 처음 인덱스 - 1로 초기화.
   // 인덱스의 처음부터 끝까지 반복하여 그 안에서 정렬 후 기준점이 될 인덱스 파악하는 부분.
   for (int j = p; j < r; j++)
   {
      if (a[j] <= a[pivot])
      {
         i++;
         swap(a, i, j);
      }
   }
   i++;
   swap(a, r, i);
   return i; // 기준점의 인덱스 반환.
}
/*   Randomized-Quicksort
parameter a : array to be sorted
parameter p, r : index of start, end point in array */
// 랜덤하게 Quick Sort해주는 함수.
void quickSort(int a[], int p, int r) {
   // 인덱스 값을 인자로 받아 조건에 맞게 분리하여 정렬 실시.
   if (p < r)
   {
      // divide and conquer 실시.
      int q = partition(a, p, r); // int형 변수 q를 partition 함수에서 얻은 기준점으로 초기화.
      quickSort(a, p, q ); // q를 기준으로 왼쪽 quickSort 함수 실시.
      quickSort(a, q + 1, r); // q를 기준으로 오른쪽 quickSort 함수 실시.
   }
}
/*   function to do swap in array a
parameter a : array
parameter i, j : index to be swapped */
// sort할 때, swap해주는 함수.
// file의 값을 입력받은 a와 swap을 위해 위치를 알려주는 변수를 받기 위해 int형 배열 a와 int형 변수 i, j를 매개 변수로 둠.
void swap(int a[], int i, int j)
{
   int temp = a[i]; // 이전 값을 저장하는 int형 변수 temp 선언 및 초기화.
   a[i] = a[j]; // j번째 있는 값을 i번째로 값 이동.
   a[j] = temp; // 이전에 저장한 temp 변수에 있는 값을 j번째로 이동.
}
// sort가 완료되었는지 체크해주는 함수.
// file의 값을 입력받은 a와 범위를 나타내는 변수 cnt를 받기 위해 int형 배열 a와 int형 변수 n을 매개 변수로 둠.
void checkSort(int a[], int n)
{
   int i, sorted; // 반복문을 위한 변수 i와 sort 체크를 위한 변수 sorted 선언.
   sorted = TRUE; // sorted 변수 초기화.
   for (i = 0; i < n - 1; i++)
   {
      if (a[i] > a[i + 1]) // sort가 안 되었을 시 FALSE.
      sorted = FALSE;
      if (!sorted) break; // FALSE일 경우 break.
   }
   if (sorted) printf("정렬 완료.\n"); // TRUE일 경우 완료 메세지 출력.
   else printf("정렬 오류.\n"); // 아닐 경우 오류 메세지 출력.
}
// 읽어 온 파일의 값이나 sort된 값을 출력해주는 함수.
// file의 값을 입력받은 a와 범위를 나타내는 변수 cnt를 받기 위해 int형 배열 a와 int형 변수 n을 매개 변수로 둠.
void printArray(int a[], int n)
{
   int i; // 반복문을 위한 int형 변수 i 선언.
   for (i = 0; i < n; i++) {// 출력을 위한 반복문.
      if (!((i + 1) % 10)) printf("%d\n", a[i]);
      else printf("%d   ", a[i]);
   }
}

// main fucntion
int main(void)
{
   int *a; // file에서 읽어 온 값을 저장하기 위한 포인터 변수.
   int cnt = 0; // file에서 읽어 온 값을 포인터 변수에 저장하면서 길이 조절을 위한 범위용 카운트 변수를 전역 변수로 둠.
   FILE *f = fopen("input500.txt", "rt"); // file을 읽기 전용으로 읽기 위해 설정하는 파일 포인터 변수.
   time_t start = 0, end = 0;

   a = (int*)malloc(sizeof(int)); // 포인터 변수 a 메모리 할당.
   // file이 끝이 아닐 동안 realloc 함수를 통해 사이즈를 재할당하면서 file의 정보를 스캔하여 포인터 변수 a에 저장.
   while (!feof(f))
   {
      a = (int*)realloc(a, sizeof(int)*(cnt + 1));
      fscanf(f, "%d\n", &a[cnt++]);
   }

   printf("input50.txt 실시.\n");
   // 읽어 온 값 출력해주는 부분.
   printf("File에서 읽어 온 값 : \n");
   printArray(a, cnt); // printArray 함수의 인자로 file의 입력값이 있는 a와 범위를 나타낼 수 있는 cnt를 넘겨줌.
   // Quick Sort 실시.
   printf("Quick Sort 실시. 시간 측정 중...\n");

   start = clock(); // 시간 변수 start를 시작 시간에 초기화.
   quickSort(a, 0, cnt-1); // quickSort 함수의 인자로 file의 입력값이 있는 a와 0, 범위를 나타낼 수 있는 cnt를 넘겨줌.
   end = clock(); // 시간 변수 end를 종료 시간에 초기화.
   printf("시간 측정 완료. 측정 시간 : %f초\n", (float)(end - start) / (CLOCKS_PER_SEC));
   checkSort(a, cnt); // sort가 완료되었는지 체크하는 부분. 인자로 file의 입력값이 있는 a와 범위를 나타낼 수 있는 cnt를 넘겨줌.

   // sort한 값을 출력해주는 부분.
   printf("Quick Sort한 값 : \n");
   printArray(a, cnt); // printArray 함수의 인자로 file의 입력값이 있는 a와 범위를 나타낼 수 있는 cnt를 넘겨줌.

   return 0;
}
