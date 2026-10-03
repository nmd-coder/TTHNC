// 08_parallel.c - Ví dụ directive parallel (tạo vùng song song)
#include <stdio.h>
#include <omp.h>

int main() {
    // Chỉ thị tạo 4 luồng chạy song song khối lệnh bên trong
    #pragma omp parallel num_threads(4)
    {
        int i = omp_get_thread_num();
        printf("Hello from thread %d\n", i);
    }
    return 0;
}
