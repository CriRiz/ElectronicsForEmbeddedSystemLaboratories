#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_timestamp.h"

// UART parameters
//#define BAUDRATE    9600
#define NBIT        8
#define NSTOPBIT    1
#define NOPARITY    0
#define EVENPARITY  1
#define ODDPARITY   2
#define PARITY      NOPARITY

#define PROJECT5_Cri

#ifdef PROJECT1

// Only on quartus

#endif

#ifdef PROJECT4_1 //

#define BAUDRATE 300

int main() {

    int ticks_per_sec = alt_timestamp_freq();
    int ticks_per_bit = ticks_per_sec / BAUDRATE;

    int c[NBIT];
    int val;

    printf("UART RX ready.\n");

    while (1) {

        //-----------------------------------------
        // 1. Aspetta START BIT (linea bassa)
        //-----------------------------------------
        do {
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        } while (val == 1);

        //-----------------------------------------
        // 2. Aspetta finché il timer non ha raggiunto metà del tempo di un bit, così posso campionare lo start bit nel punto più stabile.
        //-----------------------------------------
        alt_timestamp_start();
        while (alt_timestamp() < (ticks_per_bit >> 1)) {}

        // Controllo sull'effettivo start
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        if (val != 0) {
            continue;
        }

        //-----------------------------------------
        // 3. Precalcolo degli istanti di campionamento
        //-----------------------------------------
        alt_timestamp_start();
        int sample_times[NBIT + NSTOPBIT];
        for (int i = 0; i < NBIT + NSTOPBIT; i++)
            sample_times[i] = (i + 1) * ticks_per_bit;

        //-----------------------------------------
        // 4. Leggi i bit di DATA
        //-----------------------------------------
        for (int i = 0; i < NBIT; i++) {
            while (alt_timestamp() < sample_times[i]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[i] = val;        // c[0] = LSB
        }

        //-----------------------------------------
        // 5. Leggi STOP BIT e verifica
        //-----------------------------------------
        while (alt_timestamp() < sample_times[NBIT]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;

        if (val != 1) {
            printf("ERRORE: stop bit non valido!\n");
            continue;
        }

        //-----------------------------------------
        // 6. Ricostruisci carattere
        //-----------------------------------------
        int result = 0;
        for (int i = 0; i < NBIT; i++)
            // | è l'operatore OR bit a bit
            result |= (c[i] << i);

        printf("Ricevuto: %c (0x%02X) (%d)\n", result, result, result);
    }

    return 0;
}
#endif

#ifdef PROJECT4_2 // With loop unrolling

#define BAUDRATE 300

int main() {

    int ticks_per_sec = alt_timestamp_freq();
    int ticks_per_bit = ticks_per_sec / BAUDRATE;

    int c[NBIT];
    int val;

    printf("UART RX ready.\n");

    while (1) {

        //-----------------------------------------
        // 1. Aspetta START BIT (linea bassa)
        //-----------------------------------------
        do {
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        } while (val == 1);

        //-----------------------------------------
        // 2. Aspetta finché il timer non ha raggiunto metà del tempo di un bit, così posso campionare lo start bit nel punto più stabile.
        //-----------------------------------------
        alt_timestamp_start();
        while (alt_timestamp() < (ticks_per_bit >> 1)) {}

        // Controllo sull'effettivo start
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        if (val != 0) {
            continue;
        }

        //-----------------------------------------
        // 3. Precalcolo degli istanti di campionamento
        //-----------------------------------------
        alt_timestamp_start();
        int sample_times[NBIT + NSTOPBIT];
        for (int i = 0; i < NBIT + NSTOPBIT; i++)
            sample_times[i] = (i + 1) * ticks_per_bit;

        //-----------------------------------------
        // 4. Leggi i bit di DATA - loop unrolling

            while (alt_timestamp() < sample_times[0]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[0] = val;

            while (alt_timestamp() < sample_times[1]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[1] = val;

            while (alt_timestamp() < sample_times[2]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[2] = val;

            while (alt_timestamp() < sample_times[3]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[3] = val;

            while (alt_timestamp() < sample_times[4]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[4] = val;

            while (alt_timestamp() < sample_times[5]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[5] = val;

            while (alt_timestamp() < sample_times[6]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[6] = val;

            while (alt_timestamp() < sample_times[7]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[7] = val;


        //-----------------------------------------
        // 5. Leggi STOP BIT e verifica
        //-----------------------------------------
        while (alt_timestamp() < sample_times[NBIT]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;

        if (val != 1) {
            printf("ERRORE: stop bit non valido!\n");
            continue;
        }

        //-----------------------------------------
        // 6. Ricostruisci carattere
        //-----------------------------------------
        int result = 0;
        for (int i = 0; i < NBIT; i++)
            // | è l'operatore OR bit a bit
            result |= (c[i] << i);

        printf("Ricevuto: %c (0x%02X) (%d) (%d%d%d%d%d%d%d%d)\n", result, result, result, c[7], c[6], c[5], c[4], c[3], c[2], c[1], c[0]);
    }

    return 0;
}
#endif

#ifdef PROJECT5_OLD

#define BAUDRATE 300

int main() {

    int ticks_per_sec = alt_timestamp_freq();
    int ticks_per_bit = ticks_per_sec / BAUDRATE;

    int c[NBIT];
    int val;

    printf("UART RX ready.\n");

    while (1) {

        //-----------------------------------------
        // 1. Aspetta START BIT (linea bassa)
        //-----------------------------------------
        do {
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        } while (val == 1);

        //-----------------------------------------
        // 2. Aspetta finché il timer non ha raggiunto metà del tempo di un bit, così posso campionare lo start bit nel punto più stabile.
        //-----------------------------------------
        alt_timestamp_start();
        while (alt_timestamp() < (ticks_per_bit >> 1)) {}

        // Controllo sull'effettivo start
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        if (val != 0) {
            continue;
        }

        //-----------------------------------------
        // 3. Precalcolo degli istanti di campionamento
        //-----------------------------------------
        alt_timestamp_start();
        int sample_times[NBIT + NSTOPBIT];
        for (int i = 0; i < NBIT + NSTOPBIT; i++)
            sample_times[i] = (i + 1) * ticks_per_bit;

        //-----------------------------------------
        // 4. Leggi i bit di DATA

            while (alt_timestamp() < sample_times[0]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[0] = val;

            while (alt_timestamp() < sample_times[1]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[1] = val;

            while (alt_timestamp() < sample_times[2]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[2] = val;

            while (alt_timestamp() < sample_times[3]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[3] = val;

            while (alt_timestamp() < sample_times[4]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[4] = val;

            while (alt_timestamp() < sample_times[5]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[5] = val;

            while (alt_timestamp() < sample_times[6]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[6] = val;

            while (alt_timestamp() < sample_times[7]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[7] = val;


        //-----------------------------------------
        // 5. Leggi STOP BIT e verifica
        //-----------------------------------------
        while (alt_timestamp() < sample_times[NBIT]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;

        if (val != 1) {
            printf("ERRORE: stop bit non valido!\n");
            continue;
        }

        //-----------------------------------------
        // 6. Ricostruisci carattere
        //-----------------------------------------
        int result = 0;
        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, 0);
        for (int j= 0; j < NBIT; j++){
            // | è l'operatore OR bit a bit
            result |= (c[j] << j);
            IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[j]);
            // mettere timer e forzare pin alto
        }

            printf("Ricevuto: %c (0x%02X) (%d) (%d%d%d%d%d%d%d%d);\n", result, result, result, c[7], c[6], c[5], c[4], c[3], c[2], c[1], c[0]);
    }

    return 0;
}
#endif


#ifdef PROJECT5_NEW

#define BAUDRATE 300 // Overwrite old value

int main() {

    int ticks_per_sec = alt_timestamp_freq();
    int ticks_per_bit = ticks_per_sec / BAUDRATE;

    int c[NBIT];
    int val;

    printf("UART RX ready.\n");

    while (1) {

        //-----------------------------------------
        // 1. Aspetta START BIT (linea bassa)
        //-----------------------------------------
        do {
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        } while (val == 1);

        //-----------------------------------------
        // 2. Aspetta finché il timer non ha raggiunto metà del tempo di un bit, così posso campionare lo start bit nel punto più stabile.
        //-----------------------------------------
        alt_timestamp_start();
        while (alt_timestamp() < (ticks_per_bit >> 1)) {}

        // Controllo sull'effettivo start
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        if (val != 0) {
            continue;
        }

        //-----------------------------------------
        // 3. Precalcolo degli istanti di campionamento
        //-----------------------------------------
        alt_timestamp_start();
        int sample_times[NBIT + NSTOPBIT];
        for (int i = 0; i < NBIT + NSTOPBIT; i++)
            sample_times[i] = (i + 1) * ticks_per_bit + (ticks_per_bit >> 1); // + (ticks_per_bit >> 1) is added to mantain the phase

        //-----------------------------------------
        // 4. Leggi i bit di DATA

        while (alt_timestamp() < sample_times[0]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        c[0] = val;

        while (alt_timestamp() < sample_times[1]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        c[1] = val;

        while (alt_timestamp() < sample_times[2]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        c[2] = val;

        while (alt_timestamp() < sample_times[3]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        c[3] = val;

        while (alt_timestamp() < sample_times[4]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        c[4] = val;

        while (alt_timestamp() < sample_times[5]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        c[5] = val;

        while (alt_timestamp() < sample_times[6]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        c[6] = val;

        while (alt_timestamp() < sample_times[7]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        c[7] = val;


        //-----------------------------------------
        // 5. Leggi STOP BIT e verifica
        //-----------------------------------------
        while (alt_timestamp() < sample_times[NBIT]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;

        if (val != 1) {
            printf("ERRORE: stop bit non valido!\n");
            continue;
        }

        #ifdef DEBUG
        int result = 0;
        for (int i = 0; i < NBIT; i++)
            // | è l'operatore OR bit a bit
            result |= (c[i] << i);

        printf("Ricevuto da NIOS II: %c (0x%02X) (%d) (%d%d%d%d%d%d%d%d)\n", result, result, result, c[7], c[6], c[5], c[4], c[3], c[2], c[1], c[0]);
        #endif

        // --- TX PHASE

        //-----------------------------------------
        // 6. Invia Carattere
        //-----------------------------------------
        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, 1); // Linea ALTA

        //-----------------------------------------
        // 7. Precalcolo degli istanti di invio
        //-----------------------------------------
        // NSTOPBIT at the fist is the NSTARTBIT
        for (int i = 0; i < NSTOPBIT + NBIT; i++)
            sample_times[i] = (i + 1) * ticks_per_bit;


        // START BIT TX
        alt_timestamp_start();

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, 0);
        while (alt_timestamp() < sample_times[0]) {}

        // DATA BITs TX
        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[0]);
        while (alt_timestamp() < sample_times[1]) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[1]);
        while (alt_timestamp() < sample_times[2]) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[2]);
        while (alt_timestamp() < sample_times[3]) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[3]);
        while (alt_timestamp() < sample_times[4]) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[4]);
        while (alt_timestamp() < sample_times[5]) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[5]);
        while (alt_timestamp() < sample_times[6]) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[6]);
        while (alt_timestamp() < sample_times[7]) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[7]);
        while (alt_timestamp() < sample_times[8]) {}

        // "STOP BIT" TX
        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, 1);


        int result = 0;
        for (int i = 0; i < NBIT; i++)
            // | è l'operatore OR bit a bit
            result |= (c[i] << i);

        printf("Mandato da NIOS II: %c (0x%02X) (%d) (%d%d%d%d%d%d%d%d)\n", result, result, result, c[7], c[6], c[5], c[4], c[3], c[2], c[1], c[0]);
    }

    return 0;
}
#endif

#ifdef PROJECT5_Cri

#define BAUDRATE 19200

#include <stdint.h>
int main() {

    int ticks_per_sec = alt_timestamp_freq();
    int ticks_per_bit = ticks_per_sec / BAUDRATE;

    int c[NBIT];
    int val;

    IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, 1);
    printf("UART RX ready.\n");

    while (1) {

        //-----------------------------------------
        // 1. Aspetta START BIT (linea bassa)
        //-----------------------------------------
        do {
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;

        } while (val == 1);

        //-----------------------------------------
        // 2. Aspetta finché il timer non ha raggiunto metà del tempo di un bit, così posso campionare lo start bit nel punto più stabile.
        //-----------------------------------------
        alt_timestamp_start();
        while (alt_timestamp() < (ticks_per_bit >> 1)) {}

        // Controllo sull'effettivo start
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
        if (val != 0) {
            continue;
        }

        //-----------------------------------------
        // 3. Precalcolo degli istanti di campionamento
        //-----------------------------------------
        alt_timestamp_start();
        int sample_times[NBIT + NSTOPBIT];
        for (int i = 0; i < NBIT + NSTOPBIT; i++)
        	sample_times[i] = (i + 1) * ticks_per_bit;

        //-----------------------------------------
        // 4. Leggi i bit di DATA

            while (alt_timestamp() < sample_times[0]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[0] = val;

            while (alt_timestamp() < sample_times[1]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[1] = val;

            while (alt_timestamp() < sample_times[2]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[2] = val;

            while (alt_timestamp() < sample_times[3]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[3] = val;

            while (alt_timestamp() < sample_times[4]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[4] = val;

            while (alt_timestamp() < sample_times[5]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[5] = val;

            while (alt_timestamp() < sample_times[6]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[6] = val;

            while (alt_timestamp() < sample_times[7]) {}
            val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
            c[7] = val;


        //-----------------------------------------
        // 5. Leggi STOP BIT e verifica
        //-----------------------------------------
        while (alt_timestamp() < sample_times[NBIT]) {}
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;

        if (val != 1) {
            printf("ERRORE: stop bit non valido!\n");
            continue;
        }

        //-----------------------------------------
        // 6. Ricostruisci carattere
        //-----------------------------------------
        int result = 0;
        result |= (c[0] << 0);
        result |= (c[1] << 1);
        result |= (c[2] << 2);
        result |= (c[3] << 3);
        result |= (c[4] << 4);
        result |= (c[5] << 5);
        result |= (c[6] << 6);
        result |= (c[7] << 7);

        printf("Ricevuto: %c (0x%02X) (%d) (%d%d%d%d%d%d%d%d);\n", result, result, result, c[7], c[6], c[5], c[4], c[3], c[2], c[1], c[0]);

        alt_timestamp_start();

        //START BIT
        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, 0);
        while (alt_timestamp() < ticks_per_bit) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[0]);
        while (alt_timestamp() < ticks_per_bit*2) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[1]);
        while (alt_timestamp() < ticks_per_bit*3) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[2]);
        while (alt_timestamp() < ticks_per_bit*4) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[3]);
        while (alt_timestamp() < ticks_per_bit*5) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[4]);
        while (alt_timestamp() < ticks_per_bit*6) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[5]);
        while (alt_timestamp() < ticks_per_bit*7) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[6]);
        while (alt_timestamp() < ticks_per_bit*8) {}

        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, c[7]);
        while (alt_timestamp() < ticks_per_bit*9) {}

        //STOP BIT = 1
        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE, 1);
        while (alt_timestamp() < ticks_per_bit*10) {}

    }

    return 0;
}
#endif
