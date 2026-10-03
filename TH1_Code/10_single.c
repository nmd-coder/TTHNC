// 10_single.c - Ví dụ directive single (chỉ 1 luồng bất kỳ thực thi khối lệnh)
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(4)
    {
        // Khối single 1: Chỉ 1 luồng duy nhất đọc dữ liệu (có barrier ngầm định ở cuối)
        #pragma omp single
        printf("--- Buoc 1: Thread %d doc du lieu vao (read input)\n", omp_get_thread_num());

        // Tất cả các luồng cùng tính toán song song
        printf("--- Buoc 2: Thread %d dang tinh toan...\n", omp_get_thread_num());

        // Khối single 2: Chỉ 1 luồng ghi kết quả
        #pragma omp single
        printf("--- Buoc 3: Thread %d ghi ket qua ra file (write output)\n", omp_get_thread_num());
    }
    return 0;
}
