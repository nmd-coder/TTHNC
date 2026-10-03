// 06_master.c - Ví dụ directive master (chỉ luồng chính chạy)
#include <omp.h>
#include <stdio.h>

int main( )
{
    int a[5], i;

    #pragma omp parallel num_threads(3)
    {
        // Tính toán song song
        #pragma omp for
        for (i = 0; i < 5; i++)
            a[i] = i * i;

        // Chỉ có luồng chính (thread 0) in kết quả trung gian
        #pragma omp master
        {
            printf("--- Ket qua trung gian (In boi Master thread %d) ---\n", omp_get_thread_num());
            for (i = 0; i < 5; i++)
                printf("a[%d] = %d\n", i, a[i]);
        }

        // Đồng bộ các luồng trước khi bước sang tính toán tiếp
        #pragma omp barrier

        // Tiếp tục tính toán song song
        #pragma omp for
        for (i = 0; i < 5; i++)
            a[i] += i;
    }

    printf("--- Ket qua cuoi cung ---\n");
    for (i = 0; i < 5; i++)
        printf("a[%d] = %d\n", i, a[i]);

    return 0;
}
