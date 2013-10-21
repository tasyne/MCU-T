
#include <gpio.h>
#include <attiny45.h>

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/io.h>

int LED = PB4; 
int LEDBit = PIN_SOURCE_4;

/*
void system_sleep() {
	//cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
	sleep_enable();

	sleep_mode();                        // System sleeps here
	sleep_disable();                     // System continues execution here when watchdog timed out 
	
	PORTB |= 1 << LED; 		//set to HIGH
	_delay_ms(1000);
	PORTB ^= 1 << LED; 	//flip-flop LED
	//sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
}
*/

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
	sei();

   // Set up Port B pin 4 mode to output
    //DDRB |= 1<<LED;
	port_setDir(LEDBit);

	//PORTB |= 1<<LED;
	//DDRB = 0xFF;
	
	
	//PORTB = 0xFF;
	setPins(LEDBit);
	
	// ?? WDCE is needed????
   // temporarily prescale timer to 0.5 s so we can !?
   //WDTCR = 0;
   WDTCR = (1<<WDP2) | (1<<WDP0) | (1<<WDCE) | (0<<WDE) | (1<<WDIE); //(1<<WDP3); 

   // Enable watchdog timer interrupts
   /*
   WDTCR |= (1<<WDCE); //within 4 clock cycles... disable WDE
   WDTCR &= (0<<WDE);
   WDTCR |= (1<<WDIE);
   */

	for(;;){
	//_delay_ms(500);
		//PORTB ^= PIN_SOURCE_4;
	//togglePin(LEDBit);

		//_delay_ms(500);
		//PORTB = 0<<LED;
		//PORTB = 0;
	}
	
 /*
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
*/
}

ISR(WDT_vect) {
   // Toggle Port B pin 4 output state
   //PORTB ^= 1<<LED;
	togglePin(LEDBit);

	//system_sleep();
}

