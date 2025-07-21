/**
 * @file       cbuffer.c
 * @copyright  
 * @license    
 * @version    1.0.0
 * @date       2025-07-21
 * @author     Bach Pham
 * @author     Chinh Nguyen
 * @author     Tai Tran
 * @author     Phuong Mai   
 * @brief      This file include the init function and clear function for cbuffer
 *
 * @note       None
 * @example    cbuffer_t cb;
 *             uint8_t cb_buff[6];
 *             uint8_t a;
 *             void main(void)
 *             {
 *                 cb_init(&cb, cb_buff, 100);
 *                 cb_clear(&cb);
 *             }
 */

/* Includes ----------------------------------------------------------- */
#include "cbuffer.h"
//#include "code_template.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
uint32_t cb_data_count(cbuffer_t *cb)
{
    if(cb->reader <= cb->writer)
    {
      return cb->writer - cb->reader;
    } else {
      return cb->size + cb->writer - cb->reader;
    }
}

uint32_t cb_space_count(cbuffer_t *cb)
{
    return cb->size - cb_data_count(cb) -1;
}
/* Private definitions ----------------------------------------------- */
/* End of file -------------------------------------------------------- */
