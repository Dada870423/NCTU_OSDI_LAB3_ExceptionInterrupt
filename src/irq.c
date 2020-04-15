#include "../include/entry.h"
#include "../include/uart.h"
#include "../include/irq.h"
#include "../include/peripherals.h"
#include "../include/peripherals.h"


const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};
/*
void enable_interrupt_controller()
{
	put32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
}*/



void print_system_registers(){
	unsigned int elr_el1, elr_el2, elr_el3;
	unsigned int esr_el1, esr_el2, esr_el3;
	unsigned int currentel, daif, nzcv, spsel;	

	char buf[100];

	asm volatile("mrs %0, elr_el1\n" : "=r"(elr_el1));
	itoa(elr_el1, buf, 10);
	uart_puts("ELR_EL1: 0x");
	//uart_puts(buf);
	uart_hex(elr_el1);
	uart_puts("\n");
/*
*/
	asm volatile("mrs %0, esr_el1\n" : "=r"(esr_el1));
	itoa(esr_el1, buf, 10);
	uart_puts("ESR_EL1: 0x");
	//uart_puts(buf);
	uart_hex(esr_el1);
	uart_puts("\n");
/*
*/
	asm volatile("mrs %0, CurrentEL\n" : "=r"(currentel));
	currentel = currentel >> 2;
	itoa(currentel, buf, 10);
	uart_puts("CURRENT EXCEPTION LEVEL: ");
	uart_puts(buf);
	uart_puts("\n");

	asm volatile("mrs %0, DAIF\n" : "=r"(daif));
	itoa(daif, buf, 10);
	uart_puts("DAIF: ");
	uart_puts(buf);
	uart_puts("\n");

	asm volatile("mrs %0, NZCV\n" : "=r"(nzcv));
	itoa(nzcv, buf, 10);
	uart_puts("NZCV: ");
	uart_puts(buf);
	uart_puts("\n");

	asm volatile("mrs %0, SPSel\n" : "=r"(spsel));
	itoa(spsel, buf, 10);
	uart_puts("SPSEL: ");
	uart_puts(buf);
	uart_puts("\n");

}























void system_call(unsigned int syscall_number){

	/*if(syscall_number == 1){	// core timer enable
		core_timer_enable();
	}else if(syscall_number == 2){
		uart_puts("system call 2 test\n");	
	}else*/ if(syscall_number == 3){
		print_system_registers();
	}else{
		uart_puts("no such system call number!\n");
	}
	return;
}








void sync_el0_64_handler(int x0, int x1, int x2, int x3, int x4, int x5){

	unsigned int elr_el1;
	unsigned int esr_el1;
	unsigned int syscall_number;

	// read the system call number
	asm volatile("mrs %0, elr_el1\n" : "=r"(elr_el1));	// exception return address
	asm volatile("mrs %0, esr_el1\n" : "=r"(esr_el1));	// read the exception class
	asm volatile("mov %0, x8\n" : "=r"(syscall_number));	// system call number is saved in x8 register

	if(( (esr_el1 & 0xFC000000) >> 26) == 0x15){	// SVC instruction execution in AArch64 state
		if(!(esr_el1 & 0x00000FFF)){	// 
			system_call(syscall_number);
			return;
		}else{
			show_invalid_entry_message(-1, esr_el1, elr_el1);
		}
	}else{
		// pass
	}
}


void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
    uart_puts(entry_error_messages[type]);
    uart_puts(", ESR: ");
    uart_hex(esr);
    uart_puts(", address: ");
    uart_hex(address);
    uart_puts("\r\n");
	//printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}

void handle_irq(void)
{
/*	unsigned int irq = get32(IRQ_PENDING_1);
	switch (irq) {
		case (SYSTEM_TIMER_IRQ_1):
			handle_timer_irq();
			break;
		default:*/
//			printf("Unknown pending irq: %x\r\n", irq);
    uart_puts("Unknown pending irq: \r\n");
//	}
}
