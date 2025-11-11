/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"

#define PROJECT4

// All useful datas
#define CLK  50
#define BAUDRATE 300 // bit/s da cambiare per vedere fino a quando non c'è perdita di informazioni
#define NBIT 8
#define NSTOPBIT 1
#define NOPARITY 0
#define EVENPARITY 1
#define ODDPARITY 2
#define PARITY NOPARITY

#ifdef PROJECT1
int main()
{
  printf("Hello Sandro, Gianluca, Pietro and Cri!\n");

  return 0;
}
#endif

// 32 bit integer number

#ifdef PROJECT2
int main(){
  int n = 8;
  int ticksPerSec = alt_timestamp_freq();
  int nticks, wticks, c[NBIT], t1, t2;
  int val;

  /*
  - while pin si high (UART idle) do nothing
  - when pin becomes low, start timer
  - after half bit, sample START BIT (check that it still low)
    - restart timer
  - loop n times
    - after one bit time, sample bit (in the middle), restart timer
  - after one bit time, sample parity or stop bits
  - return to the beginning
  */

  printf(" BaudRate = %d\n ticksPerSecond = %d\n ticksPerBit = %d\n totalBit = %d\n", BAUDRATE, ticksPerSec, (ticksPerSec/(BAUDRATE)), (NBIT+2));

  while (1){
    do{
      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
    }while ((val == 1));
    
    //------------------------------------------------------------------------------------------------
    alt_timestamp_start(); //inizio a contare quanto tempo passa
    nticks = ticksPerSec/(BAUDRATE);
    while(alt_timestamp()<(nticks/2+1)){} // se è ancora a 0 dopo metà boadrate allora è start bit
    //-------------------------------------------------------------------------------------------------
    val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE); // LETTURA
    val = val & 0x01;
    //-------------------------------------------------------------------------------------------------
    if (val == 0){
      while(alt_timestamp()<(nticks+1)){}
      for (int i = 0; i < NBIT; i++){
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
        val = val & 0x01;
        c[NBIT-1-i] = val; // parte da LSB
        while(alt_timestamp()<(nticks*(i+1)+1)){}
      }
      // controllare se stop è 1???
      // parity???
      printf("Char ");
      while(alt_timestamp()<(nticks*(NBIT+1))){}

    }

  }
	
	return 0;
}
#endif

#ifdef PROJECT3
int main(){
  int mask;
  int ticksPerSec = alt_timestamp_freq();
  int nticks = ticksPerSec/(BAUDRATE);
  int val;

  printf(" BaudRate = %d\n ticksPerSecond = %d\n ticksPerBit = %d\n totalBit = %d\n", BAUDRATE, ticksPerSec, (ticksPerSec/(BAUDRATE)), (NBIT+2));

  /*
  - while pin si high (UART idle) do nothing
  - when pin becomes low, start timer
  - after half bit, sample START BIT (check that it still low)
    - restart timer
  - loop n times
    - after one bit time, sample bit (in the middle), restart timer
  - after one bit time, sample parity or stop bits
  - return to the beginning
  */

  while (1){
    mask = 0x0;
	printf("Waiting for Startbit\n");

    do{
      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
    }while ((val == 1));
    
    //------------------------------------------------------------------------------------------------
    alt_timestamp_start(); //inizio a contare quanto tempo passa
    while(alt_timestamp()<(nticks/2)){} // se è ancora a 0 dopo metà boadrate allora è start bit
    //-------------------------------------------------------------------------------------------------
    val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE); // LETTURA
    val = val & 0x01;
    //-------------------------------------------------------------------------------------------------
    if (val == 0){
      while(alt_timestamp()<(nticks)){}
      for (int i = 0; i < NBIT; i++){
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
        val = val & 0x01;

        mask = mask | (val << i);

        while(alt_timestamp()<(nticks*(i+2))){}
      }
      // controllare se stop è 1???
      // parity???
      printf("Data: %X (%c) (%d)\n", mask, mask, mask);
      while(alt_timestamp()<(nticks*(NBIT+2))){}

    }

  }
	
	return 0;
}
#endif

#ifdef PROJECT4
int main(){
  int val, mask, t0, t1, t2, t3, t4, t5, t6, t7;
  int ticksPerSec = alt_timestamp_freq();
  int nticks = ticksPerSec/(BAUDRATE);
  t0 = nticks*2+1;
  t1 = nticks*3+1;
  t2 = nticks*4+1;
  t3 = nticks*5+1;
  t4 = nticks*6+1;
  t5 = nticks*7+1;
  t6 = nticks*8+1;
  t7 = nticks*9+1;

  printf(" BaudRate = %d\n ticksPerSecond = %d\n ticksPerBit = %d\n totalBit = %d\n", BAUDRATE, ticksPerSec, (ticksPerSec/(BAUDRATE)), (NBIT+2));


  /*
  - while pin si high (UART idle) do nothing
  - when pin becomes low, start timer
  - after half bit, sample START BIT (check that it still low)
    - restart timer
  - loop n times
    - after one bit time, sample bit (in the middle), restart timer
  - after one bit time, sample parity or stop bits
  - return to the beginning
  */

  while (1){
    mask = 0x0;
    do{
      printf("Waiting for Startbit\n");
      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
    }while ((val == 1));
    
    //------------------------------------------------------------------------------------------------
    alt_timestamp_start(); //inizio a contare quanto tempo passa
    while(alt_timestamp()<(nticks/2+1)){} // se è ancora a 0 dopo metà boadrate allora è start bit
    //-------------------------------------------------------------------------------------------------
    val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE); // LETTURA
    val = val & 0x01;
    //-------------------------------------------------------------------------------------------------
    if (val == 0){
      while(alt_timestamp()<(nticks+1)){}
      /*
      for (int i = 0; i < NBIT; i++){
        val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
        val = val & 0x01;

        mask = mask | (val << i);

        while(alt_timestamp()<(nticks*(i+1)+1)){}
      }*/
      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
      mask = mask | val;

      while(alt_timestamp()<(t0)){}

      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
      mask = mask | (val << 1);

      while(alt_timestamp()<(t1)){}

      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
      mask = mask | (val << 2);

      while(alt_timestamp()<(t2)){}

      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
      mask = mask | (val << 3);

      while(alt_timestamp()<(t3)){}

      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
      mask = mask | (val << 4);

      while(alt_timestamp()<(t4)){}

      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
      mask = mask | (val << 5);

      while(alt_timestamp()<(t5)){}

      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
      mask = mask | (val << 6);

      while(alt_timestamp()<(t6)){}

      val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
      val = val & 0x01;
      mask = mask | (val << 7);

      while(alt_timestamp()<(t7)){}


      // controllare se stop è 1???
      // parity???
      printf("Data: %X (%c) (%d)\n", mask, mask, mask);
      while(alt_timestamp()<(nticks*(NBIT+2))){}

    }

  }
	
	return 0;
}
#endif
