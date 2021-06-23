 /**********************************************************************************************************************************\
 *                                                                                                                                  *
 * Title : Little Versatile Graphix Library, driver for the ILI9341 and EC11 rotary encoder                                         *
 *                                                                                                                                  *
 * Filename : littlevgl_support.c and littlevgl_support.h                                                                           *
 *                                                                                                                                  *
 * Author : Code from NXP/Waveshare/ILI all thrown together & panel beaten by Gert van Biljon                                       *
 *                                                                                                                                  *
 * EMail : gertvb@gmail.com                                                                                                         *
 *                                                                                                                                  *
 \**********************************************************************************************************************************/

 /**********************************************************************************************************************************\
 *                                                                                                                                  *
 * What am I : Driver to interface lvgl under MCUXpresso to the following hardware:                                                 *
 *             i.   ILI9341 Display driver                                                                                          *
 *             ii.  EC11 Rotary Encoder                                                                                             *
 *                                                                                                                                  *
 ************************************************************************************************************************************
 *                                                                                                                                  *
 * ILI9341 Display driver                                                                                                           *
 *                                                                                                                                  *
 * What I do : In essence I set up lv_port_disp_init by linking the following 2 functions to it :                                   *
 *             i.  ILI9341_Init                                                                                                     *
 *             ii. ILI9341_Flush_Buffer_to_Display                                                                                  *
 *                                                                                                                                  *
 *             In the background I provide supporting functions to the above 2 functions to speak to the hardware:                  *
 *             i.   ILI9341_SPI_DMA_Write_Command_Byte                                                                              *
 *             ii.  ILI9341_SPI_DMA_Write_Data_Byte                                                                                 *
 *             iii. ILI9341_SPI_DMA_Write_Data_N_Byte_Array                                                                         *
 *             iv.  ILI9341_Hardware_Reset                                                                                          *
 *             v.   ILI9341_SetBackLight_Percentage                                                                                 *
 *                                                                                                                                  *
 *             I also provide a test function, that enables me to see whether the HW setup and connections are OK by flooding the   *
 *             screen with one colour:                                                                                              *
 *             i.   ILI9341_Set_Memory_Write_Extents                                                                                *
 *             ii.  ILI9341_Colour_Flood_Screen                                                                                     *
 *                                                                                                                                  *
 * Origin : i.   fsl_ili9341.c & fsl_ili9341.c as generated during MCUXpresso new project creation, when selecting ILI9341 under    *
 *               Board components from the SDK                                                                                      *
 *          ii.  /lvgl/examples/porting/lv_port_disp_template.c                                                                     *
 *          iii. LCD_2inch4.c & LCD_2inch4.h from WaveShare                                                                         *
 *               https://www.waveshare.com/2.4inch-lcd-module.htm                                                                   *
 *               LCD_Module_code.7z, downloaded from : https://www.waveshare.com/wiki/2.4inch_LCD_Module                            *
 *               Started off with the ARDUINO 2.4inch sample code, and later discarded in favour of the ST 2.4 inch sample code     *                                                                                          *
 *          iv.  littlevgl_support.c & littlevgl_support.h from the MCUXpresso sample project : lpcxpresso55s69_littlevgl_demo_widgets_bm
 *               DEMO_SPI_LCD_WriteData function                                                                                    *
 *          v.   EXAMPLE_MasterStartDMATransfer function from the MCUXpresso sample project : lpcxpresso55s69_spi_HS_LSPI_dma_b2b_transfer_master
 *                                                                                                                                  *
 * MCUXpresso : i.   Set up the SPI DMA to speak to the ILI93421                                                                    *
 *              ii.  Set up the PWM to control the TFT backlight                                                                    *
 *              iii. Set up the Pin Connections as follows :                                                                        *
 *                                                                                                                                  *
 *              D13 | Oranje | CLK | SPI Clock                                | 01/02 | LSPI_HS_SCK                                 *
 *              D11 | Groen  | DIN | SPI Data In                              | 00/26 | LSPI_HS_MOSI                                *
 *              D10 | Geel   | CS  | Chip Select - Low Active                 | 01/01 | LSPI_HS_SSE1                                *
 *              D09 | Grys   | BL  | Backlight - CTIMER3_MAT2 / PWM Channel 2 | 01/21 | TFT_Backlight                               *
 *              D08 | Bruin  | RST | Reset - Low Active                       | 01/26 | TFT_Reset                                   *
 *              D07 | Blou   | DC  | Data - Low / Command - High              | 01/27 | TFT_Data_or_Command                         *
 *                                                                                                                                  *
 ************************************************************************************************************************************
 *                                                                                                                                  *
 * EC11 Rotary Encoder                                                                                                              *
 *                                                                                                                                  *
 * How it works : 1. Connect the common line of the rotary encoder to ground, and the 3 signal lines to gpio pins, pulled up        *
 *                   internally, without any capacitors to help with debounce                                                       *
 *                2. Set up 6 PINT interrupts on the Rotary encoder A, B and Switch signal lines on the rising and falling edges.   *
 *                   In each of the interrupt handlers check if the rotation was CW or CCW, and set the Green LED for CW and Red    *
 *                   for CW                                                                                                         *
 *                3. Set up a 100ms UTICK timer, start the timer in each of the pin edge interrupts, and prevent another pin        *
 *                   interrupt from firing before the utick timer has expired - thereby debouncing the signal                       *
 *                4. Populate 2 lvgl global variables in the interrupt handlers :                                                   *
 *                   i.  lvgl_RotaryEncoder_State, as LV_INDEV_STATE_REL or LV_INDEV_STATE_PR                                       *
 *                   ii. lvgl_RotaryEncoder_Diff, indicating the number of steps since the last xfer to lvgl                        *
 *                5. lvgl inputs are handled with a lv_indev_drv_t variable, this is created in lv_port_indev_init and linked to    *
 *                   the whole lvgl system with lv_indev_drv_register                                                               *
 *                6. encoder_read callback function is linked to the lv_indev_drv_t variable and called periodically from lvgl      *
 *                   This callback, basically transfers the 2 global variables from step 4 to the lvgl system                       *
 *                                                                                                                                  *
 * EC11 Rotary Encoder : 1. Pin D & C connected to ground                                                                           *
 *                       2. Pin A : Port 1 Pin 24 : Encoder_A_Level   - GPIO                     - Internal Pull Up                 *
 *                                                  Encoder_A_Rising  - PINT Rising Edge  - INT0                                    *
 *                                                  Encoder_A_Falling - PINT Falling Edge - INT1                                    *
 *                       3. Pin B : Port 0 Pin 27 : Encoder_B_Level   - GPIO                     - Internal Pull Up                 *
 *                                                  Encoder_B_Rising  - PINT Rising Edge  - INT2                                    *
 *                                                  Encoder_B_Falling - PINT Falling Edge - INT3                                    *
 *                       4. Pin E : Port 0 Pin 13 : Encoder_SW        - GPIO                     - Internal Pull Up                 *
 *                                                                                                                                  *
 *                                            |---------|         |---------|         |---------|         |----                     *
 *                                            |         |         |         |         |         |         |                         *
 *                       Signal A    ---------|         |---------|         |---------|         |---------|                         *
 *                                                                                                                                  *
 *                                   ----|         |---------|         |---------|         |---------|                              *
 *                                       |         |         |         |         |         |         |                              *
 *                       Signal B        |---------|         |---------|         |---------|         |---------                     *
 *                                                                                                                                  *
 *                       Interrupts      ^    ^    ^    ^    ^    ^    ^    ^    ^    ^    ^    ^    ^    ^                         *
 *                                                                                                                                  *
 *                       Clockwise       4    1    2    3    4    1    2    3    4    1    2    3    4    1                         *
 *                                                                                                                                  *
 *                       Counter CW      5    8    7    6    5    8    7    6    5    8    7    6    5    8                         *
 *                                                                                                                                  *
 *                       On the Rising/Falling edge interrupt of the first signal, I check the level of the second signal, and based*
 *                       on that I can figure if it is a Clockwise or an Anti-Clockwise step                                        *
 *                                                                                                                                  *
 *                       At the start of each Edge Interrupt handler I check the UTICK timer if enough time has elapsed since the   *
 *                       previous Interrupt as a way to debounce the signal in software, instead of having to do it in hardware     *
 *                                                                                                                                  *
 * ConfigTools : 1. Top Menu -> ConfigTools -> Peripherals                                                                          *
 *               2. Top Menu -> Configtools -> Pins                                                                                 *
 *               3. Top Menu -> Configtools -> Clocks                                                                               *
 *               4. Top Menu -> Configtools -> Update Code!!!                                                                       *
 *                                                                                                                                  *
 * Gotcha's : 1. pin_mux.c -> Configtools PIN tool renames the GPIO Identifier of the GPIO pin to the PINT Identifier!!!            *
 *                                                                                                                                  *
 *               For PIO1_24, I route the pin to: PINT0 for the rising edge  : Identifier Encoder_A_Rising                          *
 *                                                PINT1 for the falling edge : Identifier Encoder_A_Falling                         *
 *                                                GPIO for the pin level     : Identifier Encoder_A_Level                           *
 *                                                                                                                                  *
 *               The generated code HOWEVER tries to do the GPIO PinInit with the Identifiers defined for the PINT functionality :  *
 *                                                                                                                                  *
 *               GPIO_PinInit(BOARD_INITPINS_Encoder_A_Rising_GPIO, BOARD_INITPINS_Encoder_A_Rising_PORT, BOARD_INITPINS_Encoder_A_Rising_PIN, &Encoder_A_Rising_config);
 *                                                                                                                                  *
 *               Which obviously doesn't compile!!!!!!                                                                              *
 *                                                                                                                                  *
 *               The workaround is to change the order in the PINS config tool, so that the GPIO routing is listed first            *
 *                                                                                                                                  *
 *               Using the GPIO functionality in your code works with the correct identifiers                                       *
 *               GPIO_PinRead(GPIO, BOARD_INITPINS_Encoder_A_Level_PORT, BOARD_INITPINS_Encoder_A_Level_PIN)                        *
 *                                                                                                                                  *
 ************************************************************************************************************************************
 *                                                                                                                                  *
 * LVGL : 0.  DO NOT USE V8 of lvgl, rather use V7. There is a problem with task handler in V8 crashing                             *
 * 	      1.  Download lvgl-release-v7.zip from https://github.com/lvgl/lvgl/tree/release/v7                                        *
 *        2.  Extract lvgl-release-v7.zip to: lvgl-release-v7 directory                                                             *
 *        3.  Copy lvgl-release-v7 directory into LPC55S69_LvGL project directory and rename it to lvgl                             *
 *        4.  Copy lv_conf_template.h from /lvgl dir to /source directory in LPC55S69_LvGL project, and rename it to lv_conf.h      *                                                                                              *
 *        5.  Modify lv_conf.h :                                                                                                    *
 *            i.   #if 0 change to #if 1                                                                                            *
 *            ii.  #define LV_COLOR_DEPTH set to 16                                                                                 *
 *            iii. #define LV_COLOR_16_SWAP  1                                                                                      *
 *        6.  Download lv_demos-release-v7.zip from https://github.com/lvgl/lv_demos/tree/release/v7                                *
 *        7.  Extract lv_demos-release-v7.zip to lv_demos-release-v7 directory                                                      *
 *        8.  Copy lv_demos-release-v7 directory into LPC55S69_LvGL project directory and rename it to lv_demos                     *
 *        9.  Copy lv_ex_conf_template.h from /lv_demos dir to /source directory in LPC55S69_LvGL project, and rename it to         *
 *            lv_ex_conf.h                                                                                                          *
 *        10. Modify lv_ex_conf.h :                                                                                                 *
 *            i.   #if 0 change to #if 1                                                                                            *
 *            ii.  #define LV_EX_MOUSEWHEEL set to 1 to enable connecting the RotaryEncoder to the lvgl group                       *
 *            iii. #define LV_USE_DEMO_KEYPAD_AND_ENCODER set to 1 to build the Encoder demo                                        *
 *        11. In main source file add the following includes :                                                                      *
 *            #include "littlevgl_support.h"                                                                                        *
 *            #include "lvgl.h"                                                                                                     *
 *            #include "lv_demo_keypad_encoder/lv_demo_keypad_encoder.h"                                                            *
 *        12. From main call:                                                                                                       *
 *            lv_init();                                                                                                            *
 *            lv_port_disp_init();                                                                                                  *
 *            lv_port_indev_init();                                                                                                 *
 *            lv_demo_keypad_encoder();                                                                                             *
 *                                                                                                                                  *
 *            And periodically call:                                                                                                *
 *            lv_task_handler();                                                                                                    *
 *            lv_tick_inc(LVGL_TICK_MS);                                                                                            *
 *        13. Project (Menu item top) > Properties > C/C++ Build > Settings > MCU C Compiler > Includes :                           *
 *            i.   /lvgl                                                                                                            *
 *            ii.  /lvgl/src                                                                                                        *
 *            iii. /lv_demos                                                                                                        *
 *            iv.  /lv_demos/src                                                                                                    *
 *        14. Project (Menu item top) > Properties > C/C++ General > Paths & Symbols > GNU C > Includes :                           *
 *            i.   /lvgl                                                                                                            *
 *            ii.  /lvgl/src                                                                                                        *
 *            iii. /lv_demos                                                                                                        *
 *            iv.  /lv_demos/src                                                                                                    *
 *        15. Project (Menu item top) > Properties > C/C++ General > Paths & Symbols > GNU C > Source Location :                    *
 *            i.   /lvgl/src                                                                                                        *
 *            ii.  /lv_demos                                                                                                        *
 *                                                                                                                                  *
 * Additional references : 1.  Mark Dunnett from Embeddedpro has some nice videos on YouTube on the LPC55S69-evk and OKDO E1        *
 *                         2.  Mark Dunnets article on Powerquad FFT : https://mcuoneclipse.com/2019/12/03/investigating-arm-cortex-m33-core-dsp-acceleration-3-powerquad-fft-tutorial/
 *                         3.  Utick timer : https://mcuoneclipse.com/2020/06/16/microtick-utick-timer-tutorial-with-okdo-e1-board/ *
 *                         4.  https://nerdhut.de/2020/09/28/how-to-use-interrupts-on-the-lpc55s69-powered-okdo-e1/                 *
 *                         5.  El Hughes's stuff on the Mini-monkey, MonkeyJam and MonkeyListen                                     *
 *                         6.  Jennie Zhang's article on configuring the USB with NXP Config Tool                                   *
 *                             https://community.nxp.com/t5/LPC-Microcontrollers-Knowledge/Using-ConfigTool-to-create-USB-Project-From-Start/ta-p/1103294
 *                         7.  NXP AN12383                                                                                          *
 *                         8.  powerquad_matrix.c from lpcxpresso55s69_powerquad_matrix sample project                              *
 *                         9.  fsl_powerquad_cmsis.c in /drivers directory                                                          *
 *                         10. Waveshare : https://www.waveshare.com/2.4inch-lcd-module.htm                                         *
 *                             LCD_Module_code.7z, downloaded from : https://www.waveshare.com/wiki/2.4inch_LCD_Module              *
 *                             Started off with the ARDUINO 2.4inch sample code, and later discarded in favour of the ST 2.4 inch   *
 *                             sample code                                                                                          *
 *                         11. Sample code for the PIC18f46k22, looks like its originally Limor Fried's code from ADAFRUIT,         *
 *                             nice #defines in ILI9341.c, where I saw the 0x37 vertical scrolling functionality                    *
 *                             https://simple-circuit.com/pic18f46k22-ili9341-tft-ccs-c-proteus/                                    *
 *                             ADAFRUIT is an amazing company that ploughs a lot back into the embedded community!!                 *
 *                         12. MCUXpresso : lpcxpresso55s69_littlevgl_demo_widgets_bm project, DEMO_SPI_LCD_WriteData function as   *
 *                             used in littlevgl_support.c                                                                          *
 *                         13. MCUXpresso : lpcxpresso55s69_spi_HS_LSPI_dma_b2b_transfer_master project,                            *
 *                                          EXAMPLE_MasterStartDMATransfer function                                                 *
 *                         14. https://docs.lvgl.io/8.0/porting/project.html                                                        *
 *                         15. https://www.nxp.com/design/training/getting-started-with-gui-guider:TIP-GETTING-STARTED-WITH-GUI-GUIDER
 *                         16. Eli Hughes's : https://community.nxp.com/t5/MCUs-Community-Articles/LPC55S69-Embedded-Graphics-Using-LVGL-to-build-a-VU-Meter/ba-p/1179826
 \**********************************************************************************************************************************/

 /**************************************************************************************************************************************************************************\
 * My Subversion Info, automatically updated on commit, don't edit!                                                                                                         *
 *                                                                                                                                                                          *
 $Author:: Gert_v_B                                                                                                                                                         $
 $Date:: 2021-06-17 10:35:16 +0200 (Thu, 17 Jun 2021)                                                                                                                       $
 $Id:: littlevgl_support.c 1499 2021-06-17 08:35:16Z Gert_v_B                                                                                                               $
 $Header:: https://techexplorer/svn/SVN_Repository/c/lpc55s69_lvgl/board/littlevgl_support.c 1499 2021-06-17 08:35:16Z Gert_v_B                                             $
 $Revision:: 1499                                                                                                                                                           $
 \**************************************************************************************************************************************************************************/

