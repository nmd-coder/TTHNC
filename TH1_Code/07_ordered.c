// 07_ordered.c - Ví dụ directive ordered (thực thi theo đúng thứ tự tuần tự trong vòng song song)
#include <stdio.h>
#include <omp.h>

void test2(int iter)
{
    // Bắt buộc in theo thứ tự tuần tự: iter 0 -> 1 -> 2 -> 3 -> 4
    #pragma omp ordered
    printf("test2() iteration %d (chay boi thread %d)\n", iter, omp_get_thread_num());
}

int main( )
{
    int i;
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for ordered
        for (i = 0 ; i < 6 ; i++)
            test2(i);
    }
    return 0;
}
