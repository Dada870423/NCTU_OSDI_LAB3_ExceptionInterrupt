#ifndef	_TIMER_H_
#define	_TIMER_H_


#define LOCAL_TIMER_CONTROL_AND_STATUS	0x40000034
#define LOCAL_TIMER_IRQ_CLR				0x40000038

void core_timer_enable();
void core_timer_handler();

void local_timer_init();
void local_timer_handler();

#endif  /*_TIMER_H */
