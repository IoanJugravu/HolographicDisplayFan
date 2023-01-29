#include "letters.h"


int k = 0;
long nrResetTimer = 0;
long timpTotal = 159150;
long timpLinie = 9946;
int prescaler = 8;
unsigned char numarLinii = 120;

char sir[] = "PS 2019";
char sirMap[50];//pentru aranjaretext
int MapMax = numarLinii/6;
int nrLitera = 0;//numara literele din sir
int nrBucati = 0;//numara bucatiile din litere



void setup()
{
    //setup arduino port
    DDRD = 0xF0;  
    DDRC = 0x0F;  
    
    //desable all interupts
    cli();
    //INT0
    EICRA |= (1<< ISC01);//the falling edge make interupt
    PORTD |= (1<< PORTD2);
    EIMSK |= (1<< INT0);
    //setup TIMER1
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;//incepe de la 0
     
    TCCR1B |= (1<<WGM12);
    OCR1A = 60000;  
    TCCR1B |= (1<<CS10);//no prescaler = 0
    TIMSK1 |= (1<<OCIE1A);
    
    //setup TIMER2
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;
    TCCR2B |= (1<<CS20);
    TIMSK2 |= (1<<TOIE2);

    //conversie sir
    Map();
    //enable interupts
    sei();
    //creare sir afisat
}

void loop()
{    
}
//INT0
ISR(INT0_vect){
    //timp = a*256*1/16*10^-6 sec
    timpTotal = 0;
    timpTotal = nrResetTimer*16;//timp in nanosecunde
    timpTotal += TCNT2/16;//nanosecunde
  
    setPrescaler(timpTotal);//setuptimer1
    //afisare
    nrResetTimer = 0;//resetsre valori
    TCNT2 = 0;//resetare registru timer
    //restartare afisare
    nrBucati = 5;
    nrLitera = strlen(sirMap)-1;
}
//TIMER2 --- masoara timpul scurs de la activarea senzorului;
ISR(TIMER2_OVF_vect){
  //incrementare dupa fiecare OVF
  nrResetTimer++;
  if(nrResetTimer > 2147483640){
    //se reseteaza daca se trece peste val max long
    nrResetTimer=0;
  }
}
//TIMER1 --- imparte timpul total in bucatele de litere
ISR(TIMER1_COMPA_vect){
    
    afisareLitera(sirMap[nrLitera], nrBucati);
    nrBucati--;
    if(nrBucati < 0){
      if(nrLitera>=0){
        nrLitera --;  
      }
      nrBucati = 5;
    }
}
void setPrescaler(long timp){
  timpLinie = 16*timp/numarLinii;//
    //setare prescaler = 1 
    // val max OCR1A=65535
    if(timpLinie < 65535){
      prescaler = 1;
      TCCR1B |= (1<<CS10);
      TCCR1B &= ~(1<<CS11) & ~(1<<CS12); 
    }
    //setare prescaler = 8 
    if(timpLinie > 65535 && timpLinie < 8*65535){    
      //TCCR1B =0;
      prescaler = 8;
      TCCR1B |= (1<<CS11);
      TCCR1B &= ~(1<<CS10) & ~(1<<CS12); 
    }
    //setare prescaler = 64 
    if(timpLinie > 8*65535 && timpLinie < 64*65535){    
      //TCCR1B =0;
      prescaler = 64;
      TCCR1B |= (1<<CS11) | (1<<CS10);
      TCCR1B &= ~(1<<CS12); 
    }
    //setare prescaler = 256 
    if(timpLinie > 64*65535 && timpLinie < 256*65535){    
      //TCCR1B =0;
      prescaler = 256;
      TCCR1B |= (1<<CS12);
      TCCR1B &= ~(1<<CS11) & ~(1<<CS10); 
    }
  //setare prescaler = 1024 
    if(timpLinie > 256*65535){    
      //TCCR1B =0;
      prescaler = 1024;
      TCCR1B |= (1<<CS12) | (1<<CS10);
      TCCR1B &= ~(1<<CS11); 
    }
    timpLinie /=  prescaler;
    if(timpLinie == 0){
      timpLinie=1;
    }
    OCR1A = timpLinie;
    TCNT1 = 0;
}
void Map(){//incadreaza textul in partea de mijloc
  int i = 0;
  for(i = 0; i< MapMax; i++){
    sirMap[i] = ' ';
  }
  for(i = 0; i< strlen(sir)/2; i++){
    sirMap[MapMax - i - 1] = sir[strlen(sir)/2 - i-1];
  }
  for(i = 0; i< strlen(sir)/2 + 1; i++){
    sirMap[i] = sir[strlen(sir)/2 + i];
  }
}
