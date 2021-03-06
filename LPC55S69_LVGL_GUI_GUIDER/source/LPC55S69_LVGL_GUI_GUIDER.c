/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

 /**********************************************************************************************************************************\
 *                                                                                                                                  *
 * Title : LPC55S69 with NXP GUI GUIDER generated UI for Little Versatile Graphics Library                                          *
 *                                                                                                                                  *
 * Author : Gert van Biljon                                                                                                         *
 *                                                                                                                                  *
 * EMail : gertvb@gmail.com                                                                                                         *
 *                                                                                                                                  *
 \**********************************************************************************************************************************/

 /**********************************************************************************************************************************\
 ************************************************************************************************************************************
 **                                                                                                                                **
 ** Todo : 1.   beep on encoder input : lv_indev_drv_t -> void (*feedback_cb)(struct _lv_indev_drv_t *, uint8_t);                  **
 **        2.   back port this lvgl & GuiGuider stuff to Electrical motor Management                                               **
 **                                                                                                                                **
 ************************************************************************************************************************************
 \**********************************************************************************************************************************/

 /**********************************************************************************************************************************\
 * LVGL : 1. DO NOT USE V8 of lvgl, rather use V7. There is a problem with task handler in V8 crashing, should not be a problem as  *
 *           GUI Guider uses V7 by default                                                                                          *
 *        2. Rather download lvgl 7.11.0 and don't use lvgl V7.4.0 that comes with GuiGuider, Slider that comes with 7.11 has the   *
 *           range functionality                                                                                                    *
 *        3. Have a look at the NXP SDK sample project lpcxpresso55s69_littlevgl_guider                                             *
 *                                                                                                                                  *
 * What am I : MCUXpresso Project where I integrate an LvGL UI generated by NXP's GUI Guider (LvGL EdgeLine?)                       *
 *                                                                                                                                  *
 * Background : Rather than to roll my own and develop my own graphics library (Been there, done that! with the MCGA in 1989), I    *
 *              decided to get an existing gui library to work on the LPC55s69 with the Wavechare 2.4inch TFT and ILI9341 driver    *
 *                                                                                                                                  *
 *              On MCUXpresso there are already a few LvGL samples, thus decided to follow the route of least resistance and use    *
 *              LvGL                                                                                                                *
 *                                                                                                                                  *
 *              The available MCUXpresso samples were however built without using the ConfigTools, which makes hardware             *
 *              configuration changes difficult, and I opted to rather start from scratch with ConfigTools in this project          *
 *                                                                                                                                  *
 *              Also integrating GUI Guider stuff into an MCUXpresso project is not well documented                                 *
 *                                                                                                                                  *
 * Drivers : littlevgl_support.c & .h in /board directory, to link the ILI9341 and EC11 to lvgl with the functions :                *
 *           lv_port_disp_init & lv_port_indev_init                                                                                 *
 *                                                                                                                                  *
 * Configtools: 0.  Connect LPC PINS to WaveShare TFT, refer to littlevgl_support.c                                                 *
 *              1.  Set up the SPI DMA to speak to the ILI9341                                                                      *
 *              2.  Set up the Pin interrupts and callbacks to process the EC11 rotary encoder                                      *
 *              3.  Set up the PWM to control the TFT backlight                                                                     *
 *              4.  Set the clock to work from the 12MHz FRO via a PLL, as the OKDO E1 that I use doesn't have a physical crystal   *
 *                                                                                                                                  *
 * Gui Guider : 1.  Download GuiGuider from the NXP website, install and run                                                        *
 *              2.  Select your MCUXpresso WORKSPACE directory as your GUI Guider Project directory. DO NOT use your MCUXpresso's   *
 *                  project directory as GUI GUIDER clashes with MCUXpresso                                                         *
 *              3.  Use LPC54628 as Board template                                                                                  *
 *              4.  Set the size to custom 320X240                                                                                  *
 *              5.  Select a GUI_Guider_Project name and Click create                                                               *
 *              6.  Build your GUI, also have a look at : https://www.nxp.com/design/training/getting-started-with-gui-guider:TIP-GETTING-STARTED-WITH-GUI-GUIDER
 *              7.  Click Generate Code, your GUI will be written to /MCUXpresso_Workspace/GUI_GUIDER_Project                       *
 *              8.  In MCUXpresso create your MCUXpresso project and configure your hardware, also select the ili9341               *
 *              9.  Copy the following directories from your GUI_Guider_Project into your MCUXpresso project                        *
 *                  i.   /custom to /custom                                                                                         *
 *                  ii.  /generated to /generated                                                                                   *
 *              10. Download lvgl V7.11 or higher (lvgl-release-v7.zip) from lvgl.io, extract it to lvgl-release-v7, and also copy  *
 *                  and rename it into your MCUXpresso project as /littlevgl/lvgl                                                   *
 *                  You can use the lvgl (V7.4) that comes with GUIGuider, but I prefer V7.11 as it has a better implementation of  *
 *                  the double knob range slider                                                                                    *
 *              11. In MCUXpresso, right click on each of these directories from step 9 & 10, and from the context menu select      *
 *                  Properties right at the bottom.  In the Dialog, under C/C++ Build / Settings uncheck:                           *
 *                  "Exclude resource from build"                                                                                   *
 *              12. From /littlevgl/lvgl copy lv_conf_template.h To /source lv_conf.h                                               *
 *              13. Modify lv_conf.h :                                                                                              *
 *                  i.    #if 0 change to #if 1                                                                                     *
 *                  ii.   #define LV_COLOR_DEPTH set to 16                                                                          *
 *                  iii.  #define LV_COLOR_16_SWAP  1                                                                               *
 *              14. Project (Menu item top) > Properties > C/C++ Build > Settings > MCU C Compiler > Includes :                     *
 *                  i.    /littlevgl                                                                                                *
 *                  ii.   /littlevgl/lvgl                                                                                           *
 *                  iii.  /littlevgl/lvgl/src                                                                                       *
 *                  iv.   /littlevgl/lvgl/src/lv_font                                                                               *
 *                  v.    /generated                                                                                                *
 *                  vi.   /generated/guider_fonts                                                                                   *
 *                  vii.  /generated/guider_customer_fonts                                                                          *
 *                  viii. /custom                                                                                                   *
 *              15. Project (Menu item top) > Properties > C/C++ General > Paths & Symbols > GNU C > Includes :                     *
 *                  i.    /littlevgl                                                                                                *
 *                  ii.   /littlevgl/lvgl                                                                                           *
 *                  iii.  /littlevgl/lvgl/src                                                                                       *
 *                  iv.   /littlevgl/lvgl/src/lv_font                                                                               *
 *                  v.    /generated                                                                                                *
 *                  vi.   /generated/guider_fonts                                                                                   *
 *                  vii.  /generated/guider_customer_fonts                                                                          *
 *                  viii. /custom                                                                                                   *
 *              16. Project (Menu item top) > Properties > C/C++ General > Paths & Symbols > GNU C > Source Location :              *
 *                  i.   /custom                                                                                                    *
 *                  ii.  /generated                                                                                                 *
 *                  ii.  /littlevgl                                                                                                 *
 *              17. Project (Menu item top) > Properties > C/C++ General > Paths & Symbols > GNU C > Symbols :                      *
 *                  i.   Add : LV_CONF_INCLUDE_SIMPLE and set to 1                                                                  *
 *              18. In /generated/events_init.c function void events_init(lv_ui *ui), add the following to link the encoder to      *
 *                  LvGL :                                                                                                          *
 *                  static lv_group_t*  g;                                                                                          *
 *                                                                                                                                  *
 *                  void events_init(lv_ui *ui)                                                                                     *
 *                  {                                                                                                               *
 *                      g = lv_group_create();                                                                                      *
 *                      lv_indev_t* cur_drv = NULL;                                                                                 *
 *                      for (;;)                                                                                                    *
 *                      {                                                                                                           *
 *                          cur_drv = lv_indev_get_next(cur_drv);                                                                   *
 *                          if (!cur_drv)                                                                                           *
 *                          {                                                                                                       *
 *                              break;                                                                                              *
 *                          }                                                                                                       *
 *                                                                                                                                  *
 *                          if (cur_drv->driver.type == LV_INDEV_TYPE_ENCODER)                                                      *
 *                          {                                                                                                       *
 *                              lv_indev_set_group(cur_drv, g);                                                                     *
 *                          }                                                                                                       *
 *                      }                                                                                                           *
 *                                                                                                                                  *
 *                      lv_group_add_obj(g, ui->screen_plus);                                                                       *
 *                      lv_group_add_obj(g, ui->screen_minus);                                                                      *
 *                  }                                                                                                               *
 *                                                                                                                                  *
 *              19. In main source file add the following includes :                                                                *
 *                  #include "lvgl.h"                                                                                               *
 *                  #include "littlevgl_support.h"                                                                                  *
 *                  #include "gui_guider.h"                                                                                         *
 *                  #include "events_init.h"                                                                                        *
 *                  #include "custom.h"                                                                                             *
 *              20. From main call:                                                                                                 *
 *                  lv_init();                                                                                                      *
 *                  lv_port_disp_init();                                                                                            *
 *                  lv_port_indev_init();                                                                                           *
 *                  setup_ui(&guider_ui);                                                                                           *
 *                  events_init(&guider_ui);                                                                                        *
 *                  custom_init(&guider_ui);                                                                                        *
 *                                                                                                                                  *
 *                  And periodically call:                                                                                          *
 *                  lv_task_handler();                                                                                              *
 *                  lv_tick_inc(LVGL_TICK_MS);                                                                                      *
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
 *                         12. MCUXpresso : lpcxpresso55s69_littlevgl_demo_widgets_bm project, DEMO_SPI_LCD_WriteData function      *
 *                         13. MCUXpresso : lpcxpresso55s69_spi_HS_LSPI_dma_b2b_transfer_master project,                            *
 *                                          EXAMPLE_MasterStartDMATransfer function                                                 *
 *                         14. MCUXpresso : lpcxpresso55s69_littlevgl_guider                                                        *
 *                         15. https://docs.lvgl.io/8.0/porting/project.html                                                        *
 *                         16. https://www.nxp.com/design/training/getting-started-with-gui-guider:TIP-GETTING-STARTED-WITH-GUI-GUIDER
 *                         17. Eli Hughes's : https://community.nxp.com/t5/MCUs-Community-Articles/LPC55S69-Embedded-Graphics-Using-LVGL-to-build-a-VU-Meter/ba-p/1179826
 *                                                                                                                                  *
 * Note : 1. The OKDO E1 board that I am working with doesn't have a 32MHz crystal, hence me running the clock from the 12MHz       *
 *           Free running Oscillator via the PLL                                                                                    *
 *        2. I am NOT yet an expert on the LPC55S69 - Thus my setup of is definitely NOT optimal, and there are lots of scope for   *
 *           improvement                                                                                                            *
 *                                                                                                                                  *
 * Subversion : Checking the whole project into SVN has an implication of size, thus I only check in the important files and let    *
 *              MCUXpresso generate the rest                                                                                        *
 *                                                                                                                                  *
 *              So to regenerate the project from the stuff stored in SVN:                                                          *
 *              1. Generate a new MCUXpresso project called LPC55S69_GUI_GUIDER, and add the following : CTimer, ADC, DMA, GPIO,    *
 *                 RTC, USB, DMA SPI, ILI9341 and Debug Console.                                                                    *
 *                 The generated stuff should now sit in S:\workspace\mcuxpresso\LPC55S69_GUI_GUIDER                                *
 *              2. In MCUXpresso open the ConfigTools' Pins, Clocks and Peripherals make minor changes, and update code so that the *
 *                 .mex file can be created and source files added to the project                                                   *
 *              3. Close MCUXpresso                                                                                                 *
 *              4. Copy from S:\local_checked_out_source\c\LPC55S69_GUI_GUIDER the following files :                                *
 *                 .cproject                                                                                                        *
 *                 LPC55S69_GUI_GUIDER.mex                                                                                          *
 *                 /source/LPC55S69_GUI_GUIDER.c                                                                                    *
 *              5. Open MCUXpresso again, and open this project again                                                               *
 *              6. Go into the configtools, Top Menu -> ConfigTools -> Peripherals/Pins/Clocks and change something insignificant   *
 *                 in each like changing the order of the pins at the bottom of the pins config, then:                              *
 *                 Top Menu -> Configtools -> Update Code!!!                                                                        *
 *              7. Back in the editor, do a clean, and then a build                                                                 *
 *              8. Go back to configtools and undo your simple changes and Update Code again, clean and build and the project       *
 *                 should run on your board                                                                                         *
 *                                                                                                                                  *
 * SVN Commit nr 1500! on 2021/06/17 08:38                                                                                          *
 \**********************************************************************************************************************************/

 /**************************************************************************************************************************************************************************\
 * My Subversion Info, automatically updated on commit, don't edit!                                                                                                         *
 *                                                                                                                                                                          *
 $Author:: Gert_v_B                                                                                                                                                         $
 $Date:: 2021-06-17 10:38:06 +0200 (Thu, 17 Jun 2021)                                                                                                                       $
 $Id:: LPC55S69_LVGL_GUI_GUIDER.c 1500 2021-06-17 08:38:06Z Gert_v_B                                                                                                        $
 $Header:: https://techexplorer/svn/SVN_Repository/c/lpc55s69_lvgl_GuiGuider/source/LPC55S69_LVGL_GUI_GUIDER.c 1500 2021-06-17 08:38:06Z Gert_v_B                           $
 $Revision:: 1500                                                                                                                                                           $
 \**************************************************************************************************************************************************************************/

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"

