#include <io.h>
#include <stdint.h>
#include <interrupt.h>
#include <delay.h>

// Segments: A=PC0, B=PB5, C=PC1, D=PC2, E=PC3, F=PC4, G=PC5, DP=PD0
#define A(x) (x ? (PORTC|=(1<<0)):(PORTC &= ~(1<<0)))
#define B(x) (x ? (PORTB|=(1<<5)):(PORTB &= ~(1<<5)))
#define C(x) (x ? (PORTC|=(1<<1)):(PORTC &= ~(1<<1)))
#define D(x) (x ? (PORTC|=(1<<2)):(PORTC &= ~(1<<2)))
#define E(x) (x ? (PORTC|=(1<<3)):(PORTC &= ~(1<<3)))
#define F(x) (x ? (PORTC|=(1<<4)):(PORTC &= ~(1<<4)))
#define G(x) (x ? (PORTC|=(1<<5)):(PORTC &= ~(1<<5)))
#define DP(x)(x ? (PORTD|=(1<<0)):(PORTD &= ~(1<<0)))

// Digits: Common Cathode  LOW = ON, HIGH = OFF
#define DIG1(x) (x ? (PORTD &= ~(1<<1)) : (PORTD |= (1<<1)))  // LOW = ON
#define DIG2(x) (x ? (PORTD &= ~(1<<2)) : (PORTD |= (1<<2)))  // LOW = ON
#define DIG3(x) (x ? (PORTD &= ~(1<<3)) : (PORTD |= (1<<3)))  // LOW = ON
#define DIG4(x) (x ? (PORTD &= ~(1<<4)) : (PORTD |= (1<<4)))  // LOW = ON

const uint8_t seg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

volatile uint16_t counter = 0;
volatile uint8_t digits[4] ={0};
volatile uint8_t current_digit = 0;

void main(void)
{   DDRB |= (1<<5);     // PB5 output (Segment B)
    DDRC |= 0x3F;       // PC0-PC5 output (Segments A,C,D,E,F,G)
    DDRD |= 0x1F;       // PD0-PD4 output (DP, DIG1-DIG4)
    
    //initialize
    counter=2000;
    //update_digits();
    
    //start timers
    timer_init();
    
    
    
     
     
     #asm("sei")
     TCNT0=5;//VALUE
     
while (1)
    {
    

    }
}


void put_7seg(uint8_t dat)
{ 
    A(dat & 0x01);
    B(dat & 0x02);
    C(dat & 0x04);
    D(dat & 0x08);
    E(dat & 0x10);
    F(dat & 0x20);
    G(dat & 0x40);
    DP(dat & 0x80);
}

interrupt [TIM0_OVF] void timer0_ovf(void)
{
  TCNT0=5;
  DIG1(0);
  DIG2(0);
  DIG3(0);
  DIG4(0);
  switch(current_digit)
  {
    case 0:
        DIG1(1);
        break;
    case 1:
        DIG2(1);
        break;
    case 3:
        DIG3(1);
        break;
    case 4:
            DIG4(1);
            break;
            }
}


void timer_init(void)
{
    //TIMER0-NORMAL MODE-PRESCALER=64-1.024ms overflow
     TCCR0B=0x3;//division by 64 //TCCR0B=(1<<CS02)|(1<<CS00)
     TIMSK0=0x1;//overflow interrupt enable //(1<<TOIE0)
     //TIMER2-normal mode-prescaler=64
     TCCR2B=0x4;//(1<<CS22)
     TIMSK2=0x1;//(1<<TOIE2)

}

void digits_update(uint8_t dat)
{

}
