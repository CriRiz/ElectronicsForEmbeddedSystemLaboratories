#include <stdio.h>
#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <sys/alt_timestamp.h>

int main()
{
    printf("Starting pin toggle program\n");
    // Controllo presenza del timer
    if (alt_timestamp_start() < 0) {
        printf("Timer not available\n");
        exit(0);
    }
    
    int freq = alt_timestamp_freq();
    printf("Timer frequency: %d ticks per second\n", freq);

    // Durata del ritardo in ticks
    const int DELAY_TICKS = freq / 10; 
    int pin_value = 0;

    while (1) {
        // Cambio il valore del pin
        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, pin_value);

        // Valore complementato per il prossimo ciclo
        pin_value ^= 1;

        // Attesa
        alt_timestamp_start();
        while (alt_timestamp() < DELAY_TICKS)
            ;
    }

    return 0;
}
