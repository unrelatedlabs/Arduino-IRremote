/*
 * ============================================================================
 *
 *       Filename:  Arduino-IRremote.cpp
 *
 *    Description:  Arduino Library for IR communication
 *
 *        Version:  2.0
 *        Created:  11/29/2015 07:05:44 PM
 *       Revision:  0
 *       Compiler:  Arduino IDE [Version: ]
 *
 *         Author:  Rafi Khan (z3t0)
 *
 *         Adapted from: Ken Shirriff's work which is copyrighted by Ken Shirriff
 *         Contributors found in Contributors.md
 *
 * ============================================================================
 */
 
#include "Arduino-IRremote.h"
#include "devices.h"
 
//=============================================================================
// Send Class
//=============================================================================

IR_Send::IR_Send(int send_pin)
{
    pin = send_pin;
}

void IR_Send::mark(unsigned int time)
{
    // ENABLE PWM
    if (time > 0) custom_delay_usec(time);
}

void IRsend::space (unsigned int time)
{
    // DISABLE PWM
    if (time > 0) custom_delay_usec(time);
}
 
 
 // Delay Function
custom_delay_usec(unsigned long uSecs) {
  if (uSecs > 4) {
    unsigned long start = micros();
    unsigned long endMicros = start + uSecs - 4;
    if (endMicros < start) { // Check if overflow
      while ( micros() > start ) {} // wait until overflow
    }
    while ( micros() < endMicros ) {} // normal wait
  } 
 
  else {
    __asm__("nop\n\t"); // must have or compiler optimizes out
  }
}

// TODO:
// void  IRsend::enableIROut (int khz)
// {
// 	// Disable the Timer2 Interrupt (which is used for receiving IR)
// 	TIMER_DISABLE_INTR; //Timer2 Overflow Interrupt

// 	pinMode(TIMER_PWM_PIN, OUTPUT);
// 	digitalWrite(TIMER_PWM_PIN, LOW); // When not sending PWM, we want it low

// 	// COM2A = 00: disconnect OC2A
// 	// COM2B = 00: disconnect OC2B; to send signal set to 10: OC2B non-inverted
// 	// WGM2 = 101: phase-correct PWM with OCRA as top
// 	// CS2  = 000: no prescaling
// 	// The top value for the timer.  The modulation frequency will be SYSCLOCK / 2 / OCR2A.
// 	TIMER_CONFIG_KHZ(khz);
// }

 
 // Receive Class
 