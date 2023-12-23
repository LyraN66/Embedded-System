#include "mbed.h"
#include "platform/mbed_thread.h"
 
PwmOut buzzer(D3);
 
int main() {
 
 float Nota_C4 = 262;
 float Nota_A4 = 440;
 float Nota_E4 = 659;
 
 while(1){
   
   buzzer.period(1.0/Nota_C4); // Configurando el periodo, que es equivalente a frecuencia (veces que se reproducira el tono por segundo)
   buzzer.write(0.5);
   thread_sleep_for(200);
   
   buzzer.period(1.0/Nota_A4); // Configurando el periodo, que es equivalente a frecuencia (veces que se reproducira el tono por segundo)
   buzzer.write(0.5);
   thread_sleep_for(200);
   
   buzzer.period(1.0/Nota_E4); // Configurando el periodo, que es equivalente a frecuencia (veces que se reproducira el tono por segundo)
   buzzer.write(0.5);
   thread_sleep_for(200);
   
 }
}
