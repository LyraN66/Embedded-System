#include "mbed.h"
#include "MFRC522.h"
#include "platform/mbed_thread.h"

#define MF_RESET    D8  // pin du Nucleo branchée à la pin RST du RC522
PwmOut buzzer(D3);
DigitalIn flameSensor(D2);

float AlarmNote1 = 200; 
float AlarmNote2 = 350; 
float AlarmNote3 = 250;
float AlarmNote4 = 400;
float AlarmNote5 = 150;

const char bonUID[4] = {0x90, 0xCF, 0x94, 0x75};

MFRC522    RfChip   (SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, MF_RESET);

// SPI_MOSI = D11
// SPI_MISO = D12
// SPI_SCK = D13
// SPI_CS/SDA = D10
// MF_RESET = D8
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

int main(void) {

    RfChip.PCD_Init();

    while (true) {

        if(flameSensor.read() == 0) { // Alev algılandı
            playFireAlarm(); // Yangın alarmı melodisini çal
        } else {
            buzzer.write(0); // Alev algılanmadığında buzzer'ı kapat
        }

        int refus = 0;  // demeure nul si l'UID est bon

        if ( ! RfChip.PICC_IsNewCardPresent()) {
            HAL_Delay(50);
            continue;
        }

        if ( ! RfChip.PICC_ReadCardSerial()) {
            HAL_Delay(50);
            continue;
        }

        printf("UID:"); // UID bilgisini baslamadan once etiket

        for (uint8_t i = 0; i < RfChip.uid.size; i++) {
            printf(" %02X", RfChip.uid.uidByte[i]); // UID bytes

            if (RfChip.uid.uidByte[i] != bonUID[i]) {
                refus++;
            }
        }

        printf("\n"); // Sonunda yeni bir satıra geç

        if (refus > 0) {
            // UID yanlış ise burada işlemler yapabilirsiniz
        } else {
            // UID doğru ise burada işlemler yapabilirsiniz
        }

        RfChip.PICC_HaltA(); // Kartı durdur
    }
}