#include "littlevgl_support.h"
#include "lvgl.h"
#include <string.h>
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_debug_console.h"
#include "fsl_spi_dma.h"
#include "peripherals.h"
#include "fsl_ili9341.h"

volatile bool UTick_fired = true;
//volatile bool Rotary_Direction_Clockwise = true;
//volatile bool Rotary_Direction_Changed = false;
//volatile bool Rotary_Turned = false;
//volatile bool Rotary_Switch_On = false;
//volatile bool Rotary_Switch_Changed = false;

//Following 2 values are updated in the rotary encoder pin interrupts
//and their values are read in encoder_read function lower down
//disabled when disabling the pushbutton interrupts volatile lv_indev_state_t lvgl_RotaryEncoder_State = LV_INDEV_STATE_REL; //LV_INDEV_STATE_REL or LV_INDEV_STATE_PR
volatile int16_t lvgl_RotaryEncoder_Diff = 0; //For LV_INDEV_TYPE_ENCODER number of steps since the previous read

SDK_ALIGN(static uint8_t s_frameBuffer[2][LCD_VIRTUAL_BUF_SIZE * LCD_FB_BYTE_PER_PIXEL], 4);

extern dma_handle_t FLEXCOMM8_RX_Handle; //defined in peripherals.c
extern dma_handle_t FLEXCOMM8_TX_Handle;
extern spi_dma_handle_t FLEXCOMM8_DMA_Handle;
extern const spi_master_config_t FLEXCOMM8_config;
volatile bool is_FLEXCOMM8_SPI_Transfer_Completed = false;

