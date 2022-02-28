#ifndef __REPRINTF_H
#define __REPRINTF_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f4xx.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#ifdef __cplusplus
}
#endif
#endif /* __REPRINTF_H */
