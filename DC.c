/*
The end-goal of this rather simple program is to keep the MCU in as low
a power state as possible, for about an hour, to an hour and a half. The
exact time should vary, and does not need to be precise.

At this point, the MCU should awaken from sleep, and set a pin HIGH for
a second or so, and then repeat.

This is meant to run on an ATTiny45

*/

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/io.h>


int LED = PINB4; 


void system_sleep() {
	//cbi(ADCSRA,ADEN);                    // switch ADC OFF to save more power
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
	sleep_enable();

	sleep_mode();                        // System sleeps here
	sleep_disable();                     // System continues execution here when watchdog timed out 
	
	PORTB |= 1 << LED; 		//set to HIGH
	_delay_ms(1000);
	PORTB ^= 1 << LED; 	//flip-flop LED
	//sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON (maybe?)
}

/*
void WDT_off(void)
{
	_WDR();
	// Clear WDRF in MCUSR
	MCUSR = 0x00;
	// Write logical one to WDCE and WDE
	WDTCR |= (1<<WDCE) | (1<<WDE);
	// Turn off WDT
	WDTCR = 0x00;
}
*/

int main(void) {
   // Set up Port B pin 4 mode to output
    DDRB |= 1<<LED;
	
   // temporarily prescale timer to 4s so we can measure current
   WDTCR |= (1<<WDP3); // (1<<WDP2) | (1<<WDP0);
 
   // Enable watchdog timer interrupts
   WDTCR |= (1<<WDE);
 
   sei(); // Enable global interrupts
 
   // Use the Power Down sleep mode
   //set_sleep_mode(SLEEP_MODE_PWR_DOWN);
 
   for (;;) {
      //sleep_mode();   // go to sleep and wait for interrupt...
	  system_sleep();
   }
}

ISR(WDT_vect) {
	system_sleep();
}