//Used by all 3 of the SPI_DMA_Write... functions, just made them global here
volatile uint8_t masterRxData[DMA_MAX_TRANSFER_COUNT]; //Todo GvB figure this, for 4 byte xfer I have to create a 1024byte array???
volatile spi_transfer_t masterXfer;

typedef void (*ili9341_send_byte_t)(uint8_t dataToSend);
void ILI9341_Init(ili9341_send_byte_t _writeData, ili9341_send_byte_t _writeCommand);

/**********************************************************************************************************************************\
* Function name : ILI9341_SPI_DMA_Write_Command_Byte/Data_Byte/n_Bytes                                                             *
*                                                                                                                                  *
* Author : NXP's DEMO_SPI_LCD_WriteCmd, heavily panelbeaten to conform to configtools SPI stuff by Gert van Biljon                 *
*                                                                                                                                  *
* What do I do : Use SPI DMA to write a uint8_t/uint16_t/uint32_t/uint8_t array to the ILI9341                                     *
*                                                                                                                                  *
* How I work : 1. Set the correct level on the DATA/COMMAND pin to select Data or Command mode on the ILI9341                      *
*              2. Populate the SPI data structures                                                                                 *
*              3. call SPI_MasterTransferDMA                                                                                       *
*                                                                                                                                  *
* Additional info : 1. lpcxpresso55s69_littlevgl_demo_widgets_bm MCUXpresso project, DEMO_SPI_LCD_WriteCmd and                     *
*                      DEMO_SPI_LCD_WriteMultiData functions, from littlevgl_support.c                                             *
*                   2. lpcxpresso55s69_spi_HS_LSPI_dma_b2b_transfer_master MCUXpresso project, EXAMPLE_MasterStartDMATransfer      *
*                      function                                                                                                    *
\**********************************************************************************************************************************/
void FLEXCOMM8_SPI_Transfer_Complete(SPI_Type *base, spi_dma_handle_t *handle, status_t status ,void *userData)
{
    if (status == kStatus_Success)
    {
        is_FLEXCOMM8_SPI_Transfer_Completed = true;
    }
}

