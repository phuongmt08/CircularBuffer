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
void cb_init(cbuffer_t *cb, void *buf, uint32_t size)
{
  if (cb == NULL || buf == NULL || size == 0 || size > CB_MAX_SIZE)
    {
      return;
    }
    
  cb->data = (uint8_t *)buf;
  cb->size = size;
  cb->writer = 0;
  cb->reader = 0;
  cb->overflow = 0;
  cb->active = 1;
}

void cb_clear(cbuffer_t *cb)
{
  if (cb->active == 0)  // check if cb active
  {
    return;
  }
  else 
    {
      if (cb == NULL)  // check if cb pointer valid 
        {
          return;
        }
    
      cb->writer = 0;
      cb->reader = 0;
      cb->overflow = 0;
      }
}

/* Private definitions ----------------------------------------------- */
/* End of file -------------------------------------------------------- */
