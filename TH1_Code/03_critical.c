// 03_critical.c - Ví dụ directive critical (vùng găng / tranh chấp)
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int main()
{
    int i;
    int max;
    int a[SIZE];

    srand((unsigned int)time(NULL));
    printf("Khoi tao mang a: ");
    for (i = 0; i < SIZE; i++)
    {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
    }
    printf("\n");

    max = a[0];

    #pragma omp parallel for num_threads(4)
    for (i = 1; i < SIZE; i++)
    {
        if (a[i] > max)
        {
            // Chỉ 1 luồng được vào khối critical tại 1 thời điểm
            #pragma omp critical
            {
                // Kiểm tra lại lần 2 (Double-checked locking pattern)
                // vì có thể biến max đã bị luồng khác cập nhật trước đó
                if (a[i] > max) {
                    max = a[i];
                    printf("Thread %d cap nhat max moi = %d\n", omp_get_thread_num(), max);
                }
            }
        }
    }

    printf("Gia tri max cuoi cung tim duoc: %d\n", max);
    return 0;
}