void ILI9341_SPI_DMA_Write_Command_Byte(uint8_t data)
{
    //Indicate to the ILI9341 whether it is a command ot a data byte that is going to be sent
    GPIO_PinWrite(GPIO, BOARD_INITPINS_TFT_Data_or_Command_PORT, BOARD_INITPINS_TFT_Data_or_Command_PIN, 0);

    masterXfer.txData      = (uint8_t *)&data;
    masterXfer.rxData      = (uint8_t *)&masterRxData;
    masterXfer.dataSize    = 1;
    masterXfer.configFlags = kSPI_FrameAssert;

    is_FLEXCOMM8_SPI_Transfer_Completed = false;

    if (kStatus_Success != SPI_MasterTransferDMA(FLEXCOMM8_PERIPHERAL, &FLEXCOMM8_DMA_Handle, &masterXfer))
    {
        PRINTF("ILI9341_SPI_DMA_Write_Command_Byte error with : 0x%2x \r\n ", data);
    }

    while (is_FLEXCOMM8_SPI_Transfer_Completed == false)
    {
        __asm volatile ("nop");
    }
    //SDK_DelayAtLeastUs(ILI9341_RESET_CANCEL_MS * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

void ILI9341_SPI_DMA_Write_Data_Byte(uint8_t data)
{
    //Indicate to the ILI9341 whether it is a command ot a data byte that is going to be sent
    GPIO_PinWrite(GPIO, BOARD_INITPINS_TFT_Data_or_Command_PORT, BOARD_INITPINS_TFT_Data_or_Command_PIN, 1);

    masterXfer.txData      = (uint8_t *)&data;
    masterXfer.rxData      = (uint8_t *)&masterRxData;
    masterXfer.dataSize    = 1;
    masterXfer.configFlags = kSPI_FrameAssert;

    is_FLEXCOMM8_SPI_Transfer_Completed = false;

    if (kStatus_Success != SPI_MasterTransferDMA(FLEXCOMM8_PERIPHERAL, &FLEXCOMM8_DMA_Handle, &masterXfer))
    {
        PRINTF("ILI9341_SPI_DMA_Write_Data_Byte error with : 0x%02x \r\n ", data);
    }

    while (is_FLEXCOMM8_SPI_Transfer_Completed == false)
    {
        __asm volatile ("nop");
    }
}

void ILI9341_SPI_DMA_Write_Data_N_Byte_Array(const uint8_t *data_byte_array, uint16_t array_length)
{
    //Indicate to the ILI9341 whether it is a command ot a data byte that is going to be sent
    GPIO_PinWrite(GPIO, BOARD_INITPINS_TFT_Data_or_Command_PORT, BOARD_INITPINS_TFT_Data_or_Command_PIN, 1);

    //Break up the writes into 1024 byte chunks, which is the most that the DMA can handle in one shot
    while (array_length > DMA_MAX_TRANSFER_COUNT)
    {
        masterXfer.txData      = (uint8_t *)data_byte_array;//GvB I want it to be only data_byte_array without the (uint8_t *), but I like compiler warnings less
		masterXfer.rxData      = (uint8_t *)&masterRxData;
		masterXfer.dataSize    = DMA_MAX_TRANSFER_COUNT;
		masterXfer.configFlags = kSPI_FrameAssert;

        is_FLEXCOMM8_SPI_Transfer_Completed = false;

		if (kStatus_Success != SPI_MasterTransferDMA(FLEXCOMM8_PERIPHERAL, &FLEXCOMM8_DMA_Handle, &masterXfer))
		{
			PRINTF("ILI9341_SPI_DMA_Write_Data_N_Byte_Array write error in while\r\n");
		}

		while (is_FLEXCOMM8_SPI_Transfer_Completed == false)
		{
			__asm volatile ("nop");
		}

		array_length -= DMA_MAX_TRANSFER_COUNT;
		data_byte_array += DMA_MAX_TRANSFER_COUNT;
    }

    //Write what is left over
    if (array_length > 0)
    {
		masterXfer.txData      = (uint8_t *)data_byte_array;//GvB I want it to be only data_byte_array without the (uint8_t *)
		masterXfer.rxData      = (uint8_t *)&masterRxData;
		masterXfer.dataSize    = array_length; //refers to unsigned int on ARM, eg uint32_t
		masterXfer.configFlags = kSPI_FrameAssert;

		is_FLEXCOMM8_SPI_Transfer_Completed = false;

		if (kStatus_Success != SPI_MasterTransferDMA(FLEXCOMM8_PERIPHERAL, &FLEXCOMM8_DMA_Handle, &masterXfer))
		{
			PRINTF("ILI9341_SPI_DMA_Write_Data_N_Byte_Array write error at end\r\n");
		}

		while (is_FLEXCOMM8_SPI_Transfer_Completed == false)
		{
			__asm volatile ("nop");
		}
    }
}

/**********************************************************************************************************************************\
* Function name : ILI9341_Hardware_Reset                                                                                           *
*                                                                                                                                  *
* Author : Harvested from Waveshare ST Demo, LCD_2inch4.c                                                                          *
*                                                                                                                                  *
* What do I do : Pull the ILI9341 Reset pin low and release                                                                        *
\**********************************************************************************************************************************/
static void ILI9341_Hardware_Reset(void)
{
    SDK_DelayAtLeastUs(120000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    GPIO_PinWrite(GPIO, BOARD_INITPINS_TFT_Reset_PORT, BOARD_INITPINS_TFT_Reset_PIN, 0);
    SDK_DelayAtLeastUs(120000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    GPIO_PinWrite(GPIO, BOARD_INITPINS_TFT_Reset_PORT, BOARD_INITPINS_TFT_Reset_PIN, 1);
    SDK_DelayAtLeastUs(120000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

/**********************************************************************************************************************************\
* Function name : ILI9341_SetBackLight_Percentage                                                                                  *
*                                                                                                                                  *
* Author : Gert v Biljon                                                                                                           *
*                                                                                                                                  *
* Percentage : 0%   : Backlight off                                                                                                *
*              100% : Full brightness                                                                                              *
*                                                                                                                                  *
* Required : HW Connect Backlight control Transistor's base to Ctimer3 Match pin                                                   *
*                                                                                                                                  *
* What do I do : Update the PWM duty cycle with a percentage value                                                                 *
\**********************************************************************************************************************************/
void ILI9341_SetBackLight_Percentage(uint8_t Percentage)
{
    CTIMER_UpdatePwmDutycycle(CTIMER3_PERIPHERAL, CTIMER3_PWM_PERIOD_CH, CTIMER3_PWM_0_CHANNEL, Percentage);
}

/**********************************************************************************************************************************\
* Function name : ILI9341_Flush_Buffer_to_Display                                                                                  *
*                                                                                                                                  *
* Author : NXP? / ILI? / LvGL?   Harvested from DEMO_FlushDisplay in lpcxpresso55s69_littlevgl_demo_widgets_bm project             *
*                                                                                                                                  *
* What do I do : 1. Basically set the Column and Page address extents                                                              *
*                2. Dump the framebuffer to the ILI9341                                                                            *
*                3. After dumping the framebuffer to the screen, signal to LvGL that I am finished                                 *
*                                                                                                                                  *
* LvGL : This function is linked to the LvGL framework as the callback function to render a memory buffer to the screen            *
*        1.  The display buffer instance variable is instantiated in the lv_port_disp_init function :                              *
*            lv_disp_drv_t disp_drv;                                                                                               *
*        2.  This function is set as the callback function :                                                                       *
*            disp_drv.flush_cb = ILI9341_Flush_Buffer_to_Display;                                                                  *
\**********************************************************************************************************************************/
static void ILI9341_Flush_Buffer_to_Display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    lv_coord_t x1 = area->x1;
    lv_coord_t y1 = area->y1;
    lv_coord_t x2 = area->x2;
    lv_coord_t y2 = area->y2;

    uint8_t data[4];
    const uint8_t *pdata = (const uint8_t *)color_p;
    uint32_t send_size   = (x2 - x1 + 1) * (y2 - y1 + 1) * LCD_FB_BYTE_PER_PIXEL;

    /*Column addresses*/
    ILI9341_SPI_DMA_Write_Command_Byte(ILI9341_CMD_COLADDR);
    data[0] = (uint8_t)((x1 >> 8) & 0xFF);
    data[1] = (uint8_t)(x1 & 0xFF);
    data[2] = (uint8_t)((x2 >> 8) & 0xFF);
    data[3] = (uint8_t)(x2 & 0xFF);
    ILI9341_SPI_DMA_Write_Data_N_Byte_Array(data, 4);

    /*Page addresses*/
    ILI9341_SPI_DMA_Write_Command_Byte(ILI9341_CMD_PAGEADDR);
    data[0] = (uint8_t)((y1 >> 8) & 0xFF);
    data[1] = (uint8_t)(y1 & 0xFF);
    data[2] = (uint8_t)((y2 >> 8) & 0xFF);
    data[3] = (uint8_t)(y2 & 0xFF);
    ILI9341_SPI_DMA_Write_Data_N_Byte_Array(data, 4);

    /*Memory write*/
    ILI9341_SPI_DMA_Write_Command_Byte(ILI9341_CMD_GRAM);
    ILI9341_SPI_DMA_Write_Data_N_Byte_Array(pdata, send_size);

    lv_disp_flush_ready(disp_drv);
}

/**********************************************************************************************************************************\
* Function name : ILI9341_Set_Memory_Write_Extents                                                                                 *
*                                                                                                                                  *
* Author : Waveshare, originally called LCD_2IN4_SetWindow                                                                         *
*                                                                                                                                  *
* Modified : GertvB 20210524, modified to rather send a 4 byte array, than to use 4 X separate spi write commands                  *
*                                                                                                                                  *
* What do I do : Basically set the Column and Page address extents in memory where subsequent colour value writes should be        *
*                written to                                                                                                        *
*                                                                                                                                  *
* Note : This function is NOT required by LvGL, it is just for me to get some feedback as to whether all the connections and SPI   *
*        etc are all working and I can write to the screen                                                                         *                                                                                                                                 *
\**********************************************************************************************************************************/
void ILI9341_Set_Memory_Write_Extents(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
    uint8_t spi_write_array[4];

    ILI9341_SPI_DMA_Write_Command_Byte(ILI9341_CMD_COLADDR);
    if (Xstart <= Xend)
    {
    	spi_write_array[0] = (uint8_t)((Xstart >> 8) & 0xFF);
    	spi_write_array[1] = (uint8_t)((Xstart) & 0xFF);
    	spi_write_array[2] = (uint8_t)((Xend >> 8) & 0xFF);
    	spi_write_array[3] = (uint8_t)((Xend) & 0xFF);
    }
    else
    {
        spi_write_array[0] = (uint8_t)((Xend >> 8) & 0xFF);
        spi_write_array[1] = (uint8_t)((Xend) & 0xFF);
        spi_write_array[2] = (uint8_t)((Xstart >> 8) & 0xFF);
        spi_write_array[3] = (uint8_t)((Xstart) & 0xFF);
    }
    ILI9341_SPI_DMA_Write_Data_N_Byte_Array(spi_write_array, 4);

    ILI9341_SPI_DMA_Write_Command_Byte(ILI9341_CMD_PAGEADDR);
    if (Ystart <= Yend)
    {
        spi_write_array[0] = (uint8_t)((Ystart >> 8) & 0xFF);
        spi_write_array[1] = (uint8_t)((Ystart) & 0xFF);
        spi_write_array[2] = (uint8_t)((Yend >> 8) & 0xFF);
        spi_write_array[3] = (uint8_t)((Yend) & 0xFF);
    }
    else
    {
        spi_write_array[0] = (uint8_t)((Yend >> 8) & 0xFF);
        spi_write_array[1] = (uint8_t)((Yend) & 0xFF);
        spi_write_array[2] = (uint8_t)((Ystart >> 8) & 0xFF);
        spi_write_array[3] = (uint8_t)((Ystart) & 0xFF);
    }
    ILI9341_SPI_DMA_Write_Data_N_Byte_Array(spi_write_array, 4);

    ILI9341_SPI_DMA_Write_Command_Byte(ILI9341_CMD_GRAM);
}

/**********************************************************************************************************************************\
* Function name : ILI9341_Colour_Flood_Screen                                                                                      *
*                                                                                                                                  *
* Author : Waveshare, originally called LCD_2IN4_Clear                                                                             *
*                                                                                                                                  *
* Modified : GertvB 20210524, modified to rather send 320 times a (screen width x 2) byte array, than to send 320 times 240        *
*            separate spi write commands                                                                                           *
*                                                                                                                                  *
* Note : This function is NOT required by LvGL, it is just for me to get some feedback as to whether all the connections and SPI   *
*        etc are all working and I can write to the screen                                                                         *                                                                                                                                 *
\**********************************************************************************************************************************/
void ILI9341_Colour_Flood_Screen(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color)
{
    uint16_t i, j;
    uint8_t colour_high_byte;
    uint8_t colour_low_byte;
    uint32_t send_size   = (Xend - Xstart + 1) * LCD_FB_BYTE_PER_PIXEL;
    uint8_t spi_write_array[send_size];

    colour_high_byte = (uint8_t)((Color >> 8) & 0xFF);
    colour_low_byte  = (uint8_t)((Color) & 0xFF);

    //ILI9341_Set_Memory_Write_Extents(Xstart, Ystart, Xend, Yend);

    for(i = 0; i < (Xend - Xstart + 1); i++)//HeHeHe!! remember when you fill an array to start at position 0, and not at position Xstart.......
    {
        spi_write_array[ i * LCD_FB_BYTE_PER_PIXEL     ] = colour_high_byte;
        spi_write_array[(i * LCD_FB_BYTE_PER_PIXEL) + 1] = colour_low_byte;
        //PRINTF("i    %d    %d    %d    %d\n", i, i * LCD_FB_BYTE_PER_PIXEL, (i * LCD_FB_BYTE_PER_PIXEL) + 1, send_size);
     }
    for(j = Ystart; j < (Yend + 1); j++)
    {
        ILI9341_Set_Memory_Write_Extents(Xstart, j, Xend, j);//Slower to do it line by line, but less artifacts . . ..
    	ILI9341_SPI_DMA_Write_Data_N_Byte_Array(spi_write_array, send_size);
        //PRINTF("j    %d\n", j);
    }
}

//lpcxpresso55s69_littlevgl_demo_widgets_bm project littlevgl_support.c & h
//See samples in /lvgl/examples/porting/lv_port_disp_template.c & lv_port_indev_template.c
void lv_port_disp_init(void)
{
    //static lv_disp_draw_buf_t disp_buf; //lvgl V8
    static lv_disp_buf_t disp_buf;

    memset(s_frameBuffer, 0, sizeof(s_frameBuffer));
    //lv_disp_draw_buf_init(&disp_buf, s_frameBuffer[0], s_frameBuffer[1], LCD_VIRTUAL_BUF_SIZE); //LVGL V8
    lv_disp_buf_init(&disp_buf, s_frameBuffer[0], s_frameBuffer[1], LCD_VIRTUAL_BUF_SIZE);

    /*-------------------------
     * Initialize your display
     * -----------------------*/
	ILI9341_Hardware_Reset();

	ILI9341_SetBackLight_Percentage(50);

	//MCUXpresso : Board Components : Driver ILI9341 : in /lcd/fsl_ili9341.c & .h
	FT9341_Init(ILI9341_SPI_DMA_Write_Data_Byte, ILI9341_SPI_DMA_Write_Command_Byte);

    // Change to landscape view for lvgl.
    // Remember to update LCD_WIDTH and LCD_HEIGHT in lvgl_ILI9341_Driver.h if you change the following
	ILI9341_SPI_DMA_Write_Command_Byte(ILI9341_CMD_MAC);
	ILI9341_SPI_DMA_Write_Data_Byte(0x28);

    //GvB: This is just to test whether SPI writes to the screen are working . . . . .
    ILI9341_Colour_Flood_Screen( 0,  0, 319, 239, ILI9341_RED);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);//Delay, so I can see if the rotary encoder leds are working
    ILI9341_Colour_Flood_Screen(23, 23, 295, 215, ILI9341_ORANGE);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);//Delay, so I can see if the rotary encoder leds are working
    ILI9341_Colour_Flood_Screen(47, 47, 271, 191, ILI9341_YELLOW);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);//Delay, so I can see if the rotary encoder leds are working
    ILI9341_Colour_Flood_Screen(71, 71, 247, 167, ILI9341_GREEN);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);//Delay, so I can see if the rotary encoder leds are working
    ILI9341_Colour_Flood_Screen(95, 95, 223, 143, ILI9341_BLUE);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);//Delay, so I can see if the rotary encoder leds are working
    ILI9341_Colour_Flood_Screen( 0,  0, 319, 239, ILI9341_BLUE);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);//Delay, so I can see if the rotary encoder leds are working
    ILI9341_Colour_Flood_Screen(23, 23, 295, 215, ILI9341_GREEN);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);//Delay, so I can see if the rotary encoder leds are working
    ILI9341_Colour_Flood_Screen(47, 47, 271, 191, ILI9341_YELLOW);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);//Delay, so I can see if the rotary encoder leds are working
    ILI9341_Colour_Flood_Screen(71, 71, 247, 167, ILI9341_ORANGE);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);//Delay, so I can see if the rotary encoder leds are working
    ILI9341_Colour_Flood_Screen(95, 95, 223, 143, ILI9341_RED);
    SDK_DelayAtLeastUs(100, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);//Delay, so I can see if the rotary encoder leds are working

    /*-----------------------------------
     * Register the display in LittlevGL
     *----------------------------------*/

    lv_disp_drv_t disp_drv;      /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = ILI9341_Flush_Buffer_to_Display;

    /*Set a display buffer*/
    //disp_drv.draw_buf = &disp_buf; //LVGL V8
    disp_drv.buffer = &disp_buf;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

 /**********************************************************************************************************************************\
 * Function name : Rotary_Encoder_A/B_Rising/Falling                                                                                *
 *                                                                                                                                  *
 * Author : Gert van Biljon                                                                                                         *
 *                                                                                                                                  *
 * What do I do : I try to determine the rotation direction of the Rotary Encoder shaft, as well as trying to debounce the          *
 *                electrical signal in the same breath                                                                              *
 *                                                                                                                                  *
 * What I require : Rising and Falling edge interrupts for both Channel A and B from the rotary encoder : PINT0-3                   *
 *                  Signal levels for both Channel A and B from the rotary encoder : GPIO                                           *
 *                  UTick fired flag, indicating that sufficient time has elapsed since the previous edge interrupt                 *
 *                                                                                                                                  *
 * How I work : 1. Check for sufficient elapsed time since the previous Interrupt was processed                                     *
 *              2. Disable PINT Interrupts                                                                                          *
 *              3. Determine the level of the other encoder channel                                                                 *
 *              4. Based on the Square wave diagram in the top comments I can figure the direction, and switch the correct led      *
 *              5. Start the UTICK to wait before processing the next interrupt                                                     *
 *                                                                                                                                  *
 * EC11 Rotary Encoder : 1. Pin D & C connected to ground                                                                           *
 *                       2. Pin A : Port 1 Pin 24 : Encoder_A_Level   - GPIO                     - Internal Pull Up                 *
 *                                                  Encoder_A_Rising  - PINT Rising Edge  - INT0                                    *
 *                                                  Encoder_A_Falling - PINT Falling Edge - INT1                                    *
 *                       3. Pin B : Port 0 Pin 27 : Encoder_B_Level   - GPIO                     - Internal Pull Up                 *
 *                                                  Encoder_B_Rising  - PINT Rising Edge  - INT2                                    *
 *                                                  Encoder_B_Falling - PINT Falling Edge - INT3                                    *
 *                       4. Pin E : Port 0 Pin 13 : Encoder_SW        - GPIO                     - Internal Pull Up                 *
 *                                                                                                                                  *
 *                                            |---------|         |---------|         |---------|         |----                     *
 *                                            |         |         |         |         |         |         |                         *
 *                       Signal A    ---------|         |---------|         |---------|         |---------|                         *
 *                                                                                                                                  *
 *                                   ----|         |---------|         |---------|         |---------|                              *
 *                                       |         |         |         |         |         |         |                              *
 *                       Signal B        |---------|         |---------|         |---------|         |---------                     *
 *                                                                                                                                  *
 *                       Interrupts      ^    ^    ^    ^    ^    ^    ^    ^    ^    ^    ^    ^    ^    ^                         *
 *                                                                                                                                  *
 *                       Clockwise       4    1    2    3    4    1    2    3    4    1    2    3    4    1                         *
 *                                                                                                                                  *
 *                       Counter CW      5    8    7    6    5    8    7    6    5    8    7    6    5    8                         *
 *                                                                                                                                  *
 *                       On the Rising/Falling edge interrupt of the first signal, I check the level of the second signal, and based*
 *                       on that I can figure if it is a Clockwise or an Anti-Clockwise step                                        *
 *                                                                                                                                  *
 *                       At the start of each Edge Interrupt handler I check the UTICK timer if enough time has elapsed since the   *
 *                       previous Interrupt as a way to debounce the signal in software, instead of having to do it in hardware     *
 *                                                                                                                                  *
 \**********************************************************************************************************************************/
