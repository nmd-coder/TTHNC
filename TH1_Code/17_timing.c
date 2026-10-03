// 17_timing.c - Đo thời gian thực thi bằng omp_get_wtime() (Phần 3 trang 33)
// Lưu ý: Trong file TH1.pdf có lỗi in ấn in ra exec_gap thay vì exec_time.
#include <stdio.h>
#include <omp.h>
#include <windows.h>

int main() {
    double itime, ftime, exec_time;

    // Lấy thời điểm bắt đầu
    itime = omp_get_wtime();

    // Giả lập khối tính toán (chờ 500ms)
    Sleep(500);

    // Lấy thời điểm kết thúc
    ftime = omp_get_wtime();

    exec_time = ftime - itime;
    printf("Thoi gian do chinh xac (omp_get_wtime): %f giay\n", exec_time);
    printf("Do phan giai dong ho (omp_get_wtick):   %.10e giay\n", omp_get_wtick());

    return 0;
}
