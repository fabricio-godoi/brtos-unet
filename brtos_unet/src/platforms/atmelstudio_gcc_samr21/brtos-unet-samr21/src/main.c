/**
 * \file main.c
 *
 * \brief  BRTOS UNET port to SAMR21
 *
 */

#include "asf.h"

void main_app(void);

int main(void)
{
	irq_initialize_vectors();

	system_init();
	delay_init();

	cpu_irq_enable();
	
	// Initialize system and tasks
	main_app();

	while (1) 
	{

	}
}
