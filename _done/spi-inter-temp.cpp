/*
* Hi, I'm currently trying to send data from one STM32F4 board as a master to the
* other STM32F4 board which is the slave via SPI. At the moment I have written code
* for the master to transmit data, though I am not entirely sure whether I have
* configured it correctly and if it is actually sending the data. I have also made
* an attempt for the slave polling (ideally I'd like it as an interrupt but not sure
* where to start) the RXNE but it seems that the RXNE is never set or at least it
* doesn't see it. Anyone know what I'm doing wrong? Any help would be greatly
* appreciated. Thank you.
*
* Here is my code for the master:
*/

#include <stm32f4xx.h>
#include <stm32f4xx_spi.h>


void Delay(__IO uint32_t nCount) {
  while(nCount--) { }
}


void init_GPIO(void) {
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //Enable GPIOD peripheral clock

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12; //Select LED GPIO pins to configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //Set pins to output
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //Set GPIO clock speed
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //Set pin type to push/pull
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; //Set pullup/pulldown resistors to be inactive
  GPIO_Init(GPIOD, &GPIO_InitStruct); //Initialise GPIOD

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //Enable GPIOA peripheral clock

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; //Select pin PA0 (User Button) to configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //Set pin to input
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //Set GPIO clock speed
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //Set pin type to push/pull
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; //Enable pulldown resistor to detect high level
  GPIO_Init(GPIOA, &GPIO_InitStruct); //Initialise GPIOA
}


// this function initializes the SPI1 peripheral
void init_SPI1(void){

  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  // enable clock for used IO pins
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* configure pins used by SPI1
  * PA5 = SCK   PA6 = MISO   PA7 = MOSI
  */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  // connect SPI1 pins to SPI alternate function
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

  // enable clock for used IO pins
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

  /* Configure the chip select pin, in this case we will use PE7 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIOE->BSRRL |= GPIO_Pin_7; // set PE7 high

  // enable peripheral clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  /* configure SPI1 in Mode 0
  * CPOL = 0 --> clock is low when idle
  * CPHA = 0 --> data is sampled at the first edge
  */
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;     // transmit in master mode, NSS pin has to be always high
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;        // clock is low when idle
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;      // data sampled at first edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // SPI frequency is APB2 frequency / 4
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first
  SPI_Init(SPI1, &SPI_InitStruct);

  SPI_Cmd(SPI1, ENABLE); // enable SPI1
}


