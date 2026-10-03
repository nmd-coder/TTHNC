# BÁO CÁO BÀI THỰC HÀNH SỐ 1: HỌC PHẦN HPC (TÍNH TOÁN HIỆU NĂNG CAO)
**Chủ đề:** Cài đặt môi trường và Lập trình song song với OpenMP trong môi trường bộ nhớ chia sẻ (Shared Memory)

---

## I. MỤC TIÊU VÀ DANH SÁCH CÔNG VIỆC ĐÃ THỰC HIỆN
- [x] **Cài đặt và thiết lập môi trường biên dịch OpenMP:**
  - Cấu hình Visual Studio (bản Community): Bật cờ `OpenMP Support (/openmp)` trong C/C++ > Language.
  - Thiết lập biên dịch dòng lệnh qua GCC/G++ MinGW với cờ `-fopenmp`.
- [x] **Lập trình và làm chủ các chỉ thị chỉ dẫn (Directives) của OpenMP API:**
  - Thực hành tạo vùng song song: `#pragma omp parallel`
  - Chia sẻ công việc vòng lặp: `#pragma omp for`
  - Chia nhỏ các luồng công việc độc lập: `#pragma omp sections` và `#pragma omp section`
  - Đồng bộ và giới hạn luồng: `#pragma omp single`, `#pragma omp master`, `#pragma omp barrier`
  - Cơ chế đồng bộ bảo vệ vùng tranh chấp: `#pragma omp critical`, `#pragma omp atomic`
  - Đồng bộ khung nhìn bộ nhớ giữa cache và RAM: `#pragma omp flush`
  - Thực thi tuần tự hóa có thứ tự: `#pragma omp ordered`
- [x] **Làm chủ các mệnh đề (Clauses) trong OpenMP:**
  - Mệnh đề phạm vi dữ liệu: `shared`, `private`, `firstprivate`, `lastprivate`, `threadprivate`, `copyprivate`, `copyin`
  - Mệnh đề điều kiện và luồng: `if`, `num_threads`, `nowait`
  - Mệnh đề thu gom kết quả song song: `reduction`
  - Các cơ chế lập lịch phân phối công việc: `schedule(static, chunk)`, `schedule(dynamic, chunk)`, `schedule(guided)`
- [x] **Sử dụng các biến môi trường và hàm thư viện Run-time OpenMP:**
  - Đọc/ghi số luồng: `omp_set_num_threads()`, `omp_get_num_threads()`, `omp_get_thread_num()`
  - Đo thời gian chính xác cao: `omp_get_wtime()`, `omp_get_wtick()`
- [x] **Thực hành thuật toán HPC: Tính xấp xỉ số Pi bằng tích phân số (Riemann Sum):**
  - Cài đặt thuật toán song song với `parallel for reduction(+:sum)`
  - So sánh thời gian thực thi tuần tự và song song trên các số lượng luồng khác nhau.
  - Tính toán hệ số tăng tốc (Speedup) và hiệu suất thực thi (Efficiency).

---

## II. KẾT QUẢ VÀ GIẢI THÍCH CHI TIẾT CÁC CHƯƠNG TRÌNH VÍ DỤ

### 1. Chương trình kiểm tra cấu hình OpenMP (Hello World song song)
- **Mã nguồn:** `00_hello_openmp.c`
- **Kết quả chạy:**
```text
Hello World from thread 0
Hello World from thread 6
Hello World from thread 4
Hello World from thread 3
Hello World from thread 7
Hello World from thread 8
Hello World from thread 9
Hello World from thread 2
Hello World from thread 1
Hello World from thread 10
Hello World from thread 5
Hello World from thread 11
There are 12 threads
```
- **Giải thích:**
  - Khối `#pragma omp parallel` khởi tạo nhóm luồng (team of threads). Thứ tự in `Hello World` từ các luồng không theo thứ tự từ 0 đến 11 do các luồng chạy đồng thời trên các nhân CPU khác nhau và cạnh tranh nhau khi xuất ra màn hình console (I/O race).
  - `#pragma omp barrier` đóng vai trò rào chắn: toàn bộ 12 luồng phải chạy đến điểm này và dừng lại đợi nhau. Sau khi tất cả đã đến rào chắn, luồng `th_id == 0` mới thực hiện in tổng số luồng (`There are 12 threads`).

