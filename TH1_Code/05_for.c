// 05_for.c - Ví dụ directive for (chia vòng lặp cho các luồng)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NUM_THREADS 4
#define NUM_START 1
#define NUM_END 10

int main() {
    int i, nSum = 0;
    int nStart = NUM_START, nEnd = NUM_END;
    int nThreads = 0;
    int nSumCalc = (nStart + nEnd) * (nEnd - nStart + 1) / 2;

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel default(none) private(i) shared(nSum, nThreads, nStart, nEnd)
    {
        #pragma omp master
        nThreads = omp_get_num_threads();

        // Chia các bước lặp của vòng for cho các luồng trong nhóm
        #pragma omp for
        for (i = nStart; i <= nEnd; ++i) {
            #pragma omp atomic
            nSum += i;
        }
    }

    printf("%d OpenMP threads were used.\n", nThreads);
    if (nSum == nSumCalc) {
        printf("The sum of %d through %d is %d (Chinh xac!)\n", nStart, nEnd, nSum);
    } else {
        printf("ERROR: Expected %d, but got %d\n", nSumCalc, nSum);
    }

    return 0;
}
