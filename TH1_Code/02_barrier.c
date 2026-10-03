// 02_barrier.c - Ví dụ directive barrier (rào chắn đồng bộ)
#include <stdio.h>
#include <omp.h>
#include <windows.h>

int main() {
    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        printf("Thread %d: Bat dau giai doan 1...\n", id);

        // Giả lập công việc khác nhau tốn thời gian khác nhau
        Sleep((4 - id) * 100);

        printf("Thread %d: Hoan thanh giai doan 1, doi o barrier.\n", id);
        
        // Rào chắn đồng bộ: Mọi thread phải đến đây mới được đi tiếp giai đoạn 2
        #pragma omp barrier

        printf("Thread %d: >>> Qua barrier, bat dau giai doan 2!\n", id);
    }
    return 0;
}
