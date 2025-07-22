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
#define TESTCASE_1 
#define TESTCASE_2 

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