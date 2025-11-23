#include "altera_avalon_pio_regs.h"
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

#define BAUDRATE 115200
#define NBIT 8
#define NSTOPBIT 1
#define NOPARITY 0
#define EVENPARITY 1
#define ODDPARITY 2
#define PARITY NOPARITY

#define CLOCK_FREQUENCY 50000000

// Util functions

void print_bin(uint8_t x) {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (x >> i) & 1);
  }
  printf("\n");
}

#define PROJECT5

#ifndef PROJECT1

int main() {
  uint8_t rxdata = *((int *)UART_0_RX_REG);
  uint8_t txdata = *((int *)UART_0_TX_REG);
  uint8_t stdata = *((int *)UART_0_ST_REG);
  uint8_t cntdata = *((int *)UART_0_CNT_REG);
  uint8_t divdata = *((int *)UART_0_DIV_REG);

  print_bin(rxdata);
  print_bin(txdata);
  print_bin(stdata);
  print_bin(cntdata);
  print_bin(divdata);

  return 0;
}

#endif

#ifndef PROJECT2

int main() {
  volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG;

  // TODO

  return 0;
}

#endif

#ifndef PROJECT3

#define BAUDRATE 2400
#define PARITY EVENPPARITY

int main() {
  char msg = 'f';

  volatile uint32_t *ptr_rx = (volatile uint32_t *)UART_0_RX_REG;
  volatile uint32_t *ptr_tx = (volatile uint32_t *)UART_0_TX_REG;
  volatile uint32_t *ptr_sts = (volatile uint32_t *)UART_0_ST_REG;
  volatile uint32_t *ptr_cnt = (volatile uint32_t *)UART_0_CNT_REG;
  volatile uint32_t *ptr_div = (volatile uint32_t *)UART_0_DIV_REG;

  // Check if TRDY is 1 (status_register[6])
  if ((*ptr_sts) & (1 << 6))
    (*ptr_sts) &= ~(1 << 6);
  else {
    (*ptr_sts) |= (1 << 4); // Report overrun TOE (status_register[4])
  }

  // no ongoing transmission TMT == 1 (statis_register[5]
  while (!((*ptr_sts) & (1 << 5)))
    ;

  // Set busy
  (*ptr_sts) |= (1 << 6);

  // Start transmission
  // TX High at fist
  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 1);
  // Start bit
  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);

  // TODO COMPLY TO BAUDRATE!!
  for (int i = 0; i < NBIT; i++) {
    IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, (msg >> i) & 1);
  }

  return 0;
}

#endif