---

### 2. Chỉ thị `#pragma omp atomic` (1.1)
- **Mã nguồn:** `01_atomic.c`
- **Kết quả:** `Number of threads: 10` (khi `num_threads(10)`).
- **Giải thích:**
  - Lệnh `count++` không phải là một thao tác đơn lẻ ở mức phần cứng máy tính (gồm 3 bước: Read -> Modify -> Write). Nếu không có cơ chế bảo vệ, việc 10 luồng cùng ghi đồng thời sẽ gây ra hiện tượng thất thoát dữ liệu (Race Condition).
  - `#pragma omp atomic` sử dụng các lệnh cấp phần cứng (Hardware atomic instructions) để khóa vị trí bộ nhớ của `count`, đảm bảo biến được tăng chính xác mà không tốn overhead lớn như `critical`.

---

### 3. Chỉ thị `#pragma omp barrier` (1.2)
- **Mã nguồn:** `02_barrier.c`
- **Kết quả:** Tất cả các luồng in xong giai đoạn 1 và báo "doi o barrier", sau đó mới đồng loạt in ">>> Qua barrier, bat dau giai doan 2!".
- **Giải thích:** Barrier là điểm đồng bộ hoá mức nhóm luồng. Không có luồng nào được vượt qua barrier chừng nào còn ít nhất một luồng trong nhóm chưa hoàn thành đoạn mã phía trước barrier.

---

### 4. Chỉ thị `#pragma omp critical` (1.3)
- **Mã nguồn:** `03_critical.c`
- **Mục đích:** Tìm giá trị lớn nhất (`max`) trong mảng số nguyên bằng thuật toán song song.
- **Giải thích:**
  - Vòng lặp `for` được chia cho 4 luồng. Khi một luồng thấy `a[i] > max`, nó cần cập nhật biến `max`.
  - Khối `#pragma omp critical` đảm bảo tại một thời điểm chỉ có duy nhất 1 luồng được phép thực thi đoạn gán `max = a[i]`.
  - Kỹ thuật *Double-checked locking* (kiểm tra lại `if (a[i] > max)` bên trong `critical`) giúp đảm bảo biến `max` không bị ghi đè bởi một giá trị nhỏ hơn từ luồng chạy trước đó.

---

### 5. Chỉ thị `#pragma omp flush` (1.4)
- **Mã nguồn:** `04_flush.c`
- **Mục đích:** Đồng bộ dữ liệu giữa Cache của các Core CPU với RAM theo mô hình Producer-Consumer.
- **Giải thích:**
  - Trong các CPU đa nhân hiện đại, mỗi Core có bộ nhớ đệm L1/L2 Cache riêng. Khi một luồng ghi vào biến `data` hoặc `flag`, giá trị có thể chỉ nằm trên Cache mà chưa kịp đẩy xuống RAM.
  - Lệnh `#pragma omp flush(var)` ép buộc CPU đẩy giá trị mới nhất của biến vào bộ nhớ dùng chung và làm mới bản sao trong bộ nhớ của các luồng khác, giúp luồng Reader đọc được giá trị `flag == 1` và `data` chính xác.

---

### 6. Chỉ thị `#pragma omp for` và `#pragma omp master` (1.5 & 1.6)
- **Mã nguồn:** `05_for.c` và `06_master.c`
- **Giải thích:**
  - `#pragma omp for` tự động chia không gian lặp `for (i = 1; i <= 10; ++i)` cho các luồng xử lý.
  - `#pragma omp master` chỉ thị chỉ cho phép luồng chủ (Master thread - có ID = 0) thực thi khối lệnh (thường dùng để in kết quả trung gian, khởi tạo mảng, hoặc ghi log). Khác với `single`, `master` không có rào chắn `barrier` ngầm định ở cuối.

---

