/**
 * @file       example.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    1.0.0
 * @date       2025-07-21
 * @author     Bach Pham
 * @author     Chinh Nguyen
 * @author     Tai Tran
 * @author     Phuong Mai       
 * @brief      Test circular buffer with numeric macro selection
 *             
 * @note       Change #define TESTCASE to choose test
 * @example    example_file.c
 *             TESTCASE = 1..10 for different test cases
 */

/* Includes ----------------------------------------------------------- */
#include "main_v1.0.c"

/* Private defines ---------------------------------------------------- */
#define TESTCASE_GENERAL 
// #define TESTCASE_2 
// #define TESTCASE_1 
// #define TESTCASE_2
//#define TESTCASE_3 
#define TESTCASE_4

/* Public variables --------------------------------------------------- */

/* --- TEST CASE 1 ---------------------------------------------------- */
#define TESTCASE_GENERAL

#ifdef TESTCASE_GENERAL
cbuffer_t cb;
uint8_t cb_buff[10] = {0};
uint8_t a;

void run_testcase_general(void)
{
    printf("==== RUNNING TESTCASE GENERAL ====\n");
    printf("Size buffer: %d\n", sizeof(cb_buff));
    cb_init(&cb, cb_buff, sizeof(cb_buff));
    cb_clear(&cb);
    printf("Data in Buffer:\n");
    for (int i = 0; i < sizeof(cb_buff); i++) {
        printf("%d ", cb.data[i]);
    }
    printf("\n");
    printf("---------------------------------\n");
    // 1. Ghi/Đọc dữ liệu lần 1
    char a1[] = {10, 11, 12, 13, 14};
    cb_write(&cb, a1, sizeof(a1));
    printf("Wrote 5 bytes: {10..14}\n");

    printf("data count: %d| space count: %d| overflow: %d\n",
         cb_data_count(&cb),cb_space_count(&cb),cb.overflow);

    char b1[5] = {0};
    cb_read(&cb, b1, sizeof(b1));
    printf("Read 5 bytes store to b1:\n");
    for (int i = 0; i < sizeof(b1); i++) {
        printf("%d ", b1[i]);
    }
    printf("\n");
    printf("Data in Buffer:\n");
    for (int i = 0; i < sizeof(cb_buff); i++) {
        printf("%d ", cb.data[i]);
    }
    printf("\n");
    printf("Writer: %d, Reader: %d\n", cb.writer, cb.reader);
    printf("---------------------------------\n");

    // 2. Ghi/Đọc dữ liệu lần 2: test wrap-around
    char a2[] = {20, 21, 22, 23, 24};
    cb_write(&cb, a2, sizeof(a2));
    printf("Wrote 5 bytes: {20..24} \n");

    printf("data count: %d| space count: %d| overflow: %d\n",
         cb_data_count(&cb),cb_space_count(&cb),cb.overflow);
    char b2[5] = {0};
    cb_read(&cb, b2, sizeof(b2));
    printf("Read 5 bytes store to b2:\n");
    for (int i = 0; i < sizeof(b2); i++) {
        printf("%d ", b2[i]);
    }
    printf("\n");
    printf("Data in Buffer:\n");
    for (int i = 0; i < sizeof(cb_buff); i++) {
        printf("%d ", cb.data[i]);
    }
    printf("\n");
    printf("Writer: %d, Reader: %d\n", cb.writer, cb.reader);
    printf("---------------------------------\n");

    // 2. Ghi/Đọc dữ liệu lần 3
    char a3[] = {30, 31, 32, 33, 34, 35, 36, 37};
    cb_write(&cb, a3, sizeof(a3));
    printf("Wrote 8 bytes: {30..37}\n");

    printf("data count: %d| space count: %d| overflow: %d\n",
         cb_data_count(&cb),cb_space_count(&cb),cb.overflow);
    char b3[10] = {0};
    uint32_t r = cb_read(&cb, b3, sizeof(b3));
    printf("Read 8 bytes store to b3:\n");
    for (int i = 0; i < sizeof(b3); i++) {
        printf("%d ", b3[i]);
    }
    printf("\n");
    printf("Data in Buffer:\n");
    for (int i = 0; i < sizeof(cb_buff); i++) {
        printf("%d ", cb.data[i]);
    }
    printf("\n");

    // 7. In trạng thái con trỏ cuối cùng
    printf("Final Writer: %d, Reader: %d\n", cb.writer, cb.reader);
}
#endif


