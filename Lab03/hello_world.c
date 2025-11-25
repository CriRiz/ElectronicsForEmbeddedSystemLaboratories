#include "altera_avalon_pio_regs.h"
#include "string.h"
#include "sys/alt_timestamp.h"
#include "system.h"
#include <stdint.h>
#include <stdio.h>

#define UART_0_BASE 0x8001060

#define UART_0_RX_REG (UART_0_BASE + 0)
#define UART_0_TX_REG (UART_0_BASE + 4)
#define UART_0_ST_REG (UART_0_BASE + 8)
#define UART_0_CNT_REG (UART_0_BASE + 12)
#define UART_0_DIV_REG (UART_0_BASE + 16)

/*
        rxdata 0x08001060
        txdata 0x08001064
        status 0x08001068
        control 0x0800106C
        divisor 0x08001070
*/

#define NBIT 8
#define NSTOPBIT 1
#define NOPARITY 0
#define EVENPARITY 1
#define ODDPARITY 2

#define CLOCK_FREQUENCY 50000000

// Util functions

void print_bin(uint8_t x) {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (x >> i) & 1);
  }
  printf("\n");
}

void print_bin16(uint16_t x) {
  for (int i = 15; i >= 0; i--) {
    printf("%d", (x >> i) & 1);
  }
  printf("\n");
}

#define PROJECT5_2

#ifdef PROJECT1

#define BAUDRATE 115200
#define PARITY NOPARITY

int main() {
  // NIOS II is 32 bit, but UART is mapped on the lower 16 bits

  uint16_t rxdata = *((volatile uint32_t *)UART_0_RX_REG) & 0xFFFF; //La maschera non dovrebbe essere 0xFF?
  uint16_t txdata = *((volatile uint32_t *)UART_0_TX_REG) & 0xFFFF; //La maschera non dovrebbe essere 0xFF?
  uint16_t stdata = *((volatile uint32_t *)UART_0_ST_REG) & 0xFFFF;
  uint16_t cntdata = *((volatile uint32_t *)UART_0_CNT_REG) & 0xFFFF;
  uint16_t divdata = *((volatile uint32_t *)UART_0_DIV_REG) & 0xFFFF; // Qui non ci dovrebbe essere la maschera

  printf("RX DATA: ");
  print_bin16(rxdata);

  printf("TX DATA: ");
  print_bin16(txdata);

  printf("STATUS DATA: ");
  print_bin16(stdata);

  printf("CONTROLLER DATA: ");
  print_bin16(cntdata);

  printf("DIV DATA: ");
  print_bin16(divdata);

  return 0;
}

#endif

#ifdef PROJECT1Cri
int main(){
    volatile int *base = (int*) UART_0_BASE;
    int offRX, offTX, offStat, offContr, offDiv, dataRX, dataTX, dataStat, dataContr, dataDiv;
    offRX = 0;
    offTX = 1;
    offStat = 2;
    offContr = 3;
    offDiv = 4;


    dataRX = *(base+offRX);
    dataRX = dataRX & 0x000000ff;
    dataTX = *(base+offTX);
    dataTX = dataTX & 0x000000ff;
    dataStat = *(base+offStat);
    dataStat = dataStat & 0x00000fff;
    dataContr = *(base+offContr);
    dataContr = dataContr & 0x00000fff;
    dataDiv = *(base+offDiv);
    printf("Indirizzo base:     0x%08x (%d)\nIndirizzo RXDATA:       0x%08x (%d) - valore = %d\nIndirizzo TXDATA:       0x%08x (%d) - valore = %d\nIndirizzo STATUS:       0x%08x (%d) - valore = 0x%04x\nIndirizzo CONTROL:      0x%08x (%d) - valore = 0x%04x\nIndirizzo DIVISOR:      0x%08x (%d) - valore = %d\n",
        (int) base, (int) base,
        (int) offRX, (int) offRX, dataRX,
        (int) offTX, (int) offTX, dataTX,
        (int) offStat, (int) offStat, dataStat,
        (int) offContr, (int) offContr, dataContr,
        (int) offDiv, (int) offDiv, dataDiv);
    return 0;
}
#endif

