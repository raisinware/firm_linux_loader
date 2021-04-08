#ifndef _GIC_H
#define _GIC_H

// These are only accessible from arm11 core...

#define MPCORE_PRIV_REG_BASE	(0x17E00000)
#define GIC_CPU_REGS_BASE	(MPCORE_PRIV_REG_BASE + 0x0100)
#define GIC_DIST_REGS_BASE	(MPCORE_PRIV_REG_BASE + 0x1000)

/*
 * Names/values via:
 * https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/include/linux/irqchip/arm-gic.h
 */

#define GIC_CPU_CTRL		(GIC_CPU_REGS_BASE + 0x00)
#define GIC_DIST_ENABLE_SET	(GIC_DIST_REGS_BASE + 0x100)
#define GIC_DIST_ENABLE_CLEAR	(GIC_DIST_REGS_BASE + 0x180)
#define GIC_DIST_PENDING_CLEAR	(GIC_DIST_REGS_BASE + 0x280)
#define GIC_DIST_PRI		(GIC_DIST_REGS_BASE + 0x400)
#define GIC_DIST_TARGET		(GIC_DIST_REGS_BASE + 0x800)

#ifndef __ASSEMBLY__

void gic_enable_control(void);
void gic_disable_all(void);
void gic_clear_interrupt(int id);
void gic_set_prio(int id, int prio);
void gic_set_target(int id, int core);
void gic_enable_interrupt(int id);

#endif
#endif
