#include "mbed.h"
#include "MFRC522.h"

#define MF_RESET    D8  // pin du Nucleo branchée à la pin RST du RC522

const char bonUID[4] = {0x90, 0xCF, 0x94, 0x75};

MFRC522    RfChip   (SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, MF_RESET);

// SPI_MOSI = D11
// SPI_MISO = D12
// SPI_SCK = D13
// SPI_CS = D10
// MF_RESET = D8

int main(void) {

    RfChip.PCD_Init();

    while (true) {

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