/*Project #2
The UART peripheral is customized in Platform Designer to have a configurable baud rate. It means a DIVISOR
register is present (register 4) to scale the clock frequency. The default value of the DIVISOR at generation time
is to give a baud rate of 115200.
1. Compute the value of the DIVISOR to get a baud rate of 115200, starting from a clock frequency of
50MHz and compare it with the value obtained when reading it in Project #1.
2. Compute the value of the DIVISOR to get a baud rate of 2400. Write a software program to write the
new value to the DIVISOR register, read it again, and display the new value to verify that writing was
correct.

formula: (fck/BR)-1

DIVISOR             433
BAUDRATE effettivo  115207
*/

#ifdef PROJECT2_1

#define BAUDRATE 115200
#define FREQ  50000000
#define PARITY NOPARITY

int main() {
  volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG; // indirizzo di DIVISOR
  uint16_t divdata = (FREQ/BAUDRATE)-1;

  *ptr_div = divdata;

  divdata = *((volatile uint32_t *)UART_0_DIV_REG);

  printf("Valore di div modificato: %d (0x%08x)\n", (int) divdata, (int) divdata);

  return 0;
}

#endif

#ifdef PROJECT2_2

#define BAUDRATE 2400
#define FREQ  50000000
#define PARITY NOPARITY

int main() {
  volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG; // indirizzo di DIVISOR
  uint16_t divdata = (FREQ/BAUDRATE)-1;

  *ptr_div = divdata;

  divdata = *((volatile uint32_t *)UART_0_DIV_REG);

  printf("Valore di div modificato: %d (0x%08x)\n\n\n\n\n", (int) divdata, (int) divdata);

  uint16_t rxdata = *((volatile uint32_t *)UART_0_RX_REG) & 0xFFFF; //La maschera non dovrebbe essere 0xFF?
  uint16_t txdata = *((volatile uint32_t *)UART_0_TX_REG) & 0xFFFF; //La maschera non dovrebbe essere 0xFF?
  uint16_t stdata = *((volatile uint32_t *)UART_0_ST_REG) & 0xFFFF;
  uint16_t cntdata = *((volatile uint32_t *)UART_0_CNT_REG) & 0xFFFF;
  uint16_t divdata1 = *((volatile uint32_t *)UART_0_DIV_REG) & 0xFFFF; // Qui non ci dovrebbe essere la maschera

  printf("RX DATA: ");
  print_bin16(rxdata);

  printf("TX DATA: ");
  print_bin16(txdata);

  printf("STATUS DATA: ");
  print_bin16(stdata);

  printf("CONTROLLER DATA: ");
  print_bin16(cntdata);

  printf("DIV DATA: ");
  print_bin16(divdata1);

  return 0;
}

#endif

#ifdef PROJECT3_1

#define BAUDRATE 2400
#define PARITY EVENPPARITY

int main() {
  char msg = 'f';

  volatile uint32_t *ptr_rx = (volatile uint32_t *)UART_0_RX_REG;
  volatile uint32_t *ptr_tx = (volatile uint32_t *)UART_0_TX_REG;
  volatile uint32_t *ptr_sts = (volatile uint32_t *)UART_0_ST_REG;
  volatile uint32_t *ptr_cnt = (volatile uint32_t *)UART_0_CNT_REG;
  volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG;

  // Configuration

  // The UART core's parity, data bits and stop bits are configurable.
  // These settings are fixed at system generation time; they cannot
  // be altered via the register file !!

  // Set baudrate
  *ptr_div |= (uint16_t)0x5160;

  // 	1st point
  printf("Status before transmission: ");
  print_bin16((uint16_t)*ptr_sts);

  // wait trdy
  // while (((*ptr_sts) & (1 << 6)) == 0);

  // send msg
  *ptr_tx = (uint32_t)msg;

  printf("Status after transmission: ");
  print_bin16((uint16_t)*ptr_sts);

  return 0;
}

