/**
 * @file    system_stm32f4.c
 * @author  Necdet Sanli (me@necdetsanli.com)
 * @brief   System clock initialization for STM32F4 MCUs.
 *
 * Configures the main clock tree from board-specific parameters defined in
 * board.h: enables HSE, programs the main PLL (M/N/P/Q), sets the AHB/APB
 * bus prescalers, configures Flash wait states with cache and prefetch, and
 * finally switches SYSCLK to the PLL output.
 *
 * The configuration is fully driven by BOARD_* macros and validated at
 * compile time by stm32f4_board_validate.h, so any inconsistency is caught
 * before the binary is produced.
 */

#include "board.h"
#include "stm32f4_rcc_prescalers.h"
#include "stm32f4xx.h"

/* ===== Sanity checks ====================================================== */
#if !defined(BOARD_NAME)
#error "board.h must define BOARD_NAME"
#endif
#if !defined(MCU_NAME)
#error "board.h must include an MCU header that defines MCU_NAME"
#endif

/** PLLP register encoding: human value 2/4/6/8 -> field value 00/01/10/11 */
#define PLLP_REG_VALUE ((BOARD_PLLP / 2U) - 1U)

/**
 * @brief   Initialize the system clock tree.
 *
 * Brings SYSCLK up from the post-reset HSI default to the board-defined
 * target frequency using HSE as the PLL source.
 *
 *   1. Program Flash wait states, caches and prefetch (must be done before
 *      raising the core clock so that instruction fetches do not fail).
 *   2. Enable HSE and wait for HSERDY.
 *   3. Disable the main PLL so that PLLCFGR becomes writable.
 *   4. Program PLLCFGR with the board's M/N/P/Q values, source = HSE.
 *   5. Program the AHB/APB1/APB2 prescalers BEFORE switching SYSCLK,
 *      otherwise the APB buses would momentarily exceed their limits as
 *      SYSCLK jumps to the PLL output.
 *   6. Enable the PLL and wait for PLLRDY (lock).
 *   7. Switch the SYSCLK source to the PLL output.
 *   8. Wait on the SWS field until the switch is observed by hardware.
 *
 * Called from Reset_Handler before main(), after .data/.bss initialization.
 */
void SystemInit(void)
{
    /* 1. Configure Flash: wait states + caches + prefetch BEFORE raising clock */
    FLASH->ACR = (BOARD_FLASH_LATENCY << FLASH_ACR_LATENCY_Pos) | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN;

    /* Read-back to ensure latency is applied before clock change */
    while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (BOARD_FLASH_LATENCY << FLASH_ACR_LATENCY_Pos)) {
        ;
    }

    /* 2. Enable HSE and wait until stable */
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY)) {
        ;
    }

    /* 3. Disable PLL before reconfiguring (PLLCFGR is write-protected when PLL on) */
    RCC->CR &= ~RCC_CR_PLLON;
    while (RCC->CR & RCC_CR_PLLRDY) {
        ;
    }

    /* 4. Configure main PLL: source = HSE, M/N/P/Q from board config */
    RCC->PLLCFGR = ((uint32_t)BOARD_PLLM << RCC_PLLCFGR_PLLM_Pos) | ((uint32_t)BOARD_PLLN << RCC_PLLCFGR_PLLN_Pos) |
                   ((uint32_t)PLLP_REG_VALUE << RCC_PLLCFGR_PLLP_Pos) | ((uint32_t)BOARD_PLLQ << RCC_PLLCFGR_PLLQ_Pos) | RCC_PLLCFGR_PLLSRC_HSE;

    /* 5. Set bus prescalers BEFORE switching SYSCLK to PLL,
     *    otherwise APB1/APB2 would momentarily exceed their limits. */
    RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_HPRE_Msk | RCC_CFGR_PPRE1_Msk | RCC_CFGR_PPRE2_Msk)) | BOARD_AHB_PRESCALER_REG | BOARD_APB1_PRESCALER_REG |
                BOARD_APB2_PRESCALER_REG;

    /* 6. Enable PLL and wait for lock */
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY)) {
        ;
    }

    /* 7. Switch SYSCLK source to PLL */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW_Msk) | RCC_CFGR_SW_PLL;

    /* 8. Wait until SYSCLK is actually driven by PLL (SWS field) */
    while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL) {
        ;
    }
}
