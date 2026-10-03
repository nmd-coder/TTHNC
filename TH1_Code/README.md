# THƯ MỤC SOURCE CODE BÀI THỰC HÀNH SỐ 1 - OPENMP (HPC)

Toàn bộ các ví dụ và bài toán trong file `TH1.pdf` đã được viết và kiểm tra biên dịch thành công.

## Danh sách các tệp mã nguồn:
1. `00_hello_openmp.c`: Chương trình kiểm tra cấu hình OpenMP (Phần 1, trang 1-2).
2. `01_atomic.c`: Chỉ thị `#pragma omp atomic` tránh xung đột dữ liệu (Phần 2, mục 1.1).
3. `02_barrier.c`: Chỉ thị `#pragma omp barrier` rào chắn đồng bộ luồng (Phần 2, mục 1.2).
4. `03_critical.c`: Chỉ thị `#pragma omp critical` tìm max mảng số (Phần 2, mục 1.3).
5. `04_flush.c`: Chỉ thị `#pragma omp flush` đồng bộ Cache về RAM (Phần 2, mục 1.4).
6. `05_for.c`: Chỉ thị `#pragma omp for` chia vòng lặp (Phần 2, mục 1.5).
7. `06_master.c`: Chỉ thị `#pragma omp master` chỉ luồng chủ chạy (Phần 2, mục 1.6).
8. `07_ordered.c`: Chỉ thị `#pragma omp ordered` chạy tuần tự trong vòng song song (Phần 2, mục 1.7).
9. `08_parallel.c`: Chỉ thị `#pragma omp parallel` tạo nhóm luồng (Phần 2, mục 1.8).
10. `09_sections.c`: Chỉ thị `#pragma omp sections` chia bài toán theo tác vụ (Phần 2, mục 1.9).
11. `10_single.c`: Chỉ thị `#pragma omp single` chỉ 1 luồng chạy (Phần 2, mục 1.10).
12. `11_copyprivate.c`: Mệnh đề `copyprivate` nhân bản dữ liệu từ single ra các thread (Phần 2, mục 2).
13. `12_if.c`: Mệnh đề `if(condition)` điều khiển bật/tắt song song (Phần 2, mục 2).
14. `13_nowait.c`: Mệnh đề `nowait` bỏ rào chắn cuối vòng for (Phần 2, mục 2).
15. `14_data_sharing.c`: So sánh các chế độ `shared`, `private`, `firstprivate`, `lastprivate` (Phần 2, mục 2).
16. `15_reduction.c`: Mệnh đề `reduction` tính tổng, tích an toàn (Phần 2, mục 2).
17. `16_schedule.c`: So sánh các cơ chế lập lịch `static`, `dynamic`, `guided` (Phần 2, mục 2).
18. `17_timing.c`: Đo thời gian bằng hàm `omp_get_wtime()` (Phần 3, trang 33).
19. `18_pi_integral.c`: Bài toán HPC tính xấp xỉ số Pi bằng tích phân số (Riemann sum) và đo Speedup (Phần 3, trang 34-35).

## Hướng dẫn chạy nhanh:
Mở PowerShell tại thư mục này và chạy:
```powershell
.\run_all.ps1
```
Hoặc biên dịch và chạy từng file riêng lẻ:
```powershell
gcc -fopenmp 18_pi_integral.c -o 18_pi_integral.exe
.\18_pi_integral.exe
```