/* --- TEST CASE 2 ---------------------------------------------------- */
#ifdef TESTCASE_2
void run_testcase_2(void)
{
    printf("==== RUNNING TESTCASE 2 ====\n");

    cb_init(&cb, cb_buff, sizeof(cb_buff));
    cb_clear(&cb);

    char a1[] = {5, 6, 7, 8, 9};
    cb_write(&cb, a1, 5);

    char b1[10] = {0};
    cb_read(&cb, b1, 5);

    for (int i = 0; i < 5; i++)
        printf("b1[%d] = %d\n", i, b1[i]);
}   
#endif

/* --- TEST CASE 3 ---------------------------------------------------- */
#ifdef TESTCASE_3
void run_testcase_3(void)
{
    printf("==== RUNNING TESTCASE 3 ====\n");
    uint8_t raw_buffer[5] = {0};
    cbuffer_t cb;
    cb_init(&cb, raw_buffer, 5);

    // Ghi dữ liệu NULL
    uint32_t written = cb_write(&cb, NULL, 3);

    // Kết quả
    printf("cb_write(NULL, 3 bytes) -> returned: %u\n", written);
    printf("Expected: 0 (nothing written, handled safely)\n");
}   
#endif

/* --- TEST CASE 4 ---------------------------------------------------- */
#ifdef TESTCASE_4
void print_buffer_state(cbuffer_t *cb) {
    printf("  Buffer raw: ");
    for (uint32_t i = 0; i < cb->size; i++) {
        if (i == cb->reader && i == cb->writer) {
            printf("[RW]%3d ", cb->data[i]);
        } else if (i == cb->reader) {
            printf("[R ]%3d ", cb->data[i]);
        } else if (i == cb->writer) {
            printf("[W ]%3d ", cb->data[i]);
        } else {
            printf("     %3d ", cb->data[i]);
        }
    }
    printf("\n");
}

void run_testcase_4() {
    printf("==== RUNNING TESTCASE 4 ====\n");

    uint8_t raw_buffer[6] = {0};
    cbuffer_t cb;
    cb_init(&cb, raw_buffer, 6);

    uint8_t write_val = 1;
    uint8_t read_val = 0;
    uint8_t read_buf[1];

    for (int i = 0; i < 10; i++) {
        // Ghi 1 byte
        cb_write(&cb, &write_val, 1);
        printf("[Cycle %2d] Wrote: %d\n", i + 1, write_val);
        write_val++;

        // Ghi thêm 1 byte nếu còn chỗ
        if (cb_space_count(&cb) > 0) {
            cb_write(&cb, &write_val, 1);
            printf("[Cycle %2d] Wrote: %d\n", i + 1, write_val);
            write_val++;
        }

        // Đọc 1 byte (nếu có dữ liệu)
        if (cb_data_count(&cb) > 0) {
            cb_read(&cb, read_buf, 1);
            read_val = read_buf[0];
            printf("[Cycle %2d] Read : %d\n", i + 1, read_val);
        }

        printf("  [Reader: %u, Writer: %u, Count: %u, Space: %u]\n",
               cb.reader, cb.writer, cb_data_count(&cb), cb_space_count(&cb));
        print_buffer_state(&cb);  // In thêm trạng thái raw buffer
    }

    // Đọc hết phần còn lại
    printf("\nFinal readout of remaining buffer:\n");
    while (cb_data_count(&cb) > 0) {
        cb_read(&cb, read_buf, 1);
        printf("  Read: %d\n", read_buf[0]);
        print_buffer_state(&cb);
    }
}

#endif
/* --- MAIN FUNCTION -------------------------------------------------- */
int main(void)
{
#ifdef TESTCASE_GENERAL
    run_testcase_general();
#endif
#ifdef TESTCASE_2
    run_testcase_2();
#endif
#ifdef TESTCASE_3
    run_testcase_3();
#endif
#ifdef TESTCASE_4
    run_testcase_4();
#endif

    return 0;
}