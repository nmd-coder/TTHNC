// 11_copyprivate.c - Ví dụ mệnh đề copyprivate
#include <stdio.h>
#include <omp.h>

float x = 0.0f;
#pragma omp threadprivate(x)

int main() {
    float a = 0.0f;

    #pragma omp parallel num_threads(3)
    {
        // Thread thực thi single sẽ đọc a và x, sau đó copyprivate sẽ broadcast giá trị sang các thread khác
        #pragma omp single copyprivate(a, x)
        {
            a = 99.5f;
            x = 100.5f;
            printf("Luong %d thuc hien single: gan a = %.1f, x = %.1f\n", omp_get_thread_num(), a, x);
        }

        // Sau rào chắn single copyprivate, tất cả các luồng đều nhận được giá trị mới của a và x
        printf("Luong %d nhan duoc: a = %.1f, x = %.1f\n", omp_get_thread_num(), a, x);
    }

    return 0;
}
