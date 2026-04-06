/**
 * @file startup_stm32f4.c
 * @author Necdet Sanli (me@necdetsanli.com)
 * @brief Startup code for STM32F4 written in C. Includes vector table and default handlers.
 * @version 0.1
 * @date 2026-04-06
 */

#include <stdint.h>

typedef void (*ISRHandler)(void);

#define RESERVED_SLOT ((ISRHandler)0)

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);

__attribute__((weak)) void Default_Handler(void)
{
    while (1) {
        ;
    }
}

/* Cortex-M4 System Exceptions */
__attribute__((weak, alias("Default_Handler"))) void NMI_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void HardFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void MemManage_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void BusFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void UsageFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SVC_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void DebugMon_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void PendSV_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SysTick_Handler(void);

/* STM32F4 Peripheral Interrupts used by STM32F411 mapping */
__attribute__((weak, alias("Default_Handler"))) void WWDG_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void PVD_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TAMP_STAMP_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void RTC_WKUP_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void FLASH_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void RCC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI0_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream0_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream6_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void ADC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI9_5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_BRK_TIM9_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_UP_TIM10_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_TRG_COM_TIM11_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM1_CC_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C1_EV_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C1_ER_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C2_EV_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C2_ER_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SPI1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SPI2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USART1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USART2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void EXTI15_10_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void RTC_Alarm_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void OTG_FS_WKUP_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream7_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SDIO_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void TIM5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SPI3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream0_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream1_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream2_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream3_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream4_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void OTG_FS_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream5_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream6_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream7_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void USART6_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C3_EV_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void I2C3_ER_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void FPU_IRQHandler(void);
__attribute__((weak, alias("Default_Handler"))) void SPI4_IRQHandler(void);
#if defined(STM32F411xx)
__attribute__((weak, alias("Default_Handler"))) void SPI5_IRQHandler(void);
#endif

__attribute__((noreturn)) void Reset_Handler(void)
{
    uint32_t *src = (uint32_t *)&_sidata;
    uint32_t *dst = (uint32_t *)&_sdata;
    uint32_t *dst_end = (uint32_t *)&_edata;
    uint32_t *bss_start = (uint32_t *)&_sbss;
    uint32_t *bss_end = (uint32_t *)&_ebss;

    while (dst < dst_end) {
        *dst++ = *src++;
    }

    while (bss_start < bss_end) {
        *bss_start++ = 0;
    }

    main();

    while (1) {
        ;
    }
}

