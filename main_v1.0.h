/**
 * @file       cbuffer.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date
 * @author     Triet Luu
 * @brief      Circular Buffer
 *             This Circular Buffer is safe to use in IRQ with single reader,
 *             single writer. No need to disable any IRQ.
 *
 *             Capacity = <size> - 1
 * @note       None
 * @example    cbuffer_t cb;
 *             uint8_t cb_buff[6];
 *             uint8_t a;
 *             void main(void)
 *             {
 *                 cb_init(&cb, cb_buff, 100);
 *                 cb_clear(&cb);
 *                 char a[] = {0, 1, 2, 3, 4};
 * 
 *                 int c = 5;
 *                 cb_write(&cb, a, 5);
 *                 char b[5];
 *                 cb_read(&cb, a, 5);
 *             }
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __CBUFFER_H
#define __CBUFFER_H

/* Includes ----------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
// #include "cmsis_compiler.h"

/* Public defines ----------------------------------------------------- */
#define CB_MAX_SIZE (0x00800000)

/* Public enumerate/structure ----------------------------------------- */
typedef struct
{
    uint8_t *data;
    uint32_t size;
    uint32_t writer;
    uint32_t reader;
    uint32_t overflow;
    bool active;
} cbuffer_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/**
 * @brief  cb_init requires input consisting of a circular buffer structure (cbuffer_t), 
 *         pointer toamemory-allocated buffer (buf), and the size of the circular buffer (size).
 *         In the initialization process, the circular buffer will be marked as “active”,
 *         allowing the writeoperation to start at the first position of the buffer (head).
 *
 * @param[in]    cb      Circular Buffer Structure pointer
 * @param[in]    buf     Data Buffer pointer
 * @param[in]    size    Size of the Circular Buffer
 *
 * @attention  All Cbuffer must be initialized before any kind of action involved that certainbuffer.
 *
 * @return  
 *  - Nothing: Success\n
 * @return 
 *  - Invalid parameters!!!: cb or buf is NULL
 * @return 
 *  - Invalid size!!!: size is 0, greater than CB_MAX_SIZE or less than or equal to buf
 */
void cb_init(cbuffer_t *cb, void *buf, uint32_t size);
/**
 * @brief  Reset Cbuffer’s reader, writer, and overflow counter, technically,
 *         ignore and allowoverwrite of all currently valid data in Cbuffer.
 * @param[in]    cb      Circular Buffer Structure pointer
 * @return  
 *  - Nothing: Success
 */
void cb_clear(cbuffer_t *cb);
/**
 * @brief  Read "nbytes" of data from circular buffer into external buffer
 *
 * @param cb: Circular Buffer struct
 * @param buf: External Buffer with data
 * @param nbytes: Numbers of data in buf
 *
 * @return uint32_t The number of bytes successfully read from the circular buffer.
 */
uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes);

/**
 * @brief Write “n_byte” number of data from “buf” and store it in cbuffer. The actual written
bytes will be returned
 *
 * @param cb: Circular Buffer struct
 * @param buf: External Buffer with data
 * @param nbytes: Numbers of data in buf
 *
 * @return uint32_t The number of bytes successfully written to the circular buffer.
 */
uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes);
uint32_t cb_data_count(cbuffer_t *cb);
uint32_t cb_space_count(cbuffer_t *cb);
#endif                     // __CBUFFER_H

/* End of file -------------------------------------------------------- */