#endif

#ifdef PROJECT3_1_1

#define BAUDRATE 2400
#define PARITY EVENPPARITY

int main() {
  char msg = 'f';

  volatile uint32_t *ptr_rx = (volatile uint32_t *)UART_0_RX_REG;
  volatile uint32_t *ptr_tx = (volatile uint32_t *)UART_0_TX_REG;
  volatile uint32_t *ptr_sts = (volatile uint32_t *)UART_0_ST_REG;
  volatile uint32_t *ptr_cnt = (volatile uint32_t *)UART_0_CNT_REG;
  volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG;

  // Configuration

  // The UART core's parity, data bits and stop bits are configurable.
  // These settings are fixed at system generation time; they cannot
  // be altered via the register file !!

  // Set baudrate
  *ptr_div |= (uint16_t)0x5160;

  // ! USE OSCILLOSCOPE

  for (int i = 0; i < 3; i++) {

    // wait trdy
    //while (((*ptr_sts) & (1 << 6)) == 0);

    // send msg
    *ptr_tx = (uint32_t)(msg + i);
  }

  return 0;
}

#endif

#ifdef PROJECT3_2

int main() {
  char msg = 'f';

  volatile uint32_t *ptr_rx = (volatile uint32_t *)UART_0_RX_REG;
  volatile uint32_t *ptr_tx = (volatile uint32_t *)UART_0_TX_REG;
  volatile uint32_t *ptr_sts = (volatile uint32_t *)UART_0_ST_REG;
  volatile uint32_t *ptr_cnt = (volatile uint32_t *)UART_0_CNT_REG;
  volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG;

  // Configuration

  // The UART core's parity, data bits and stop bits are configurable.
  // These settings are fixed at system generation time; they cannot
  // be altered via the register file !!

  // Set baudrate
  *ptr_div |= (uint16_t)0x5160;

  // ! USE OSCILLOSCOPE

  printf("Status before transmission: ");
  print_bin16((uint16_t)*ptr_sts);

  //for (int i = 0; i < 2; i++) {

    // wait trdy
    //while (((*ptr_sts) & (1 << 6)) == 0);

    // send msg
  //}

  *ptr_tx = (uint32_t)(msg + 0);
  *ptr_tx = (uint32_t)(msg + 1);

  printf("Status after transmission: ");
  print_bin16((uint16_t)*ptr_sts);

  return 0;
}

#endif

#ifdef PROJECT3_3

int main() {
  char msg = 'f';

  volatile uint32_t *ptr_rx = (volatile uint32_t *)UART_0_RX_REG;
  volatile uint32_t *ptr_tx = (volatile uint32_t *)UART_0_TX_REG;
  volatile uint32_t *ptr_sts = (volatile uint32_t *)UART_0_ST_REG;
  volatile uint32_t *ptr_cnt = (volatile uint32_t *)UART_0_CNT_REG;
  volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG;

  // Configuration

  // The UART core's parity, data bits and stop bits are configurable.
  // These settings are fixed at system generation time; they cannot
  // be altered via the register file !!

  // Set baudrate
  *ptr_div |= (uint16_t)0x5160;

  // ! USE OSCILLOSCOPE

  printf("Status before transmission: ");
  print_bin16((uint16_t)*ptr_sts);

  /*for (int i = 0; i < 3; i++) {

    // wait trdy
    //while (((*ptr_sts) & (1 << 6)) == 0);

    // send msg

  }*/

  *ptr_tx = (uint32_t)(msg + 0);
  *ptr_tx = (uint32_t)(msg + 1);
  *ptr_tx = (uint32_t)(msg + 2);
  printf("Status after transmission: ");
  print_bin16((uint16_t)*ptr_sts);

  return 0;
}

#endif

#ifdef PROJECT4_1