__attribute__((section(".isr_vector"), used)) ISRHandler isr_vector_table[] = {
    (ISRHandler)&_estack, /* 0  - Initial stack pointer */
    Reset_Handler,        /* 1  - Reset */
    NMI_Handler,          /* 2  - NMI */
    HardFault_Handler,    /* 3  - HardFault */
    MemManage_Handler,    /* 4  - MemManage */
    BusFault_Handler,     /* 5  - BusFault */
    UsageFault_Handler,   /* 6  - UsageFault */
    RESERVED_SLOT,        /* 7  - Reserved */
    RESERVED_SLOT,        /* 8  - Reserved */
    RESERVED_SLOT,        /* 9  - Reserved */
    RESERVED_SLOT,        /* 10 - Reserved */
    SVC_Handler,          /* 11 - SVCall */
    DebugMon_Handler,     /* 12 - Debug monitor */
    RESERVED_SLOT,        /* 13 - Reserved */
    PendSV_Handler,       /* 14 - PendSV */
    SysTick_Handler,      /* 15 - SysTick */

    /* External Interrupts (IRQ 0..81), STM32 startup .s order */
    WWDG_IRQHandler,               /* 0  */
    PVD_IRQHandler,                /* 1  */
    TAMP_STAMP_IRQHandler,         /* 2  */
    RTC_WKUP_IRQHandler,           /* 3  */
    FLASH_IRQHandler,              /* 4  */
    RCC_IRQHandler,                /* 5  */
    EXTI0_IRQHandler,              /* 6  */
    EXTI1_IRQHandler,              /* 7  */
    EXTI2_IRQHandler,              /* 8  */
    EXTI3_IRQHandler,              /* 9  */
    EXTI4_IRQHandler,              /* 10 */
    DMA1_Stream0_IRQHandler,       /* 11 */
    DMA1_Stream1_IRQHandler,       /* 12 */
    DMA1_Stream2_IRQHandler,       /* 13 */
    DMA1_Stream3_IRQHandler,       /* 14 */
    DMA1_Stream4_IRQHandler,       /* 15 */
    DMA1_Stream5_IRQHandler,       /* 16 */
    DMA1_Stream6_IRQHandler,       /* 17 */
    ADC_IRQHandler,                /* 18 */
    RESERVED_SLOT,                 /* 19 - CAN1_TX (reserved on F411) */
    RESERVED_SLOT,                 /* 20 - CAN1_RX0 (reserved on F411) */
    RESERVED_SLOT,                 /* 21 - CAN1_RX1 (reserved on F411) */
    RESERVED_SLOT,                 /* 22 - CAN1_SCE (reserved on F411) */
    EXTI9_5_IRQHandler,            /* 23 */
    TIM1_BRK_TIM9_IRQHandler,      /* 24 */
    TIM1_UP_TIM10_IRQHandler,      /* 25 */
    TIM1_TRG_COM_TIM11_IRQHandler, /* 26 */
    TIM1_CC_IRQHandler,            /* 27 */
    TIM2_IRQHandler,               /* 28 */
    TIM3_IRQHandler,               /* 29 */
    TIM4_IRQHandler,               /* 30 */
    I2C1_EV_IRQHandler,            /* 31 */
    I2C1_ER_IRQHandler,            /* 32 */
    I2C2_EV_IRQHandler,            /* 33 */
    I2C2_ER_IRQHandler,            /* 34 */
    SPI1_IRQHandler,               /* 35 */
    SPI2_IRQHandler,               /* 36 */
    USART1_IRQHandler,             /* 37 */
    USART2_IRQHandler,             /* 38 */
    RESERVED_SLOT,                 /* 39 - USART3 (reserved on F411) */
    EXTI15_10_IRQHandler,          /* 40 */
    RTC_Alarm_IRQHandler,          /* 41 */
    OTG_FS_WKUP_IRQHandler,        /* 42 */
    RESERVED_SLOT,                 /* 43 - TIM8_BRK_TIM12 (reserved on F411) */
    RESERVED_SLOT,                 /* 44 - TIM8_UP_TIM13 (reserved on F411) */
    RESERVED_SLOT,                 /* 45 - TIM8_TRG_COM_TIM14 (reserved on F411) */
    RESERVED_SLOT,                 /* 46 - TIM8_CC (reserved on F411) */
    DMA1_Stream7_IRQHandler,       /* 47 */
    RESERVED_SLOT,                 /* 48 - FSMC/FMC (reserved on F411) */
    SDIO_IRQHandler,               /* 49 */
    TIM5_IRQHandler,               /* 50 */
    SPI3_IRQHandler,               /* 51 */
    RESERVED_SLOT,                 /* 52 - UART4 (reserved on F411) */
    RESERVED_SLOT,                 /* 53 - UART5 (reserved on F411) */
    RESERVED_SLOT,                 /* 54 - TIM6_DAC (reserved on F411) */
    RESERVED_SLOT,                 /* 55 - TIM7 (reserved on F411) */
    DMA2_Stream0_IRQHandler,       /* 56 */
    DMA2_Stream1_IRQHandler,       /* 57 */
    DMA2_Stream2_IRQHandler,       /* 58 */
    DMA2_Stream3_IRQHandler,       /* 59 */
    DMA2_Stream4_IRQHandler,       /* 60 */
    RESERVED_SLOT,                 /* 61 - ETH (reserved on F411) */
    RESERVED_SLOT,                 /* 62 - ETH_WKUP (reserved on F411) */
    RESERVED_SLOT,                 /* 63 - CAN2_TX (reserved on F411) */
    RESERVED_SLOT,                 /* 64 - CAN2_RX0 (reserved on F411) */
    RESERVED_SLOT,                 /* 65 - CAN2_RX1 (reserved on F411) */
    RESERVED_SLOT,                 /* 66 - CAN2_SCE (reserved on F411) */
    OTG_FS_IRQHandler,             /* 67 */
    DMA2_Stream5_IRQHandler,       /* 68 */
    DMA2_Stream6_IRQHandler,       /* 69 */
    DMA2_Stream7_IRQHandler,       /* 70 */
    USART6_IRQHandler,             /* 71 */
    I2C3_EV_IRQHandler,            /* 72 */
    I2C3_ER_IRQHandler,            /* 73 */
    RESERVED_SLOT,                 /* 74 - OTG_HS_EP1_OUT (reserved on F411) */
    RESERVED_SLOT,                 /* 75 - OTG_HS_EP1_IN (reserved on F411) */
    RESERVED_SLOT,                 /* 76 - OTG_HS_WKUP (reserved on F411) */
    RESERVED_SLOT,                 /* 77 - OTG_HS (reserved on F411) */
    RESERVED_SLOT,                 /* 78 - DCMI (reserved on F411) */
    RESERVED_SLOT,                 /* 79 - CRYP (reserved on F411) */
    RESERVED_SLOT,                 /* 80 - HASH_RNG (reserved on F411) */
    FPU_IRQHandler,                /* 81 */
    RESERVED_SLOT,                 /* 82 */
    RESERVED_SLOT,                 /* 83 */
    SPI4_IRQHandler,               /* 84 */
#ifdef STM32F411xx
    SPI5_IRQHandler, /* 85 */
#endif
};