### 7. Chỉ thị `#pragma omp ordered` (1.7)
- **Mã nguồn:** `07_ordered.c`
- **Kết quả:** Các bước lặp dù được các luồng khác nhau thực thi nhưng lệnh in bên trong `ordered` luôn xuất hiện theo đúng thứ tự: iteration 0 -> 1 -> 2 -> 3 -> 4...
- **Giải thích:** Cho phép thực thi một đoạn mã tuần tự theo đúng thứ tự bước lặp ban đầu ngay bên trong một vòng lặp đang chạy song song.

---

### 8. Chỉ thị `#pragma omp sections` và `single` (1.9 & 1.10)
- **Mã nguồn:** `08_sections.c` và `09_single.c`
- **Giải thích:**
  - `sections`: Dùng cho bài toán song song hóa tác vụ (Task Parallelism). Mỗi khối `#pragma omp section` là một công việc độc lập được giao cho một luồng rảnh rỗi trong nhóm.
  - `single`: Chỉ định khối lệnh chỉ được thực thi bởi 1 luồng duy nhất (luồng nào đến trước sẽ thực thi trước). Thích hợp cho việc đọc file đầu vào (read input) hoặc ghi file kết quả (write output).

---

### 9. Khảo sát các mệnh đề phạm vi dữ liệu (Data-Sharing Clauses)
- **Mã nguồn:** `14_data_sharing.c`
- **So sánh 4 phạm vi dữ liệu chính:**
  1. `shared(var)`: Tất cả các luồng cùng trỏ đến một ô nhớ chung trong RAM. Thay đổi của một luồng sẽ nhìn thấy bởi các luồng khác (cần cẩn trọng race condition).
  2. `private(var)`: Mỗi luồng tạo một bản sao cục bộ trên ngăn xếp (stack) riêng của nó. Bản sao này không được khởi tạo giá trị ban đầu, và giá trị ngoài vùng song song không bị ảnh hưởng.
  3. `firstprivate(var)`: Tương tự như `private`, nhưng bản sao của mỗi luồng được khởi tạo bằng giá trị của biến đó trước khi vào vùng song song.
  4. `lastprivate(var)`: Tương tự như `private`, nhưng sau khi kết thúc vòng lặp, giá trị của bước lặp tuần tự cuối cùng (iteration cuối) sẽ được gán ngược lại cho biến ngoài vùng song song.

---

### 10. Khảo sát các cơ chế lập lịch phân phối vòng lặp (`schedule`)
- **Mã nguồn:** `16_schedule.c`
- **Bảng phân phối luồng thực tế (NUM_THREADS = 4, NUM_LOOPS = 20):**

| Bước lặp (i) | static(chunk=1) | static(chunk=5) | dynamic(chunk=1) | dynamic(chunk=5) | guided |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 0 | Thread 0 | Thread 0 | Phân phối động | Thread 0 | Phân phối kích thước |
| 1 | Thread 1 | Thread 0 | theo luồng rảnh | Thread 0 | khối giảm dần |
| 2 | Thread 2 | Thread 0 | (ai xong trước | Thread 0 | theo cấp số |
| 3 | Thread 3 | Thread 0 | nhận việc trước)| Thread 0 | |
| 4 | Thread 0 | Thread 0 | ... | Thread 0 | |
| 5..9 | Luân phiên vòng | Thread 1 | ... | Thread 1 | |
| 10..14| Luân phiên vòng | Thread 2 | ... | ... | |
| 15..19| Luân phiên vòng | Thread 3 | ... | ... | |

- **Nhận xét chuyên môn:**
  - `static`: Overhead thấp nhất, phân chia công việc cố định ngay từ lúc biên dịch/khởi chạy. Thích hợp khi khối lượng tính toán của mỗi bước lặp là như nhau.
  - `dynamic`: Phù hợp khi thời gian tính toán giữa các bước lặp chênh lệch lớn (ví dụ bước lặp chẵn tính lâu hơn bước lặp lẻ), giúp cân bằng tải (Load Balancing) tốt hơn nhưng có thêm overhead quản lý hàng đợi.
  - `guided`: Khởi đầu với kích thước chunk lớn để giảm overhead, sau đó giảm dần kích thước chunk về cuối để cân bằng tải tốt nhất.