int main() {
  char msg[50] = "My name is Gianluca";

  volatile uint32_t *ptr_rx = (volatile uint32_t *)UART_0_RX_REG;
  volatile uint32_t *ptr_tx = (volatile uint32_t *)UART_0_TX_REG;
  volatile uint32_t *ptr_sts = (volatile uint32_t *)UART_0_ST_REG;
  volatile uint32_t *ptr_cnt = (volatile uint32_t *)UART_0_CNT_REG;
  volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG;

  // Configuration

  // The UART core's parity, data bits and stop bits are configurable.
  // These settings are fixed at system generation time; they cannot
  // be altered via the register file !!

  // Set baudrate
  *ptr_div |= (uint16_t)0x5160;

  // ! USE OSCILLOSCOPE

  printf("Status before transmission: ");
  print_bin16((uint16_t)*ptr_sts);

  for (int i = 0; i < strlen(msg); i++) {

    // wait trdy
    while (((*ptr_sts) & (1 << 6)) == 0);

    // send msg
    *ptr_tx = (uint32_t)(msg[i]);
  }

  printf("Status after transmission: ");
  print_bin16((uint16_t)*ptr_sts);

  return 0;
}

#endif


#ifdef PROJECT5_1

#define RRDY_MASK       (1 << 7)   // Receive Ready
#define TRDY_MASK       (1 << 6)   // Transmit Ready

int main() {
	IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);
    volatile uint32_t *ptr_rx  = (volatile uint32_t *)UART_0_RX_REG;
    volatile uint32_t *ptr_tx  = (volatile uint32_t *)UART_0_TX_REG;
    volatile uint32_t *ptr_sts = (volatile uint32_t *)UART_0_ST_REG;
    volatile uint32_t *ptr_cnt = (volatile uint32_t *)UART_0_CNT_REG;
    volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG;

    //baudrate = 2400
    uint16_t divdata = 0x5160;
    *ptr_div = divdata;

    //Disabilita interrupt
    *ptr_cnt = 0;

    printf("UART configurata a 2400 baud, 8E1, polling.\n");

    while (1) {
        //Stampa STATUS prima della lettura
        printf("STATUS prima RX: ");

        print_bin16((uint16_t)(*ptr_sts));
        //Polling: aspetta che RRDY sia settato

        while (((*ptr_sts) & RRDY_MASK) == 0) {
            // busy wait
        }
        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 1);
        //Leggi RXDATA
        uint8_t rxchar = (uint8_t)(*ptr_rx & 0xFF);
        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);

        //Stampa STATUS dopo la lettura
        printf("STATUS dopo RX:  ");
        print_bin16((uint16_t)(*ptr_sts));

        //Stampa il carattere ricevuto
        printf("Carattere ricevuto: '%c' (ASCII=%d)\n", rxchar, rxchar);
    }

    return 0;
}
#endif

#ifdef PROJECT5_2

#define RRDY_MASK       (1 << 7)   // Receive Ready
#define TRDY_MASK       (1 << 6)   // Transmit Ready

int main() {
	IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);
    volatile uint32_t *ptr_rx  = (volatile uint32_t *)UART_0_RX_REG;
    volatile uint32_t *ptr_sts = (volatile uint32_t *)UART_0_ST_REG;
    volatile uint32_t *ptr_cnt = (volatile uint32_t *)UART_0_CNT_REG;
    volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG;

    //baudrate 2400
    uint16_t divdata = 0x5160;
    *ptr_div = divdata;

    //Disabilita interrupt
    *ptr_cnt = 0;

    printf("UART configurata a 2400 baud, 8E1, senza polling RRDY.\n");

    int freq = alt_timestamp_freq();
    const int DELAY_TICKS = freq/2;

    while (1) {

    	IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 1);

        /*alt_timestamp_start();
        while (alt_timestamp() < DELAY_TICKS);
*/
        //Leggi RXDATA direttamente (senza check RRDY)
        uint8_t rxchar = (uint8_t)(*ptr_rx & 0xFF);
    	IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);

        //Stampa carattere ricevuto
        printf("Carattere ricevuto: '%c' (ASCII=%d)\n", rxchar, rxchar);
    }

    return 0;
}
#endif
