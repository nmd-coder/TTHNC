// 18_pi_integral.c - Thuật toán song song tính xấp xỉ số Pi (Trang 34-35)
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Hàm tính Pi song song với OpenMP
double test2_parallel(long long num_steps, int num_threads) {
    long long i;
    double x, pi, sum = 0.0, step;
    step = 1.0 / (double)num_steps;

    omp_set_num_threads(num_threads);
    #pragma omp parallel for reduction(+:sum) private(x)
    for (i = 1; i <= num_steps; i++) {
        x = (i - 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    return pi;
}

// Hàm tính Pi tuần tự (1 thread)
double test2_serial(long long num_steps) {
    long long i;
    double x, pi, sum = 0.0, step;
    step = 1.0 / (double)num_steps;

    for (i = 1; i <= num_steps; i++) {
        x = (i - 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    return pi;
}

int main(int argc, char* argv[]) {
    long long n = 100000000; // 100,000,000 bước để đo rõ chênh lệch thời gian
    if (argc > 1) {
        n = atoll(argv[1]);
    }

    printf("========================================================================\n");
    printf("THUAT TOAN TICH PHAN TINH SO PI TRONG HPC (OPENMP)\n");
    printf("Cong thuc: Integral(4 / (1 + x^2)) dx tu 0 den 1 = PI\n");
    printf("So buoc chia (num_steps): %lld\n", n);
    printf("========================================================================\n\n");

    // 1. Chạy tuần tự
    double t_start = omp_get_wtime();
    DWORD dwStart = GetTickCount();
    double pi_seq = test2_serial(n);
    DWORD dwTimeSeq = GetTickCount() - dwStart;
    double t_seq = omp_get_wtime() - t_start;

    printf("[Chay Tuan Tu] (1 thread):\n");
    printf("  Pi = %.15f\n", pi_seq);
    printf("  Thoi gian (GetTickCount): %lu ms\n", dwTimeSeq);
    printf("  Thoi gian (omp_get_wtime): %.6f giay\n\n", t_seq);

    // 2. Chạy song song khảo sát hiệu năng với các số luồng khác nhau
    printf("[Khao sat Song Song theo so luong luong OpenMP]:\n");
    printf("%-10s | %-18s | %-15s | %-10s | %-10s\n", "So Luong", "Pi Xap Xi", "Thoi Gian (s)", "Speedup", "Hieu Suat");
    printf("------------------------------------------------------------------------\n");

    int thread_counts[] = {1, 2, 4, 8, 12};
    int num_tests = sizeof(thread_counts) / sizeof(thread_counts[0]);

    for (int idx = 0; idx < num_tests; idx++) {
        int threads = thread_counts[idx];

        t_start = omp_get_wtime();
        double pi_par = test2_parallel(n, threads);
        double t_par = omp_get_wtime() - t_start;

        double speedup = t_seq / t_par;
        double efficiency = (speedup / threads) * 100.0;

        printf("%-10d | %.15f | %-15.6f | %-10.2fx | %-9.1f%%\n",
               threads, pi_par, t_par, speedup, efficiency);
    }
    printf("========================================================================\n");

    return 0;
}