/* TODO: insert other include files here. */
#include "littlevgl_support.h" //Modified for EC11 and ILI9341 on the LPC55S69 by GvB, file sits in /board directory. Link lvgl with the functions : lv_port_disp_init & lv_port_indev_init
#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

/* TODO: insert other definitions and declarations here. */
lv_ui guider_ui; //gui_guider.h
lv_ui_chart_series guider_ui_chart_series; //custom.h

static volatile uint16_t Timer_1ms_ticks_counter = 0U;
static volatile bool b_Timer_5ms_Pending_Flag = false;
static volatile bool b_Timer_10ms_Pending_Flag = false;
static volatile bool b_Timer_50ms_Pending_Flag = false;
static volatile bool b_Timer_100ms_Pending_Flag = false;

void CTimer0_1ms_Callback(uint32_t flags)//Check these flags in while(happy) in main.....
{
	Timer_1ms_ticks_counter++;
	lv_tick_inc(1);//Indicate to lvgl that a 1ms tick ocurred, function is fast enough to leave here in the ISR

	if (!b_Timer_5ms_Pending_Flag)//try to speed up the isr a bit, compare is faster than %
	{
		if ((Timer_1ms_ticks_counter % 5) == 0U)
		{
			b_Timer_5ms_Pending_Flag = true;
		}
	}

	if (!b_Timer_10ms_Pending_Flag)
	{
		if ((Timer_1ms_ticks_counter % 10) == 0U)
		{
			b_Timer_10ms_Pending_Flag = true;
		}
	}

	if (!b_Timer_50ms_Pending_Flag)
	{
		if ((Timer_1ms_ticks_counter % 50) == 0U)
		{
			b_Timer_50ms_Pending_Flag = true;
		}
	}

	if (Timer_1ms_ticks_counter >= 100)
	{
		b_Timer_100ms_Pending_Flag = true;
		Timer_1ms_ticks_counter = 0;
	}
}

int main(void)
{
    //Init board hardware.
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    //Init FSL debug console.
    BOARD_InitDebugConsole();
#endif

    PRINTF("LPC55S69 with LvGL and GUI Guider\n");

    lv_init();

    //defined in : /board/littlevgl_support.c & h to link ILI9341 and EC11 to lvgl
    lv_port_disp_init();
    lv_port_indev_init();

    setup_ui(&guider_ui);
    events_init(&guider_ui);//Create a lvgl group and link the EC11 Rotary Encoder to it, encoder driver sits in /board/littlevgl_support.c functions : lv_port_disp_init & lv_port_indev_init
    custom_init(&guider_ui);//Go and populate with your own code

    while(1)
    {
    	if (b_Timer_5ms_Pending_Flag)
    	{
            b_Timer_5ms_Pending_Flag = false;
            lv_task_handler();
    	}
    }
    return 0 ;
}
