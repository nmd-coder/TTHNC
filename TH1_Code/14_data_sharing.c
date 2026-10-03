// 14_data_sharing.c - So sánh private, firstprivate, lastprivate, shared
#include <stdio.h>
#include <omp.h>

int main() {
    int val_shared = 10;
    int val_private = 20;
    int val_firstprivate = 30;
    int val_lastprivate = 0;

    printf("Gia tri TRUOC vung song song:\n");
    printf("  val_shared = %d\n", val_shared);
    printf("  val_private = %d\n", val_private);
    printf("  val_firstprivate = %d\n", val_firstprivate);
    printf("  val_lastprivate = %d\n\n", val_lastprivate);

    #pragma omp parallel for num_threads(3) \
        shared(val_shared) \
        private(val_private) \
        firstprivate(val_firstprivate) \
        lastprivate(val_lastprivate)
    for (int i = 0; i < 6; i++) {
        int id = omp_get_thread_num();

        // val_private: Biến mới, chưa được gán giá trị từ ngoài (rác hoặc cần gán)
        val_private = id * 100;

        // val_firstprivate: Đã kế thừa giá trị 30 từ trước khi vào vùng song song
        val_firstprivate += id;

        // val_lastprivate: Nhận giá trị được tính ở bước lặp cuối cùng (i = 5)
        val_lastprivate = i * 10;

        printf("  [Thread %d | i=%d] priv=%d, firstpriv=%d, lastpriv=%d\n",
               id, i, val_private, val_firstprivate, val_lastprivate);
    }

    printf("\nGia tri SAU vung song song:\n");
    printf("  val_shared = %d (dung chung giua cac thread)\n", val_shared);
    printf("  val_private = %d (khong doi so voi truoc khi vao)\n", val_private);
    printf("  val_firstprivate = %d (khong thay doi ngoai vung song song)\n", val_firstprivate);
    printf("  val_lastprivate = %d (nhan gia tri o buoc lap cuoi cung i=5)\n", val_lastprivate);

    return 0;
}
