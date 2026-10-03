// 09_sections.c - Ví dụ directive sections và section (chia các tác vụ độc lập)
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel sections num_threads(4)
    {
        #pragma omp section
        printf("Task A thuc thi boi thread %d\n", omp_get_thread_num());

        #pragma omp section
        printf("Task B thuc thi boi thread %d\n", omp_get_thread_num());

        #pragma omp section
        printf("Task C thuc thi boi thread %d\n", omp_get_thread_num());

        #pragma omp section
        printf("Task D thuc thi boi thread %d\n", omp_get_thread_num());
    }
    return 0;
}
