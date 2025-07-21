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
uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes){
    uint32_t cnt = 0;
  if(!cb->active)
  {
    printf("chua active\n");
    return 0;
  }
  if(nbytes == 0 || nbytes < CB_MAX_SIZE)
  {
    printf("du lieu doc qua lon\n");
    return 0;
  }
  
  uint8_t *bufR = (uint8_t *)buf;
  while(cnt < nbytes)
  {
    if (cb->reader == (cb->writer - 1))
    {
        break;
    } 
    // gan du lieu cho bufR
    bufR[cb->reader] = cb->data[cb->reader];   
    // tang reader va cnt        
    cb->reader = (cb->reader + 1) % cb->size;     
    cnt++;
  }
return cnt;
}
/* Private definitions ----------------------------------------------- */
/* End of file -------------------------------------------------------- */