---

## III. BÀI TOÁN TÍNH SỐ PI BẰNG PHƯƠNG PHÁP TÍCH PHÂN SỐ (RIEMANN SUM)

### 1. Cơ sở toán học
Ta có tích phân giải tích:
$$\int_{0}^{1} \frac{4}{1 + x^2} dx = 4 \cdot \arctan(1) = \pi$$

Xấp xỉ bằng công thức hình chữ nhật trung điểm (Riemann Sum) chia đoạn $[0, 1]$ thành $N$ khoảng nhỏ, độ rộng mỗi khoảng $\Delta x = \frac{1}{N}$:
$$\pi \approx \frac{1}{N} \sum_{i=1}^{N} \frac{4}{1 + x_i^2} \quad \text{với } x_i = \left(i - 0.5\right) \cdot \Delta x$$

### 2. Mã nguồn tối ưu song song
Sử dụng mệnh đề `reduction(+:sum)` để cộng dồn diện tích các hình chữ nhật một cách an toàn mà không bị race condition:
```c
#pragma omp parallel for reduction(+:sum) private(x)
for (i = 1; i <= num_steps; i++) {
    x = (i - 0.5) * step;
    sum += 4.0 / (1.0 + x * x);
}
pi = step * sum;
```

### 3. Kết quả đo đạc thực nghiệm (Số bước lặp $N = 100.000.000$)
- Thiết bị thử nghiệm: CPU đa nhân (hỗ trợ tối đa 12 logical cores).
- Kết quả chạy trên chương trình `18_pi_integral.exe`:

| Số luồng (Threads) | Giá trị $\pi$ xấp xỉ | Thời gian thực thi (s) | Hệ số tăng tốc ($Speedup = \frac{T_1}{T_p}$) | Hiệu suất ($Efficiency = \frac{S_p}{p}$) |
| :---: | :---: | :---: | :---: | :---: |
| **Tuần tự (Serial)** | 3.141592653590426 | 0.139000 s | 1.00x | 100.0% |
| **1 luồng OpenMP** | 3.141592653590426 | 0.098000 s | 1.42x | 141.8% |
| **2 luồng OpenMP** | 3.141592653589910 | 0.057000 s | 2.44x | 121.9% |
| **4 luồng OpenMP** | 3.141592653589683 | 0.050000 s | 2.78x | 69.5% |
| **8 luồng OpenMP** | 3.141592653589816 | 0.039000 s | 3.56x | 44.6% |
| **12 luồng OpenMP**| 3.141592653589828 | 0.039000 s | 3.56x | 29.7% |

### 4. Đánh giá và Phân tích hiệu năng
1. **Tính chính xác:** Giá trị $\pi$ tính được xấp xỉ tới 11 chữ số thập phân (`3.14159265358...`) khớp với giá trị toán học chuẩn.
2. **Hệ số tăng tốc (Speedup):**
   - Khi tăng số luồng từ 1 lên 2 và 4 luồng, thời gian thực thi giảm rõ rệt (từ 0.139s xuống 0.050s).
   - Tốc độ tăng tốc đạt đỉnh ở 8 - 12 luồng với $Speedup \approx 3.56\times$.
3. **Hiện tượng bão hòa hiệu năng:**
   - Khi vượt quá số nhân vật lý thực của CPU (từ 8 lên 12 luồng ảo Hyper-Threading), thời gian không giảm thêm đáng kể (giữ ở 0.039s). Nguyên nhân do chi phí quản lý luồng (thread creation & scheduling overhead) và giới hạn băng thông truy xuất bộ nhớ (Memory Bandwidth Bottleneck) theo định luật Amdahl.

---

## IV. KẾT LUẬN
- Bài thực hành đã giúp nắm vững cách thiết lập môi trường lập trình song song OpenMP trên cả Visual Studio và GCC.
- Hiểu rõ cơ chế phân chia công việc, đồng bộ hoá dữ liệu, tránh race condition và tối ưu hóa thời gian thực thi thuật toán trên kiến trúc CPU đa nhân.
