// 15_reduction.c - Ví dụ mệnh đề reduction (thu gom kết quả an toàn từ các luồng)
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define SUM_START 1
#define SUM_END 100

int main() {
    int nSum = 0;
    long long nProd = 1;
    int expected_sum = (SUM_START + SUM_END) * (SUM_END - SUM_START + 1) / 2;

    omp_set_num_threads(NUM_THREADS);

    // Tính tổng với reduction(+)
    #pragma omp parallel for reduction(+ : nSum)
    for (int i = SUM_START; i <= SUM_END; ++i) {
        nSum += i;
    }

    // Tính tích 1..10 với reduction(*)
    #pragma omp parallel for reduction(* : nProd)
    for (int i = 1; i <= 10; ++i) {
        nProd *= i;
    }

    printf("Tong tu %d den %d la: %d (Ky vong: %d)\n", SUM_START, SUM_END, nSum, expected_sum);
    printf("Giai thua 10! la: %lld (Ky vong: 3628800)\n", nProd);

    if (nSum == expected_sum && nProd == 3628800) {
        printf("=> Mệnh đề REDUCTION hoạt động CHÍNH XÁC!\n");
    }

    return 0;
}
