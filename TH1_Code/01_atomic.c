// 01_atomic.c - Ví dụ directive atomic
#include <stdio.h>
#include <omp.h>

#define MAX 10

int main() {
    int count = 0;

    // Khởi tạo vùng song song với MAX luồng
    #pragma omp parallel num_threads(MAX)
    {
        // atomic bảo vệ thao tác tăng count++, tránh race condition (xung đột dữ liệu)
        #pragma omp atomic
        count++;
    }

    printf("Number of threads: %d\n", count);
    return 0;
}
