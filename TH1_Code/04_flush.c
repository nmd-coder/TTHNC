// 04_flush.c - Ví dụ directive flush (đồng bộ bộ nhớ cache về RAM)
#include <stdio.h>
#include <omp.h>

void read_val(int *data) {
    printf("Thread %d: Ghi gia tri vao data = 42\n", omp_get_thread_num());
    *data = 42;
}

void process_val(int *data) {
    printf("Thread %d: Doc va xu ly data...\n", omp_get_thread_num());
    (*data) += 10;
}

int main() {
    int data = 0;
    int flag = 0;

    #pragma omp parallel sections num_threads(2)
    {
        // Nhánh 1: Writer
        #pragma omp section
        {
            read_val(&data);
            #pragma omp flush(data)  // Đẩy data ra bộ nhớ dùng chung
            flag = 1;
            #pragma omp flush(flag)  // Bật cờ flag và đẩy ra bộ nhớ
        }

        // Nhánh 2: Reader
        #pragma omp section
        {
            // Chờ đến khi writer bật cờ flag
            while (!flag) {
                #pragma omp flush(flag)
            }
            #pragma omp flush(data)  // Đảm bảo nhìn thấy dữ liệu mới nhất của data
            process_val(&data);
            printf("Ket qua sau khi process: data = %d\n", data);
        }
    }

    return 0;
}
