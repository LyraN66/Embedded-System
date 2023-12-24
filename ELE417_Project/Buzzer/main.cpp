#include "mbed.h"
#include "platform/mbed_thread.h"

PwmOut buzzer(D3);
DigitalIn flameSensor(D2);

float Nota_C4 = 262;
float Nota_A4 = 440;
float Nota_E4 = 659;

void playMelody() {
    buzzer.period(1.0/Nota_C4);
    buzzer.write(0.5);
    thread_sleep_for(200);

    buzzer.period(1.0/Nota_A4);
    buzzer.write(0.5);
    thread_sleep_for(200);

    buzzer.period(1.0/Nota_E4);
    buzzer.write(0.5);
    thread_sleep_for(200);
}

int main() {
    while(1){
        if(flameSensor.read() == 0) { // Alev algılandı
            for(int i = 0; i < 5; i++) {
                playMelody(); // Melodiyi çal
            }
        } else {
            buzzer.write(0); // Alev algılanmadığında buzzer'ı kapat
        }
        thread_sleep_for(100); // Kısa bir bekleme süresi
    }
}