void Rotary_Encoder_A_Rising (pint_pin_int_t pintr, uint32_t pmatch_status_)
{
    if (UTick_fired)//Only process the interrupt after 20us expired to debounce the signal
    {
        //Rotary_Turned = true;
        PINT_DisableCallback(PINT);//Disable all edge interrupts till the timer has fired
        UTick_fired = false;
        if (GPIO_PinRead(GPIO, BOARD_INITPINS_Rotary_B_Level_PORT, BOARD_INITPINS_Rotary_B_Level_PIN) == 1)
        {
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Green_PORT, BOARD_INITPINS_LED_Green_PIN, 1);
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Red_PORT,   BOARD_INITPINS_LED_Red_PIN,   0);
            //if (Rotary_Direction_Clockwise == false)
            //    Rotary_Direction_Changed = true;
            //Rotary_Direction_Clockwise = true;
            lvgl_RotaryEncoder_Diff--;
        }
        else
        {
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Green_PORT, BOARD_INITPINS_LED_Green_PIN, 0);
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Red_PORT,   BOARD_INITPINS_LED_Red_PIN,   1);
            //if (Rotary_Direction_Clockwise == true)
            //    Rotary_Direction_Changed = true;
            //Rotary_Direction_Clockwise = false;
            lvgl_RotaryEncoder_Diff++;
        }
        UTICK_SetTick(UTICK0, kUTICK_Onetime, 250000U, UTICK0_Callback);//Jip 4Hz, were dealing with humans here
    }
}

