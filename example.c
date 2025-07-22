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
#include "main_v1.0.h"

/* Private defines ---------------------------------------------------- */
#define TESTCASE_GENERAL 
// #define TESTCASE_2 

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