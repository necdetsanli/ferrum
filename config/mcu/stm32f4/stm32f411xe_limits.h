/**
 * @file    stm32f411xe_limits.h
 * @author Necdet Sanli (me@necdetsanli.com)
 * @brief   Hardware limits for STM32F411xE MCU.
 *
 * Chip-level constants derived from the official datasheet and reference
 * manual. These values describe the physical limits of the silicon and
 * MUST NOT be modified by users. Board headers reference these limits
 * to validate user-selected clock configurations at compile time.
 */

#ifndef STM32F411XE_LIMITS_H
#define STM32F411XE_LIMITS_H

/* ===== MCU identification string ================ */
#define MCU_NAME "STM32F411xE"

/* ===== Memory sizes =================================== */
#define MCU_FLASH_SIZE 0x80000 /*  512 KB  Flash   */
#define MCU_RAM_SIZE   0x20000 /*  128 KB SRAM  */

/* ===== Clock tree limits =========== */
#define MCU_SYSCLK_MAX 100000000U /*   Max SYSCLK/HCLK/AHB frequency  */
#define MCU_APB1_MAX   50000000U  /*   Max APB1 frequency  */
#define MCU_APB2_MAX   100000000U /*   Max APB2 frequency  */

/* ===== HSE oscillator ================================== */
#define MCU_HSE_MIN 4000000U  /*    Min external crystal frequency */
#define MCU_HSE_MAX 26000000U /*    Max external crystal frequency  */

/* ===== Main PLL limits ================ */
#define MCU_PLLM_MIN    2          /*   Min PLLM division factor   */
#define MCU_PLLM_MAX    63         /*   Max PLLM division factor    */
#define MCU_PLLN_MIN    50         /*   Min PLLN multiplication factor  */
#define MCU_PLLN_MAX    432        /*   Max PLLN multiplication factor  */
#define MCU_PLLQ_MIN    2U         /*   Min PLLQ  division factor    */
#define MCU_PLLQ_MAX    15U        /*   Max PLLQ division factor    */
#define MCU_VCO_IN_MIN  1000000U   /*   Min PLL input frequency (HSE/PLLM)  */
#define MCU_VCO_IN_MAX  2000000U   /*   Max PLL input frequency (HSE/PLLM)  */
#define MCU_VCO_OUT_MIN 100000000U /*   Min PLL VCO output frequency    */
#define MCU_VCO_OUT_MAX 432000000U /*   Max PLL VCO output frequency    */

/* ===== Flash wait states ================ */
/* HCLK ≤ 30 MHz: 0 WS  */
/* HCLK ≤ 60 MHz: 1 WS  */
/* HCLK ≤ 90 MHz: 2 WS  */
/* HCLK ≤ 100 MHz: 3 WS */
#define MCU_FLASH_WS1_HCLK 30000000U /* HCLK threshold above which 1 WS required    */
#define MCU_FLASH_WS2_HCLK 60000000U /* HCLK threshold above which 2 WS required    */
#define MCU_FLASH_WS3_HCLK 90000000U /* HCLK threshold above which 3 WS required    */

#endif /*   STM32F411XE_LIMITS_H   */
