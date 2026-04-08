/**
 * @file    blackpill_f411ce.h
 * @author  Necdet Sanli (me@necdetsanli.com)
 * @brief   Board configuration for the WeAct BlackPill STM32F411CE.
 *
 * Defines the physical characteristics of the board (HSE crystal frequency)
 * and the user-selected clock tree configuration (PLL parameters, bus
 * prescalers, flash wait states). All values are validated at compile time
 * against the MCU limits defined in the included chip header.
 */

#ifndef BLACKPILL_F411CE_H
#define BLACKPILL_F411CE_H

#include "stm32f411xe_limits.h"

/* ===== Board identification string ================ */
#define BOARD_NAME "blackpill_f411ce"

/* ===== HSE oscillator ================================== */
#define BOARD_HSE_FREQ 25000000U /* High-speed external oscillator frequency  */

/* ===== Main PLL settings ================ */
#define BOARD_PLLM 25  /*  Main PLL input division factor   */
#define BOARD_PLLN 200 /*  Main PLL multiplication factor   */
#define BOARD_PLLP 2   /*  Main PLL division factor for main system clock   */
#define BOARD_PLLQ 4   /*  Main PLL division factor for USB, SDIO and RNG  */

/* ===== Clock tree frequencies =========== */
#define BOARD_SYSCLK_FREQ 100000000U /* SYSCLK target frequency  */
#define BOARD_HCLK_FREQ   100000000U /* AHB bus clock freqeuncy  */
#define BOARD_APB1_FREQ   50000000U  /*  APB1 bus frequency   */
#define BOARD_APB2_FREQ   100000000U /*  APB2 bus frequency   */

/* ===== Prescalers ================ */
#define BOARD_AHB_PRESCALER  1 /*  AHB prescaler   */
#define BOARD_APB1_PRESCALER 2 /*  APB1 prescaler  */
#define BOARD_APB2_PRESCALER 1 /*  APB2 prescaler  */

/* ===== Flash wait state ================ */
#define BOARD_FLASH_LATENCY 3 /*  Flash wait states for 100 MHz at 3.3V   */

#include "stm32f4_board_validate.h"

#endif /*   BLACKPILL_F411CE_H  */
