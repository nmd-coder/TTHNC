// 12_if.c - Ví dụ mệnh đề if
#include <stdio.h>
#include <omp.h>

void test(int val) {
    // Nếu val != 0 thì chạy song song, nếu val == 0 thì chạy tuần tự (1 luồng)
    #pragma omp parallel if(val) num_threads(4)
    {
        if (omp_in_parallel()) {
            #pragma omp single
            printf("val = %d: Chay SONG SONG voi %d luong\n", val, omp_get_num_threads());
        } else {
            printf("val = %d: Chay TUAN TU (1 luong)\n", val);
        }
    }
}

int main() {
    printf("--- Kiem tra test(0) ---\n");
    test(0);

    printf("--- Kiem tra test(2) ---\n");
    test(2);

    return 0;
}