void Rotary_Encoder_A_Falling (pint_pin_int_t pintr, uint32_t pmatch_status_)
{
    if (UTick_fired)
    {
        //Rotary_Turned = true;
        PINT_DisableCallback(PINT);
        UTick_fired = false;
        if (GPIO_PinRead(GPIO, BOARD_INITPINS_Rotary_B_Level_PORT, BOARD_INITPINS_Rotary_B_Level_PIN) == 1)
        {
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Green_PORT, BOARD_INITPINS_LED_Green_PIN, 0);
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Red_PORT,   BOARD_INITPINS_LED_Red_PIN,   1);
            //if (Rotary_Direction_Clockwise == true)
            //    Rotary_Direction_Changed = true;
            //Rotary_Direction_Clockwise = false;
            lvgl_RotaryEncoder_Diff++;
        }
        else
        {
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Green_PORT, BOARD_INITPINS_LED_Green_PIN, 1);
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Red_PORT,   BOARD_INITPINS_LED_Red_PIN,   0);
            //if (Rotary_Direction_Clockwise == false)
            //    Rotary_Direction_Changed = true;
            //Rotary_Direction_Clockwise = true;
            lvgl_RotaryEncoder_Diff--;
        }
        UTICK_SetTick(UTICK0, kUTICK_Onetime, 250000U, UTICK0_Callback);//Jip 4Hz, were dealing with humans here
    }
}

