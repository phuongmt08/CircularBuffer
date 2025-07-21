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
#include "main_v1.0.h"
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

uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
  // Kiểm tra thông số đầu vào hợp lệ
  if (cb == NULL || buf == NULL || nbytes == 0 || cb->active == false)
    return 0;

  // Ép kiểu con trỏ buf và khởi tạo biến đếm 
  uint8_t *data = (uint8_t *)buf;
  uint32_t bytes_written = 0;

  // Ghi cho đến hết dữ liệu hoặc buffer đầy
  while ((bytes_written < nbytes) && (cb_space_count(cb) > 0))
  {
    // Ghi 1 byte dữ liệu; tăng biến đếm writter và biến đếm byte đã ghi
    cb->data[cb->writer] = data[bytes_written];
    cb->writer = (cb->writer + 1) % cb->size;
    bytes_written++;
  }
  
  // Nếu ghi chưa đủ thì có tràn
  if (bytes_written < nbytes)
  {
    cb->overflow += nbytes - bytes_written; 
  }
  
  return bytes_written;
}
uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
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
