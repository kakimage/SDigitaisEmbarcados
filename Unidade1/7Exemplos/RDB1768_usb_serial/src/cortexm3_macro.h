/******************************************************************************
 *   cortexm3_macro.h:  Header file for NXP LPC17xx Family 
 *   Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.21  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __CORTEXM3_MACRO_H 
#define __CORTEXM3_MACRO_H

//#include "type.h"

/* Inline functions -------------------------------------------------------- */

static inline void __NOP()                      { asm volatile ("nop"); }
static inline void __enable_irq()               { asm volatile ("cpsie i"); }
static inline void __disable_irq()              { asm volatile ("cpsid i"); }

static inline void __enable_fault_irq()         { asm volatile ("cpsie f"); }
static inline void __disable_fault_irq()        { asm volatile ("cpsid f"); }

inline void __WFI()                      		{ asm volatile ("wfi"); }
static inline void __WFE()                      { asm volatile ("wfe"); }
static inline void __SEV()                      { asm volatile ("sev"); }
static inline void __ISB(arg)                   { asm volatile ("isb"); }
static inline void __DSB(arg)                   { asm volatile ("dsb"); }
static inline void __DMB(arg)                   { asm volatile ("dmb"); }

#endif /* end __CORTEXM3_MACRO_H */

/******************************************************************************
**                            End Of File
******************************************************************************/
