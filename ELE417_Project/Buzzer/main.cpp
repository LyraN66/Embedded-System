#include "mbed.h"
#include "platform/mbed_thread.h"

PwmOut buzzer(D3);
DigitalIn flameSensor(D2);

float AlarmNote1 = 200; 
float AlarmNote2 = 350; 
float AlarmNote3 = 250;
float AlarmNote4 = 400;
float AlarmNote5 = 150;

void playFireAlarm() {
    for(int i = 0; i < 10; i++) {
        buzzer.period(1.0/AlarmNote1);
        buzzer.write(0.5);
        thread_sleep_for(100);

        buzzer.period(1.0/AlarmNote2);
        buzzer.write(0.5);
        thread_sleep_for(100);

        buzzer.period(1.0/AlarmNote3);
        buzzer.write(0.5);
        thread_sleep_for(100);

        buzzer.period(1.0/AlarmNote4);
        buzzer.write(0.5);
        thread_sleep_for(100);

        buzzer.period(1.0/AlarmNote5);
        buzzer.write(0.5);
        thread_sleep_for(100);
    }
}

int main() {
    while(1){
        if(flameSensor.read() == 0) { // Alev algılandı
            playFireAlarm(); // Yangın alarmı melodisini çal
        } else {
            buzzer.write(0); // Alev algılanmadığında buzzer'ı kapat
        }
        thread_sleep_for(100); // Kısa bir bekleme süresi
    }
}
