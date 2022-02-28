/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    13-April-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include <stdio.h>
#include <string.h>
//#include "sim900a.h"
#define MAX_STRLEN  99 
extern  char  buf[MAX_STRLEN+1];
char m=0;

void Delay(__IO uint32_t nCount);
void USART_SendString(USART_TypeDef* USARTx, char*string);
void USART_SendChar(USART_TypeDef* USARTx, u8 data);
char check_string(char *string);
void chop_tat(void);


unsigned char ReadStringUART(unsigned char *Dest, unsigned char BufferLen);
//void Delay(__IO uint32_t nCount) {
//  while(nCount--) {
//  }
//}



void USART1_IRQHandler(void){

	// check if the USART1 receive interrupt flag was set
	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){

		static uint8_t cnt = 0; // this counter is used to determine the string length
		char t = USART1->DR; // the character from the USART1 data register is saved in t

		/* check if the received character is not the LF character (used to determine end of string)
		 * or the if the maximum string length has been been reached
		 */
		if( (t !='K') && (cnt < MAX_STRLEN) ){
		buf[cnt] = t;
			cnt++;
		}
		else{ // otherwise reset the character counter and print the received string
			buf[cnt]='K';
			cnt = 0;
 USART_SendString(USART1,buf);
		}
	}
}