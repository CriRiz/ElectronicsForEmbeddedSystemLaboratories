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

void print_bin16(uint16_t x) {
  for (int i = 15; i >= 0; i--) {
    printf("%d", (x >> i) & 1);
  }
  printf("\n");
}

#define PROJECT5

#ifndef PROJECT1

int main() {
  // NIOS II is 32 bit, but UART is mapped on the lower 16 bits

  uint16_t rxdata = *((volatile uint32_t *)UART_0_RX_REG) & 0xFFFF;
  uint16_t txdata = *((volatile uint32_t *)UART_0_TX_REG) & 0xFFFF;
  uint16_t stdata = *((volatile uint32_t *)UART_0_ST_REG) & 0xFFFF;
  uint16_t cntdata = *((volatile uint32_t *)UART_0_CNT_REG) & 0xFFFF;
  uint16_t divdata = *((volatile uint32_t *)UART_0_DIV_REG) & 0xFFFF;

  printf("RX DATA: ");
  print_bin16(rxdata);

  printf("TX DATA: ");
  print_bin16(txdata);

  printf("STATUS DATA: ");
  print_bin16(stdata);

  printf("COUNT DATA: ");
  print_bin16(cntdata);

  printf("DIV DATA: ");
  print_bin16(divdata);

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

  // Read status before write something

  printf("Status before transmission:");
  print_bin(*ptr_sts);

  return 0;
}

#endif
