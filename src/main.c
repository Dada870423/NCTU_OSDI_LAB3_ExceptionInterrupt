#include "../include/uart.h"
#include "../include/util.h"
#include "../include/reboot.h"
#include "../include/mbox.h"
#include "../include/get_HW_info.h"
#include "../include/irq.h"
#include "../include/timer.h"

extern void sync_call();

void main()
{
    int i, length = 0;
    //unsigned long int el;
    //get command
    int HELLO = 0;
    int EXC = 0;
    int IRQ = 0;
    //declare done

    // set up serial console
    uart_init();

    // welcome
    uart_puts("\r\nWelcome to Lab3\n");
    //declare and initial the command buffer
    char input[100];
	asm volatile("svc #1");	
    for(i=0;i<100;i++) input[i] = '0';
    //read the current level
    for(;;)
    {
        length = ReadLine(input);
		
        //deal with the command
		
        //which command
        HELLO = StrCmp(input, "hello", length, 5);
        EXC = StrCmp(input, "exc", length, 3);
        IRQ = StrCmp(input, "irq", length, 3);
        //command detection done

			
        if(HELLO == 1) uart_puts("\rHello World!\n");
        else if(EXC == 1) 
        {
            sync_call();
            uart_puts("print the EL:(exc) ");
            uart_puts("\r\n# ");
        }
        else if(IRQ == 1)
        {
            irq_cmd();
        }
        else if(length != 0)
        { 
            uart_puts("\rcommand  ");
            for(i=0;i<length;i++) uart_send(input[i]);
            uart_puts("  not found, use help!!!\n");
        }
			
        /* if(REBOOT == 0)*/ 
        uart_puts("\r# ");
			
        //init input_command
        for(i=0;i<100;i++) input[i] = '0';
        length = 0;
        HELLO = 0;
        IRQ = 0;
    }
}
