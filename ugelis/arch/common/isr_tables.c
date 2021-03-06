/**
 *
 * Copyright (C) 2016 Gree Microelectronics.  All Rights Reserved.
 *
 * @file          
 *
 * @author        Mike.Zheng
 *
 * @version       1.0.0
 *
 * @date          2018/03/24
 *
 * @brief        
 *
 * @note
 *    2018/03/24, Mike.Zheng, V1.0.0
 *        Initial version.
 */

#include <toolchain.h>
#include <linker/sections.h>
#include <sw_isr_table.h>
#include <arch/cpu.h>

/* There is an additional member at the end populated by the linker script
 * which indicates the number of interrupts specified
 */
struct int_list_header {
	u32_t table_size;
	u32_t offset;
};

/* These values are not included in the resulting binary, but instead form the
 * header of the initList section, which is used by gen_isr_tables.py to create
 * the vector and sw isr tables,
 */
_GENERIC_SECTION(.irq_info) struct int_list_header _iheader = {
	.table_size = IRQ_TABLE_SIZE,
	.offset = CONFIG_GEN_IRQ_START_VECTOR,
};

/* These are placeholder tables. They will be replaced by the real tables
 * generated by gen_isr_tables.py.
 *
 * _irq_spurious and _isr_wrapper are used as placeholder values to
 * ensure that they are not optimized out in the first link. The first
 * link must contain the same symbols as the second one for the code
 * generation to work.
 */

/* Some arches don't use a vector table, they have a common exception entry
 * point for all interrupts. Don't generate a table in this case.
 */
#ifdef CONFIG_GEN_IRQ_VECTOR_TABLE
u32_t __irq_vector_table _irq_vector_table[IRQ_TABLE_SIZE] __used = {
	[0 ...(IRQ_TABLE_SIZE - 1)] = (u32_t)&_isr_wrapper,
};
#endif

/* If there are no interrupts at all, or all interrupts are of the 'direct'
 * type and bypass the _sw_isr_table, then do not generate one.
 */
#ifdef CONFIG_GEN_SW_ISR_TABLE
#if defined(__USE_KEIL_) || defined(__USE_GREEIDE_)
	struct _isr_table_entry _sw_isr_table[IRQ_TABLE_SIZE] __used = {
			[0 ...(IRQ_TABLE_SIZE - 1)] = {(void *)0x42, (void *)&_irq_spurious},
	};
#else
	/*for gcc ugelis */
	struct _isr_table_entry __sw_isr_table _sw_isr_table[IRQ_TABLE_SIZE] __used = {
			[0 ...(IRQ_TABLE_SIZE - 1)] = {(void *)0x42, (void *)&_irq_spurious},
	};
#endif



void _sw_isr_table_set(s32_t irq,s32_t flags,void *func,void *param)
{
	_sw_isr_table[irq].arg = param;
	_sw_isr_table[irq].isr = func;
	
}
#endif
