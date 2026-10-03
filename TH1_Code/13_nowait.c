// 13_nowait.c - Ví dụ mệnh đề nowait (bỏ rào chắn đồng bộ ở cuối vòng lặp for)
#include <stdio.h>
#include <omp.h>
#include <windows.h>

#define SIZE 4

int main() {
    int a[SIZE] = {1, 2, 3, 4};
    int b[SIZE] = {0};
    int c[SIZE] = {0};

    #pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();

        // Vòng lặp 1 có nowait: Thread nào xong không cần đợi thread kia
        #pragma omp for nowait
        for (int i = 0; i < SIZE; i++) {
            if (i == 0) Sleep(200); // Giả lập lặp 0 chạy lâu hơn
            b[i] = a[i] * a[i];
            printf("Luong %d tinh xong b[%d] = %d\n", id, i, b[i]);
        }

        // Vòng lặp 2
        #pragma omp for nowait
        for (int i = 0; i < SIZE; i++) {
            c[i] = a[i] * 10;
            printf("Luong %d tinh tiep c[%d] = %d (khong phai cho o barrier)\n", id, i, c[i]);
        }
    }

    return 0;
}