/*
* This funtion is used to transmit and receive data with SPI1
* data --> data to be transmitted returns received value
*/
uint8_t SPI1_send(uint8_t data){

  SPI1->DR = data; // write data to be transmitted to the SPI data register
  while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
  while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until receive complete
  while( SPI1->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore
  return SPI1->DR; // return received data from SPI data register
}


int main(void) {
  uint8_t i = 0;
  uint8_t received_val = 0;

  init_GPIO();
  init_SPI1();

  GPIOD->BSRRL = 0xF000; //Set PD12 through PD15 (BSRRL = Bit Set/Reset Register Low)
  Delay(0xF42400); //Wait
  GPIOD->BSRRH = 0xF000; //Reset PD12 through PD15 (BSRRH = Bit Set/Reset Register High)

  while(1) {
    //Check if bit 0 of input data register = '1' meaning button is currently pressed
    if(GPIOA->IDR & 0x0001) {
      if(i > 3) { i = 0; }
      else {
        switch(i) {
          //0x1000 = 0001000000000000
          //0x2000 = 0010000000000000
          //0x4000 = 0100000000000000
          //0x8000 = 1000000000000000
          case 0:

          GPIOD->BSRRL = 0x1000; //Set LED1 (Green)
          GPIOD->BSRRH = 0x8000; //Reset LED4 (Blue)
          break;

          case 1:
          GPIOD->BSRRL = 0x2000; //Set LED2 (Orange)
          GPIOD->BSRRH = 0x1000; //Reset LED1 (Green)
          break;

          case 2:
          GPIOD->BSRRL = 0x4000; //Set LED3 (Red)
          GPIOD->BSRRH = 0x2000; //Reset LED2 (Orange)
          break;

          case 3:
          GPIOD->BSRRL = 0x8000; //Set LED4 (Blue)
          GPIOD->BSRRH = 0x4000; //Reset LED3 (Red)
          break;
        }

        GPIOE->BSRRH |= GPIO_Pin_7; // set PE7 (CS) low
        SPI1_send(i);  // transmit data
        received_val = SPI1_send(0x00); // transmit dummy byte and receive data
        GPIOE->BSRRL |= GPIO_Pin_7; // set PE7 (CS) high
        i++;
        Delay(0x3D0900); //Add delay to debounce the switch
      }
    }
  }
}



/*
* Here is my code for the slave:
*/

#include <stm32f4xx.h>
#include <stm32f4xx_spi.h>


void Delay(__IO uint32_t nCount) {
  while(nCount--) { }
}


void init_GPIO(void) {
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //Enable GPIOD peripheral clock

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12; //Select LED GPIO pins to configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //Set pins to output
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //Set GPIO clock speed
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //Set pin type to push/pull
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; //Set pullup/pulldown resistors to be inactive
  GPIO_Init(GPIOD, &GPIO_InitStruct); //Initialise GPIOD


  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //Enable GPIOA peripheral clock

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; //Select pin PA0 (User Button) to configure
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //Set pin to input
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //Set GPIO clock speed
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //Set pin type to push/pull
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; //Enable pulldown resistor to detect high level
  GPIO_Init(GPIOA, &GPIO_InitStruct); //Initialise GPIOA
}


/* this function initializes the SPI1 peripheral */
void init_SPI1(void){

  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  // enable clock for used IO pins
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* configure pins used by SPI1
  * PA5 = SCK   PA6 = MISO   PA7 = MOSI
  */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  // connect SPI1 pins to SPI alternate function
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

  // enable clock for used IO pins
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

  /* Configure the chip select pin, in this case we will use PE7 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIOE->BSRRL |= GPIO_Pin_7; // set PE7 high

  // enable peripheral clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  /* configure SPI1 in Mode 0
  * CPOL = 0 --> clock is low when idle
  * CPHA = 0 --> data is sampled at the first edge
  */
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
  SPI_InitStruct.SPI_Mode = SPI_Mode_Slave;
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;        // clock is low when idle
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;      // data sampled at first edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // SPI frequency is APB2 frequency / 4
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first
  SPI_Init(SPI1, &SPI_InitStruct);

  SPI_Cmd(SPI1, ENABLE); // enable SPI1
}


int main(void) {
  uint8_t received_data = 0;

  init_GPIO(); //Initialise GPIO pins
  init_SPI1(); //Initialise SPI peripheral

  GPIOD->BSRRL = 0xF000; //Set PD12 through PD15 (BSRRL = Bit Set/Reset Register Low)
  Delay(0xF42400); //Wait
  GPIOD->BSRRH = 0xF000; //Reset PD12 through PD15 (BSRRH = Bit Set/Reset Register High)

  while(1) {
    if (SPI_I2S_GetFlagStatus(SPI1,  SPI_FLAG_RXNE) == RESET) {
      uint8_t received_data = SPI_I2S_ReceiveData(SPI1);

      switch(received_data) {
        //0x1000 = 0001000000000000
        //0x2000 = 0010000000000000
        //0x4000 = 0100000000000000
        //0x8000 = 1000000000000000

        case 0:
        GPIOD->BSRRL = 0x1000; //Set LED1 (Green)
        GPIOD->BSRRH = 0x8000; //Reset LED4 (Blue)
        break;

        case 1:
        GPIOD->BSRRL = 0x2000; //Set LED2 (Orange)
        GPIOD->BSRRH = 0x1000; //Reset LED1 (Green)
        break;

        case 2:
        GPIOD->BSRRL = 0x4000; //Set LED3 (Red)
        GPIOD->BSRRH = 0x2000; //Reset LED2 (Orange)
        break;

        case 3:
        GPIOD->BSRRL = 0x8000; //Set LED4 (Blue)
        GPIOD->BSRRH = 0x4000; //Reset LED3 (Red)
        break;

      }
    }
  }
}
