#ifndef LITTLEVGL_SUPPORT_H
#define LITTLEVGL_SUPPORT_H
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
 $Date:: 2021-06-14 11:26:57 +0200 (Mon, 14 Jun 2021)                                                                                                                       $
 $Id:: littlevgl_support.c 1493 2021-06-14 09:26:57Z Gert_v_B                                                                                                               $
 $Header:: https://techexplorer/svn/SVN_Repository/c/lpc55s69_lvgl/board/littlevgl_support.c 1493 2021-06-14 09:26:57Z Gert_v_B                                             $
 $Revision:: 1493                                                                                                                                                           $
 \**************************************************************************************************************************************************************************/

#include "fsl_common.h"

// Colour definitions
#define ILI9341_BLACK       0x0000  ///<   0,   0,   0
#define ILI9341_NAVY        0x000F  ///<   0,   0, 123
#define ILI9341_DARKGREEN   0x03E0  ///<   0, 125,   0
#define ILI9341_DARKCYAN    0x03EF  ///<   0, 125, 123
#define ILI9341_MAROON      0x7800  ///< 123,   0,   0
#define ILI9341_PURPLE      0x780F  ///< 123,   0, 123
#define ILI9341_OLIVE       0x7BE0  ///< 123, 125,   0
#define ILI9341_LIGHTGREY   0xC618  ///< 198, 195, 198
#define ILI9341_DARKGREY    0x7BEF  ///< 123, 125, 123
#define ILI9341_BLUE        0x001F  ///<   0,   0, 255
#define ILI9341_GREEN       0x07E0  ///<   0, 255,   0
#define ILI9341_CYAN        0x07FF  ///<   0, 255, 255
#define ILI9341_RED         0xF800  ///< 255,   0,   0
#define ILI9341_MAGENTA     0xF81F  ///< 255,   0, 255
#define ILI9341_YELLOW      0xFFE0  ///< 255, 255,   0
#define ILI9341_WHITE       0xFFFF  ///< 255, 255, 255
#define ILI9341_ORANGE      0xFD20  ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define ILI9341_PINK        0xFC18  ///< 255, 130, 198

//Changed to landscape mode, right after FT9341_Init is called in lv_port_disp_init
#define LCD_WIDTH             320
#define LCD_HEIGHT            240

#define LCD_FB_BYTE_PER_PIXEL 2
/* The virtual buffer for DBI panel, it should be ~1/10 screen size. */
#define LCD_VIRTUAL_BUF_SIZE (LCD_WIDTH * LCD_HEIGHT / 10)


#ifdef __cplusplus
extern "C" {
#endif

//lpcxpresso55s69_littlevgl_demo_widgets_bm project littlevgl_support.c & h
//See samples in /lvgl/examples/porting/lv_port_disp_template.c & lv_port_indev_template.c
void lv_port_disp_init(void);
void lv_port_indev_init(void);

#if defined(__cplusplus)
}
#endif

#endif //LITTLEVGL_SUPPORT_H
