#include "gic.h"

#define BIT(n) (1 << (n))

void gic_enable_control(void)
{
	*(volatile int*)GIC_CPU_CTRL = 1;
}

void gic_disable_all(void)
{
	volatile int *gic_enable_clear = (volatile int*)GIC_DIST_ENABLE_CLEAR;
	gic_enable_clear[0] = -1;
	gic_enable_clear[1] = -1;
	gic_enable_clear[2] = -1;
	gic_enable_clear[3] = -1;
}

static void gic_x_interrupt(volatile int* addr, int id)
{
	addr[0] = BIT(id);
	addr[1] = BIT(id % 32);
	addr[2] = BIT(id % 32);
	addr[3] = BIT(id % 32);
}

void gic_clear_interrupt(int id)
{
	gic_x_interrupt((volatile int*)GIC_DIST_PENDING_CLEAR, id);
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
	gic_x_interrupt((volatile int*)GIC_DIST_ENABLE_SET, id);
}
