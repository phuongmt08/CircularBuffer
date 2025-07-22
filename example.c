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
// #define TESTCASE_1 
// #define TESTCASE_2
//#define TESTCASE_3 
#define TESTCASE_4

/* Public variables --------------------------------------------------- */
cbuffer_t cb;
uint8_t cb_buff[10];
uint8_t a;
/* --- TEST CASE 1 ---------------------------------------------------- */
#ifdef TESTCASE_1
void run_testcase_1(void)
{
    printf("==== RUNNING TESTCASE 1 ====\n");

    cb_init(&cb, cb_buff, sizeof(cb_buff));
    cb_clear(&cb);

    char a1[] = {0, 1, 2, 3, 4};
    cb_write(&cb, a1, 5);

    printf("Writer: %d Reader: %d\n", cb.writer, cb.reader);

    char b1[10] = {0};
    cb_read(&cb, b1, 5);
    for (int i = 0; i < 5; i++)
        printf("b1[%d] = %d\n", i, b1[i]);

    printf("Writer: %d Reader: %d\n", cb.writer, cb.reader);
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
#ifdef TESTCASE_1
    run_testcase_1();
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