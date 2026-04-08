/**
 * @file    stm32f4_board_validate.h
 * @author  Necdet Sanli (me@necdetsanli.com)
 * @brief   Compile-time validation of STM32F4 board clock configuration.
 *
 * This header is included at the end of every STM32F4 board configuration
 * file. It cross-checks the user-selected BOARD_* clock parameters against
 * the MCU hardware limits exposed by the chip header (MCU_*), and against
 * the fixed RCC register field encodings of the STM32F4 family.
 *
 * Any inconsistency (out-of-range value, mismatched math, illegal prescaler,
 * insufficient flash latency) raises a #error at preprocessing time, so a
 * misconfigured board can never reach the silicon.
 *
 * @note This file must not be included directly. It is pulled in by the
 *       board header after all BOARD_* macros and the chip header are
 *       defined.
 */

#ifndef STM32F4_BOARD_VALIDATE_H
#define STM32F4_BOARD_VALIDATE_H

#ifndef BOARD_NAME
#if defined(__INTELLISENSE__)
/* IntelliSense standalone parse — silently skip */
#else
#error "stm32f4_board_validate.h must be included from a board header"
#endif /* __INTELLISENSE__ */
#else

/* ===== HSE oscillator ===================================================== */
#if (BOARD_HSE_FREQ < MCU_HSE_MIN) || (BOARD_HSE_FREQ > MCU_HSE_MAX)
#error "BOARD_HSE_FREQ out of MCU range"
#endif

/* ===== Main PLL: input divider (PLLM) ===================================== */
#if (BOARD_PLLM < MCU_PLLM_MIN) || (BOARD_PLLM > MCU_PLLM_MAX)
#error "BOARD_PLLM out of MCU range"
#endif
#if ((BOARD_HSE_FREQ / BOARD_PLLM) < MCU_VCO_IN_MIN) || ((BOARD_HSE_FREQ / BOARD_PLLM) > MCU_VCO_IN_MAX)
#error "PLL input frequency (HSE/PLLM) out of MCU range"
#endif

/* ===== Main PLL: multiplier (PLLN) and VCO output ========================= */
#if (BOARD_PLLN < MCU_PLLN_MIN) || (BOARD_PLLN > MCU_PLLN_MAX)
#error "BOARD_PLLN out of MCU range"
#endif
#if (((BOARD_HSE_FREQ / BOARD_PLLM) * BOARD_PLLN) < MCU_VCO_OUT_MIN) || (((BOARD_HSE_FREQ / BOARD_PLLM) * BOARD_PLLN) > MCU_VCO_OUT_MAX)
#error "PLL VCO output out of MCU range"
#endif

/* ===== Main PLL: system clock divider (PLLP), RCC_PLLCFGR enum ============ */
#if (BOARD_PLLP != 2) && (BOARD_PLLP != 4) && (BOARD_PLLP != 6) && (BOARD_PLLP != 8)
#error "BOARD_PLLP must be 2, 4, 6, or 8"
#endif

/* ===== Main PLL: USB/SDIO/RNG divider (PLLQ) ============================== */
#if (BOARD_PLLQ < MCU_PLLQ_MIN) || (BOARD_PLLQ > MCU_PLLQ_MAX)
#error "BOARD_PLLQ out of MCU range"
#endif

/* ===== System clock ======================================================= */
#if (BOARD_SYSCLK_FREQ > MCU_SYSCLK_MAX)
#error "BOARD_SYSCLK_FREQ exceeds MCU max"
#endif
#if BOARD_SYSCLK_FREQ != (((BOARD_HSE_FREQ / BOARD_PLLM) * BOARD_PLLN) / BOARD_PLLP)
#error "BOARD_SYSCLK_FREQ does not match (HSE/PLLM*PLLN)/PLLP"
#endif

/* ===== AHB prescaler, RCC_CFGR HPRE enum ================================== */
#if (BOARD_AHB_PRESCALER != 1) && (BOARD_AHB_PRESCALER != 2) && (BOARD_AHB_PRESCALER != 4) && (BOARD_AHB_PRESCALER != 8) && (BOARD_AHB_PRESCALER != 16) &&     \
    (BOARD_AHB_PRESCALER != 64) && (BOARD_AHB_PRESCALER != 128) && (BOARD_AHB_PRESCALER != 256) && (BOARD_AHB_PRESCALER != 512)
#error "BOARD_AHB_PRESCALER invalid (1,2,4,8,16,64,128,256,512)"
#endif

/* ===== APB1/APB2 prescalers, RCC_CFGR PPRE1/PPRE2 enums =================== */
#if (BOARD_APB1_PRESCALER != 1) && (BOARD_APB1_PRESCALER != 2) && (BOARD_APB1_PRESCALER != 4) && (BOARD_APB1_PRESCALER != 8) && (BOARD_APB1_PRESCALER != 16)
#error "BOARD_APB1_PRESCALER invalid (1,2,4,8,16)"
#endif
#if (BOARD_APB2_PRESCALER != 1) && (BOARD_APB2_PRESCALER != 2) && (BOARD_APB2_PRESCALER != 4) && (BOARD_APB2_PRESCALER != 8) && (BOARD_APB2_PRESCALER != 16)
#error "BOARD_APB2_PRESCALER invalid (1,2,4,8,16)"
#endif

/* ===== Bus frequencies: math consistency and MCU limits =================== */
#if BOARD_HCLK_FREQ != (BOARD_SYSCLK_FREQ / BOARD_AHB_PRESCALER)
#error "BOARD_HCLK_FREQ does not match SYSCLK/AHB_PRESCALER"
#endif

#if BOARD_APB1_FREQ != (BOARD_HCLK_FREQ / BOARD_APB1_PRESCALER)
#error "BOARD_APB1_FREQ does not match HCLK/APB1_PRESCALER"
#endif
#if (BOARD_APB1_FREQ > MCU_APB1_MAX)
#error "BOARD_APB1_FREQ exceeds MCU max"
#endif

#if BOARD_APB2_FREQ != (BOARD_HCLK_FREQ / BOARD_APB2_PRESCALER)
#error "BOARD_APB2_FREQ does not match HCLK/APB2_PRESCALER"
#endif
#if (BOARD_APB2_FREQ > MCU_APB2_MAX)
#error "BOARD_APB2_FREQ exceeds MCU max"
#endif

/* ===== Flash wait states (depends on HCLK and supply voltage) ============= */
#if (BOARD_FLASH_LATENCY > 7)
#error "BOARD_FLASH_LATENCY out of range (0-7)"
#endif
#if (BOARD_HCLK_FREQ > MCU_FLASH_WS3_HCLK) && (BOARD_FLASH_LATENCY < 3)
#error "Flash latency too low (need 3 WS)"
#endif
#if (BOARD_HCLK_FREQ > MCU_FLASH_WS2_HCLK) && (BOARD_FLASH_LATENCY < 2)
#error "Flash latency too low (need 2 WS)"
#endif
#if (BOARD_HCLK_FREQ > MCU_FLASH_WS1_HCLK) && (BOARD_FLASH_LATENCY < 1)
#error "Flash latency too low (need 1 WS)"
#endif

#endif /* BOARD_NAME */

#endif /* STM32F4_BOARD_VALIDATE_H */
