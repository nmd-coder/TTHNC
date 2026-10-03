// 16_schedule.c - So sánh các cơ chế lập lịch: static, dynamic, guided
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define STATIC_CHUNK 5
#define DYNAMIC_CHUNK 5
#define NUM_LOOPS 20

int main( )
{
    int nStatic1[NUM_LOOPS], nStaticN[NUM_LOOPS];
    int nDynamic1[NUM_LOOPS], nDynamicN[NUM_LOOPS];
    int nGuided[NUM_LOOPS];

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        // 1. static, chunk=1: Lần lượt chia từng vòng lặp: thread 0, 1, 2, 3, 0, 1...
        #pragma omp for schedule(static, 1)
        for (int i = 0 ; i < NUM_LOOPS ; ++i)
            nStatic1[i] = omp_get_thread_num();

        // 2. static, chunk=5: Mỗi thread nhận 1 khối 5 vòng lặp cố định:
        // Thread 0: 0..4, Thread 1: 5..9, Thread 2: 10..14, Thread 3: 15..19
        #pragma omp for schedule(static, STATIC_CHUNK)
        for (int i = 0 ; i < NUM_LOOPS ; ++i)
            nStaticN[i] = omp_get_thread_num();

        // 3. dynamic, chunk=1: Luồng nào rảnh thì nhận 1 bước lặp tiếp theo
        #pragma omp for schedule(dynamic, 1)
        for (int i = 0 ; i < NUM_LOOPS ; ++i)
            nDynamic1[i] = omp_get_thread_num();

        // 4. dynamic, chunk=5: Luồng nào rảnh thì nhận 1 khối 5 bước lặp tiếp theo
        #pragma omp for schedule(dynamic, DYNAMIC_CHUNK)
        for (int i = 0 ; i < NUM_LOOPS ; ++i)
            nDynamicN[i] = omp_get_thread_num();

        // 5. guided: Kích thước chunk giảm dần linh hoạt theo thời gian
        #pragma omp for schedule(guided)
        for (int i = 0 ; i < NUM_LOOPS ; ++i)
            nGuided[i] = omp_get_thread_num();
    }

    printf("========================================================================\n");
    printf("|  i  | static(1) | static(%d) | dynamic(1) | dynamic(%d) | guided |\n", STATIC_CHUNK, DYNAMIC_CHUNK);
    printf("========================================================================\n");
    for (int i = 0; i < NUM_LOOPS; ++i)
    {
        printf("| %2d  |     %d     |     %d      |     %d      |      %d      |   %d    |\n",
               i, nStatic1[i], nStaticN[i], nDynamic1[i], nDynamicN[i], nGuided[i]);
    }
    printf("========================================================================\n");
    return 0;
}
