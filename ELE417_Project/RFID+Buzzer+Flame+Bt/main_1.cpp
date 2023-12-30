#include "mbed.h"
#include "MFRC522.h"

#define MF_RESET    D15
PwmOut buzzer(D3);
DigitalIn flameSensor(D4);
BufferedSerial uart2(D8, D2); // UART2 (TX, RX)
BufferedSerial uart3(PB_10, PB_11); // UART3 (TX, RX)

float AlarmNote1 = 200; 
float AlarmNote2 = 350; 
float AlarmNote3 = 250;
float AlarmNote4 = 400;
float AlarmNote5 = 150;

struct UIDInfo {
    const char *uid;
    const char *label;
};

const UIDInfo uidList[] = {
    {"E3A962AD", "user1"},
    {"C1C0D0CF", "user2"},
    {"E38552F8", "user3"},
    // Daha fazla UID ve etiket eklenebilir
};

const int uidListSize = sizeof(uidList) / sizeof(uidList[0]);

MFRC522 RfChip(SPI_MOSI, SPI_MISO, SPI_SCK, D10, MF_RESET);  // Dikkat: CS pinini doğru belirleyin

void playFireAlarm() {
    for(int i = 0; i < 5; i++) {
        buzzer.period(1.0/AlarmNote1);
        buzzer.write(0.5);
        ThisThread::sleep_for(100ms);

        //buzzer.period(1.0/AlarmNote2);
        //buzzer.write(0.5);
        //ThisThread::sleep_for(100ms);

        //buzzer.period(1.0/AlarmNote3);
        //buzzer.write(0.5);
        //ThisThread::sleep_for(100ms);

        //buzzer.period(1.0/AlarmNote4);
        //buzzer.write(0.5);
        //ThisThread::sleep_for(100ms);

        //buzzer.period(1.0/AlarmNote5);
        //buzzer.write(0.5);
        //ThisThread::sleep_for(100ms);
    }
}

void send_message(BufferedSerial &serial, const char *message) {
    serial.write(message, strlen(message));
    // Burada \n eklemeyi kaldırıyoruz
}

void read_and_print_uart2() {
    char rx_buffer[100]; // Alınan verileri saklamak için bir buffer
    if (uart2.readable()) { // UART2 okunabilir mi kontrol ediliyor
        int num_bytes = uart2.read(rx_buffer, sizeof(rx_buffer)); // Veri okunuyor
        if (num_bytes > 0) {
            printf("Received from UART2: %.*s\n", num_bytes, rx_buffer); // Ekrana yazdırılıyor
        }
    }
}


int main(void) {
    RfChip.PCD_Init();
    uart2.set_baud(9600);
    uart3.set_baud(9600);
    
    send_message(uart3, "fire");
    while (true) {
        read_and_print_uart2();
        if(flameSensor.read() == 0) {
            send_message(uart2, "111");
            send_message(uart3, "111");
            playFireAlarm();
        } else {
            buzzer.write(0);
        }

        if ( ! RfChip.PICC_IsNewCardPresent()) {
            ThisThread::sleep_for(50ms);
            continue;
        }

        if ( ! RfChip.PICC_ReadCardSerial()) {
            ThisThread::sleep_for(50ms);
            continue;
        }

        char uidStr[9];
        snprintf(uidStr, sizeof(uidStr), "%02X%02X%02X%02X", 
                 RfChip.uid.uidByte[0], RfChip.uid.uidByte[1], 
                 RfChip.uid.uidByte[2], RfChip.uid.uidByte[3]);

        for (int i = 0; i < uidListSize; i++) {
            if (strcmp(uidStr, uidList[i].uid) == 0) {
                
            send_message(uart2, "000");
            send_message(uart3, "000");
                //send_message(uart2, uidList[i].label);
                //send_message(uart3, uidList[i].label);
                break;
            }
        }

        RfChip.PICC_HaltA();
    }
}