void Rotary_Encoder_B_Rising (pint_pin_int_t pintr, uint32_t pmatch_status_)
{
    if (UTick_fired)
    {
        //Rotary_Turned = true;
        PINT_DisableCallback(PINT);
        UTick_fired = false;
        if (GPIO_PinRead(GPIO, BOARD_INITPINS_Rotary_A_Level_PORT, BOARD_INITPINS_Rotary_A_Level_PIN) == 1)
        {
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Green_PORT, BOARD_INITPINS_LED_Green_PIN, 0);
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Red_PORT,   BOARD_INITPINS_LED_Red_PIN,   1);
            //if (Rotary_Direction_Clockwise == true)
            //    Rotary_Direction_Changed = true;
            //Rotary_Direction_Clockwise = false;
            lvgl_RotaryEncoder_Diff++;
        }
        else
        {
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Green_PORT, BOARD_INITPINS_LED_Green_PIN, 1);
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Red_PORT,   BOARD_INITPINS_LED_Red_PIN,   0);
            //if (Rotary_Direction_Clockwise == false)
            //    Rotary_Direction_Changed = true;
            //Rotary_Direction_Clockwise = true;
            lvgl_RotaryEncoder_Diff--;
        }
        UTICK_SetTick(UTICK0, kUTICK_Onetime, 250000U, UTICK0_Callback);//Jip 4Hz, were dealing with humans here
    }
}

