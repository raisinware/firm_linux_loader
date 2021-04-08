#ifndef _GIC_H
#define _GIC_H

#define GIC_CPU_REGS_BASE	(0x17E00100)
#define GIC_DIST_REGS_BASE	(0x17E01000)

#ifndef __ASSEMBLY__

void gic_enable_control(void);
void gic_disable_all(void);
void gic_clear_interrupt(int id);
void gic_set_prio(int id, int prio);
void gic_set_target(int id, int core);
void gic_enable_interrupt(int id);

#endif
#endif
