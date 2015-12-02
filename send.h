/*
 * =====================================================================================
 *
 *       Filename:  send.h
 *
 *    Description:  Header file for Send Class
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
 
//=============================================================================
// Send Class
//=============================================================================

class IR_Send
{   
    public:
    
        // Constructor
        IR_Send(int send_pin)
        
        // Marks and Spaces
        void mark(unsigned int time);
        void space(unsigned int time);

        // Iterates through buffer, calling on mark() and space()        
        void sendRaw(unsigned int buf[], unsigned int len, unsigned int hz);
        
        unsigned char pin;
}

// Delay Function

void custom_delay_usec(unsigned long uSecs);