void Rotary_Encoder_B_Falling (pint_pin_int_t pintr, uint32_t pmatch_status_)
{
    if (UTick_fired)
    {
        //Rotary_Turned = true;
        PINT_DisableCallback(PINT);
        UTick_fired = false;
        if (GPIO_PinRead(GPIO, BOARD_INITPINS_Rotary_A_Level_PORT, BOARD_INITPINS_Rotary_A_Level_PIN) == 1)
        {
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Green_PORT, BOARD_INITPINS_LED_Green_PIN, 1);
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Red_PORT,   BOARD_INITPINS_LED_Red_PIN,   0);
            //if (Rotary_Direction_Clockwise == false)
            //    Rotary_Direction_Changed = true;
            //Rotary_Direction_Clockwise = true;
            lvgl_RotaryEncoder_Diff--;
        }
        else
        {
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Green_PORT, BOARD_INITPINS_LED_Green_PIN, 0);
            GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Red_PORT,   BOARD_INITPINS_LED_Red_PIN,   1);
            //if (Rotary_Direction_Clockwise == true)
            //    Rotary_Direction_Changed = true;
            //Rotary_Direction_Clockwise = false;
            lvgl_RotaryEncoder_Diff++;
        }
        UTICK_SetTick(UTICK0, kUTICK_Onetime, 250000U, UTICK0_Callback);//Jip 4Hz, were dealing with humans here
    }
}

//GvB Using the EC11 with lvgl, for the pushbutton I've disabled the rising/falling pin interrupts in ConfigTools peripherals and pin configs
//encoder_read occurs often enough to rather just pass the pin level to lvgl directly
/*
void Rotary_Switch_Falling (pint_pin_int_t pintr, uint32_t pmatch_status_)
{
    if (UTick_fired)
    {
        PINT_DisableCallback(PINT);
        UTick_fired = false;
        //GPIO_PortToggle(GPIO, BOARD_INITPINS_LED_Blue_PORT,  BOARD_INITPINS_LED_Blue_PIN_MASK);
        GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Blue_PORT, BOARD_INITPINS_LED_Blue_PIN, 0);
        UTICK_SetTick(UTICK0, kUTICK_Onetime, 100000U, UTICK0_Callback);//Jip 4Hz, were dealing with humans here
        //Rotary_Switch_On = !Rotary_Switch_On;
        //Rotary_Switch_Changed = true;
        lvgl_RotaryEncoder_State = LV_INDEV_STATE_PR;
    }
}

void Rotary_Switch_Rising (pint_pin_int_t pintr, uint32_t pmatch_status_)
{
    if (UTick_fired)
    {
        PINT_DisableCallback(PINT);
        UTick_fired = false;
        GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Blue_PORT, BOARD_INITPINS_LED_Blue_PIN, 1);
        //GPIO_PortToggle(GPIO, BOARD_INITPINS_LED_Blue_PORT,  BOARD_INITPINS_LED_Blue_PIN_MASK);
        UTICK_SetTick(UTICK0, kUTICK_Onetime, 100000U, UTICK0_Callback);//Jip 4Hz, were dealing with humans here
        //Rotary_Switch_On = !Rotary_Switch_On;
        //Rotary_Switch_Changed = true;
        lvgl_RotaryEncoder_State = LV_INDEV_STATE_REL;
    }
}
*/

 /**********************************************************************************************************************************\
 * Function name : UTICK0_Callback                                                                                                  *
 *                                                                                                                                  *
 * Author : Gert van Biljon                                                                                                         *
 *                                                                                                                                  *
 * What do I do : 1. Set a global flag that the UTICK0 timer has timed out - means that PINT interrupts can be processed again      *
 *                2. Enable PINT interrupts again                                                                                   *
 *                3. Switch off direction LEDS                                                                                      *
 *                                                                                                                                  *
 * Note : I am started at the end of each PINT interrupt handler                                                                    *
 \**********************************************************************************************************************************/
void UTICK0_Callback(void)
{
    UTick_fired = true;
    PINT_EnableCallback(PINT);
    GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Green_PORT, BOARD_INITPINS_LED_Green_PIN, 1);
    GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Red_PORT,   BOARD_INITPINS_LED_Red_PIN,   1);
}

//Set values from pin interrupts into values palatable for LVGL drivers
//static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data) //LVGL V8
//lpcxpresso55s69_littlevgl_demo_widgets_bm project littlevgl_support.c & h
//See samples in /lvgl/examples/porting/lv_port_disp_template.c & lv_port_indev_template.c
static bool encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    data->enc_diff = lvgl_RotaryEncoder_Diff; //For LV_INDEV_TYPE_ENCODER number of steps since the previous read
    lvgl_RotaryEncoder_Diff = 0;

    //Initially set the pushbutton state in a rising/falling interrupt and populated
    //data->state = lvgl_RotaryEncoder_State; //LV_INDEV_STATE_REL or LV_INDEV_STATE_PR
    //in this function, but decided to disable the interrupts and just read the gpio switch level here
    if (GPIO_PinRead(GPIO, BOARD_INITPINS_Rotary_SW_PORT, BOARD_INITPINS_Rotary_SW_PIN) == 0)
    {
        GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Blue_PORT, BOARD_INITPINS_LED_Blue_PIN, 0);
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        GPIO_PinWrite(GPIO, BOARD_INITPINS_LED_Blue_PORT, BOARD_INITPINS_LED_Blue_PIN, 1);
        data->state = LV_INDEV_STATE_REL;
    }

    //following not used in lvgl V8
    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}

//lpcxpresso55s69_littlevgl_demo_widgets_bm project littlevgl_support.c & h
//See samples in /lvgl/examples/porting/lv_port_disp_template.c & lv_port_indev_template.c
void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    lv_indev_drv_register(&indev_drv);

    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_encoder, group);`*/

    /* Go and create the following in /generated/events_init.c as generated by GUI Guider :

    static lv_group_t*  g;

    void events_init(lv_ui *ui)
    {
        g = lv_group_create();

        lv_indev_t* cur_drv = NULL;
        for (;;) {
            cur_drv = lv_indev_get_next(cur_drv);
            if (!cur_drv) {
                break;
            }

            if (cur_drv->driver.type == LV_INDEV_TYPE_KEYPAD) {
                lv_indev_set_group(cur_drv, g);
            }

            if (cur_drv->driver.type == LV_INDEV_TYPE_ENCODER) {
                lv_indev_set_group(cur_drv, g);
            }

        }

        lv_group_add_obj(g, ui->screen_plus);
        lv_group_add_obj(g, ui->screen_minus);
    }*/
}
