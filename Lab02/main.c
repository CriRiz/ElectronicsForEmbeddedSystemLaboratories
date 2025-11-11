#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_timestamp.h"

// UART parameters
#define BAUDRATE    300
#define NBIT        8
#define NSTOPBIT    1
#define NOPARITY    0
#define EVENPARITY  1   
#define ODDPARITY   2
#define PARITY      NOPARITY

#define PROJECT2

#ifdef PROJECT1
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

        printf("Ricevuto: %c (0x%02X)\n", result, result);
    }

    return 0;
}
#endif

#ifdef PROJECT2
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
        for (int i = 0; i < NBIT; i++)
            // | è l'operatore OR bit a bit
            result |= (c[i] << i);

        printf("Ricevuto: %c (0x%02X)\n", result, result);
    }

    return 0;
}
#endif

#ifdef PROJECT3
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
        for (int i = 0; i < NBIT; i++)
            // | è l'operatore OR bit a bit
            //result |= (c[i] << i);
            IOWR_ALTERA_AVALON_PIO_DATA(NIOS_UARTTX_BASE,c[i])
        

        //printf("Ricevuto: %c (0x%02X)\n", result, result);
    }

    return 0;
}
#endif
