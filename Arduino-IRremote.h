/*
 * =====================================================================================
 *
 *       Filename:  Arduino-IRremote.h
 *
 *    Description:  Header file containing ir configuration settings for the Arduino
 *    IRremote library
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
 * =====================================================================================
 */

#ifndef IRremote_h
#define IRremote_h

//======================================================================================
// Include the Arduino header
//======================================================================================

/* #if defined(ARDUINO) && (ARDUINO >= 100) */
/*     #include <Arduino.h> */
/* #else */
/*     #include <WProgram.h> */

/* #endif */

//======================================================================================
// DEBUG
//======================================================================================
// Here are the debug defines
// #define IR_GLOBAL            //  Allows for sharing of extern variables
//                                  e.g.
//                                  IR_EXTERN  volatile irparams_t  irparams;
//                                  is only truly external if IR_GLOBAL is
//                                  defined
// #define IR_BLINKLED          //  Enables blinking of IR_BLINKLED_PIN when ...

//=======================================================================================
// GLOBAL VARIABLES
//=======================================================================================
// This handles definition and access to global variables
#ifdef IR_GLOBAL
    #define IR_EXTERN
#else
    #define IR_EXTERN extern
#endif

//=======================================================================================
// Information for the Interrupt Service Routine
//=======================================================================================
// Raw buffer holds data
#define RAWBUF  101  // Maximum length of raw duration buffer

// Define irparams_t ...
typedef
	struct {
		// The fields are ordered to reduce memory over caused by struct-padding
		uint8_t       rcvstate;        // State Machine state
		uint8_t       recvpin;         // Pin connected to IR data from detector
		uint8_t       blinkpin;
		uint8_t       blinkflag;       // true -> enable blinking of pin on IR processing
		uint8_t       rawlen;          // counter of entries in rawbuf
		unsigned int  timer;           // State timer, counts 50uS ticks.
		unsigned int  rawbuf[RAWBUF];  // raw data
		uint8_t       overflow;        // Raw buffer overflow occurred
	}
irparams_t;

// ISR State-Machine : Receiver States
#define STATE_IDLE      2
#define STATE_MARK      3
#define STATE_SPACE     4
#define STATE_STOP      5
#define STATE_OVERFLOW  6

// Allow all parts of the code access to the ISR data
// NB. The data can be changed by the ISR at any time, even mid-function
// Therefore we declare it as "volatile" to stop the compiler/CPU caching it
EXTERN volatile irparams_t  irparams;

//=======================================================================================
// Blinking LED defines
//=======================================================================================

#ifdef IR_BLINKLED
// TODO: Add TEENSY 2, 3
// TODO: Create Table
    #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
        #define IR_BLINKLED_PIN    13
        #define IR_BLINKLED_ON()   (PORTB |= B10000000)
        #define IR_BLINKLED_OFF()  (PORTB &= B01111111)

    #elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)
        #define IR_BLINKLED_PIN    0
        #define IR_BLINKLED_ON()   (PORTD |= B00000001)
        #define IR_BLINKLED_OFF()  (PORTD &= B11111110)

    #else
        #define IR_BLINKLED_PIN    13
	    #define IR_BLINKLED_ON()   (PORTB |= B00100000)
        #define IR_BLINKLED_OFF()  (PORTB &= B11011111)
    #endif
#endif

//=======================================================================================
// CPU Frequency
//=======================================================================================
#ifdef F_CPU
    #define IR_SYSCLOCK  F_CPU     // main Arduino clock
#else
    #error "F_CPU is not defined!!!"
#endif

//=======================================================================================
// Defines for setting and clearing register bits
//=======================================================================================
// sfr: port being cleared or set
// bit: the bit within the port being cleared or set
//
// Information: http://playground.arduino.cc/Main/AVR
//

// Clear Bit in I/O Register
#ifndef cbi
    #define cbi(sfr, bit)  (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

// Set Bit in I/O Register
#ifndef sbi
    #define sbi(sfr, bit)  (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//=======================================================================================
// IR Modulation Variables
//=======================================================================================
// Pulse parms are ((X*50)-100) for the Mark and ((X*50)+100) for the Space.
// First MARK is the one after the long gap
// Pulse parameters in uSec


// Due to sensor lag, when received, Marks  tend to be 100us too long and
//                                   Spaces tend to be 100us too short
#define IR_MARK_EXCESS    100

// microseconds per clock interrupt tick
#define IR_USECPERTICK    50

// Upper and Lower percentage toleranc4es in measurements
#define IR_TOLERANCE       25
#define IR_LTOL            (1.0 - (TOLERANCE/100.))
#define IR_UTOL            (1.0 + (TOLERANCE/100.))

// Minimum gap between IR transmissions
#define IR_GAP            5000
#define IR_GAP_TICKS       (_GAP/USECPERTICK)

#define IR_TICKS_LOW(us)   ((int)(((us)*LTOL/USECPERTICK)))
#define IR_TICKS_HIGH(us)  ((int)(((us)*UTOL/USECPERTICK + 1)))

#define IR_MARK   0		// Mark is 0? Should it not be 1? TODO: Clarify this
#define IR_SPACE  1