/**
 * @file    stm32f4_rcc_prescalers.h
 * @author  Necdet Sanli (me@necdetsanli.com)
 * @brief   STM32F4 RCC prescaler value-to-register encoding.
 *
 * Translates human-readable BOARD_*_PRESCALER values (1, 2, 4, ...) into
 * the corresponding RCC_CFGR field encodings (RCC_CFGR_HPRE_DIVx,
 * RCC_CFGR_PPRE1_DIVx, RCC_CFGR_PPRE2_DIVx) defined by CMSIS.
 *
 * The encoding is fixed across the entire STM32F4 family (RM0383 Table 27,
 * and equivalent tables in other F4 reference manuals), so this header is
 * shared by all F4 MCUs.
 *
 * @note Must be included after board.h, so that BOARD_*_PRESCALER macros
 *       are defined. Validation of the prescaler values themselves is
 *       performed by stm32f4_board_validate.h.
 */

#ifndef STM32F4_RCC_PRESCALERS_H
#define STM32F4_RCC_PRESCALERS_H

#ifndef BOARD_AHB_PRESCALER
#if defined(__INTELLISENSE__)
/* IntelliSense standalone parse — silently skip */
#else
#error "stm32f4_rcc_prescalers.h must be included after board.h"
#endif
#else

/* ===== AHB prescaler (RCC_CFGR HPRE field) ================================ */
#if BOARD_AHB_PRESCALER == 1
#define BOARD_AHB_PRESCALER_REG RCC_CFGR_HPRE_DIV1
#elif BOARD_AHB_PRESCALER == 2
#define BOARD_AHB_PRESCALER_REG RCC_CFGR_HPRE_DIV2
#elif BOARD_AHB_PRESCALER == 4
#define BOARD_AHB_PRESCALER_REG RCC_CFGR_HPRE_DIV4
#elif BOARD_AHB_PRESCALER == 8
#define BOARD_AHB_PRESCALER_REG RCC_CFGR_HPRE_DIV8
#elif BOARD_AHB_PRESCALER == 16
#define BOARD_AHB_PRESCALER_REG RCC_CFGR_HPRE_DIV16
#elif BOARD_AHB_PRESCALER == 64
#define BOARD_AHB_PRESCALER_REG RCC_CFGR_HPRE_DIV64
#elif BOARD_AHB_PRESCALER == 128
#define BOARD_AHB_PRESCALER_REG RCC_CFGR_HPRE_DIV128
#elif BOARD_AHB_PRESCALER == 256
#define BOARD_AHB_PRESCALER_REG RCC_CFGR_HPRE_DIV256
#elif BOARD_AHB_PRESCALER == 512
#define BOARD_AHB_PRESCALER_REG RCC_CFGR_HPRE_DIV512
#endif

/* ===== APB1 prescaler (RCC_CFGR PPRE1 field) ============================== */
#if BOARD_APB1_PRESCALER == 1
#define BOARD_APB1_PRESCALER_REG RCC_CFGR_PPRE1_DIV1
#elif BOARD_APB1_PRESCALER == 2
#define BOARD_APB1_PRESCALER_REG RCC_CFGR_PPRE1_DIV2
#elif BOARD_APB1_PRESCALER == 4
#define BOARD_APB1_PRESCALER_REG RCC_CFGR_PPRE1_DIV4
#elif BOARD_APB1_PRESCALER == 8
#define BOARD_APB1_PRESCALER_REG RCC_CFGR_PPRE1_DIV8
#elif BOARD_APB1_PRESCALER == 16
#define BOARD_APB1_PRESCALER_REG RCC_CFGR_PPRE1_DIV16
#endif

/* ===== APB2 prescaler (RCC_CFGR PPRE2 field) ============================== */
#if BOARD_APB2_PRESCALER == 1
#define BOARD_APB2_PRESCALER_REG RCC_CFGR_PPRE2_DIV1
#elif BOARD_APB2_PRESCALER == 2
#define BOARD_APB2_PRESCALER_REG RCC_CFGR_PPRE2_DIV2
#elif BOARD_APB2_PRESCALER == 4
#define BOARD_APB2_PRESCALER_REG RCC_CFGR_PPRE2_DIV4
#elif BOARD_APB2_PRESCALER == 8
#define BOARD_APB2_PRESCALER_REG RCC_CFGR_PPRE2_DIV8
#elif BOARD_APB2_PRESCALER == 16
#define BOARD_APB2_PRESCALER_REG RCC_CFGR_PPRE2_DIV16
#endif

#endif /* BOARD_AHB_PRESCALER */

#endif /* STM32F4_RCC_PRESCALERS_H */
