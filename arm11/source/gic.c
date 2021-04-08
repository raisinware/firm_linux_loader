#include "gic.h"

#define BIT(n) (1 << (n))

void gic_enable_control(void)
{
	*(volatile int*)GIC_CPU_CTRL = 1;
}

void gic_disable_all(void)
{
	*(volatile int*)(GIC_DIST_ENABLE_CLEAR +  0) = -1;
	*(volatile int*)(GIC_DIST_ENABLE_CLEAR +  4) = -1;
	*(volatile int*)(GIC_DIST_ENABLE_CLEAR +  8) = -1;
	*(volatile int*)(GIC_DIST_ENABLE_CLEAR + 12) = -1;
}

void gic_clear_interrupt(int id)
{
	if (id < 32)
		*(volatile unsigned*)(GIC_DIST_PENDING_CLEAR +  0) = BIT(id);
	else if (id < 64)
		*(volatile unsigned*)(GIC_DIST_PENDING_CLEAR +  4) = BIT(id % 32);
	else if (id < 96)
		*(volatile unsigned*)(GIC_DIST_PENDING_CLEAR +  8) = BIT(id % 32);
	else if (id < 128)
		*(volatile unsigned*)(GIC_DIST_PENDING_CLEAR + 12) = BIT(id % 32);
}

void gic_set_prio(int id, int prio)
{
	*(volatile int*)(GIC_DIST_PRI + id) = prio;
}

void gic_set_target(int id, int core)
{
	*(volatile int*)(GIC_DIST_TARGET + id) = core - 1;
}

void gic_enable_interrupt(int id)
{
	if (id < 32)
		*(volatile unsigned*)(GIC_DIST_ENABLE_SET +  0) = BIT(id);
	else if (id < 64)
		*(volatile unsigned*)(GIC_DIST_ENABLE_SET +  4) = BIT(id % 32);
	else if (id < 96)
		*(volatile unsigned*)(GIC_DIST_ENABLE_SET +  8) = BIT(id % 32);
	else if (id < 128)
		*(volatile unsigned*)(GIC_DIST_ENABLE_SET + 12) = BIT(id % 32);
}
