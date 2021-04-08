#include "gic.h"

#define BIT(n) (1 << (n))

void gic_enable_control(void)
{
	*(volatile int*)GIC_CPU_REGS_BASE = 1;
}

void gic_disable_all(void)
{
	// enable_clear.
	*(volatile int*)(GIC_DIST_REGS_BASE + 384) = 0xFFFFFFFF;
	*(volatile int*)(GIC_DIST_REGS_BASE + 388) = 0xFFFFFFFF;
	*(volatile int*)(GIC_DIST_REGS_BASE + 392) = 0xFFFFFFFF;
	*(volatile int*)(GIC_DIST_REGS_BASE + 396) = 0xFFFFFFFF;
}

// pending_set = +512.
void gic_clear_interrupt(int id)
{
	// pending_clear.
	if (id < 32)
		*(volatile unsigned*)(GIC_DIST_REGS_BASE + 640) = BIT(id);
	else if (id < 64)
		*(volatile unsigned*)(GIC_DIST_REGS_BASE + 644) = BIT(id % 32);
	else if (id < 96)
		*(volatile unsigned*)(GIC_DIST_REGS_BASE + 648) = BIT(id % 32);
	else if (id < 128)
		*(volatile unsigned*)(GIC_DIST_REGS_BASE + 652) = BIT(id % 32);
}

// active_set = +768
// pri = +1024
void gic_set_prio(int id, int prio)
{
	*(volatile int*)(GIC_DIST_REGS_BASE + 1024 + id) = prio;
}

// target = +2048
void gic_set_target(int id, int core)
{
	*(volatile int*)(GIC_DIST_REGS_BASE + 2048 + id) = core - 1;
}

void gic_enable_interrupt(int id)
{
	if (id < 32)
		*(volatile unsigned*)(GIC_DIST_REGS_BASE + 256) = BIT(id);
	else if (id < 64)
		*(volatile unsigned*)(GIC_DIST_REGS_BASE + 260) = BIT(id % 32);
	else if (id < 96)
		*(volatile unsigned*)(GIC_DIST_REGS_BASE + 264) = BIT(id % 32);
	else if (id < 128)
		*(volatile unsigned*)(GIC_DIST_REGS_BASE + 268) = BIT(id % 32);
}
