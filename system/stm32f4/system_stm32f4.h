/**
 * @file    system_stm32f4.h
 * @author  Necdet Sanli (me@necdetsanli.com)
 * @brief   Public interface for STM32F4 system initialization.
 */

#ifndef SYSTEM_STM32F4_H
#define SYSTEM_STM32F4_H

/**
 * @brief   Initialize the system clock tree from board configuration.
 *
 * Called from Reset_Handler before main(), after .data/.bss initialization.
 * See system_stm32f4.c for the full clock bring-up sequence.
 */
void SystemInit(void);

#endif /* SYSTEM_STM32F4_H */
