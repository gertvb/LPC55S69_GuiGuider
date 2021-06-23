/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: LPC55S69
package_id: LPC55S69JBD100
mcu_data: ksdk2_0
processor_version: 9.0.2
pin_labels:
- {pin_num: '68', pin_signal: PIO1_26/FC2_CTS_SDA_SSEL0/SCT0_OUT3/CT_INP3/UTICK_CAP1/HS_SPI_SSEL3/PLU_IN5, label: TFT_Reset, identifier: TFT_Reset}
- {pin_num: '85', pin_signal: PIO1_27/FC2_RTS_SCL_SSEL1/SD0_D4/CTIMER0_MAT3/CLKOUT/PLU_IN4, label: TFT_Data_or_Command, identifier: TFT_Data_or_Command}
- {pin_num: '71', pin_signal: PIO0_13/FC1_CTS_SDA_SSEL0/UTICK_CAP0/CT_INP0/SCT_GPI0/FC1_RXD_SDA_MOSI_DATA/PLU_IN0/SECURE_GPIO0_13, label: Rotary_SW, identifier: Rotary_SW;Rotary_SW_Falling;Rotary_SW_Rising}
- {pin_num: '3', pin_signal: PIO1_24/FC2_RXD_SDA_MOSI_DATA/SCT0_OUT1/SD1_D1/FC3_SSEL3/PLU_OUT6, label: Rotary_A, identifier: Rotary_A;Rotary_A_Level;Rotary_A_Rising;Rotary_A_Falling}
- {pin_num: '1', pin_signal: PIO1_4/FC0_SCK/SD0_D0/CTIMER2_MAT1/SCT0_OUT0/FREQME_GPIO_CLK_A, label: LED_Red, identifier: LED_Red}
- {pin_num: '5', pin_signal: PIO1_6/FC0_TXD_SCL_MISO_WS/SD0_D3/CTIMER2_MAT1/SCT_GPI3, label: LED_Blue, identifier: LED_Blue}
- {pin_num: '9', pin_signal: PIO1_7/FC0_RTS_SCL_SSEL1/SD0_D1/CTIMER2_MAT2/SCT_GPI4, label: LED_Green, identifier: LED_Green}
- {pin_num: '88', pin_signal: PIO0_5/FC4_RXD_SDA_MOSI_DATA/CTIMER3_MAT0/SCT_GPI5/FC3_RTS_SCL_SSEL1/MCLK/SECURE_GPIO0_5, label: SW_ISP, identifier: SW_ISP}
- {pin_num: '10', pin_signal: PIO1_9/FC1_SCK/CT_INP4/SCT0_OUT2/FC4_CTS_SDA_SSEL0/ADC0_12, label: SW_User, identifier: SW_User}
- {pin_num: '64', pin_signal: PIO1_18/SD1_POW_EN/SCT0_OUT5/PLU_OUT0, label: SW_Wake, identifier: SW_Wake}
- {pin_num: '27', pin_signal: PIO0_27/FC2_TXD_SCL_MISO_WS/CTIMER3_MAT2/SCT0_OUT6/FC7_RXD_SDA_MOSI_DATA/PLU_OUT0/SECURE_GPIO0_27, label: Rotary_B, identifier: Rotary_B_Level;Rotary_B_Rising;Rotary_B_Falling}
- {pin_num: '30', pin_signal: PIO1_21/FC7_CTS_SDA_SSEL0/CTIMER3_MAT2/FC4_RXD_SDA_MOSI_DATA/PLU_OUT3, label: TFT_Backlight, identifier: TFT_Backlight}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "fsl_inputmux.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm33_core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '92', peripheral: FLEXCOMM0, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO0_29/FC0_RXD_SDA_MOSI_DATA/SD1_D2/CTIMER2_MAT3/SCT0_OUT8/CMP0_OUT/PLU_OUT2/SECURE_GPIO0_29,
    mode: inactive, slew_rate: standard, invert: disabled, open_drain: disabled}
  - {pin_num: '94', peripheral: FLEXCOMM0, signal: TXD_SCL_MISO_WS, pin_signal: PIO0_30/FC0_TXD_SCL_MISO_WS/SD1_D3/CTIMER0_MAT0/SCT0_OUT9/SECURE_GPIO0_30, mode: inactive,
    slew_rate: standard, invert: disabled, open_drain: disabled}
  - {pin_num: '1', peripheral: GPIO, signal: 'PIO1, 4', pin_signal: PIO1_4/FC0_SCK/SD0_D0/CTIMER2_MAT1/SCT0_OUT0/FREQME_GPIO_CLK_A, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: '5', peripheral: GPIO, signal: 'PIO1, 6', pin_signal: PIO1_6/FC0_TXD_SCL_MISO_WS/SD0_D3/CTIMER2_MAT1/SCT_GPI3, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: '9', peripheral: GPIO, signal: 'PIO1, 7', pin_signal: PIO1_7/FC0_RTS_SCL_SSEL1/SD0_D1/CTIMER2_MAT2/SCT_GPI4, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: '68', peripheral: GPIO, signal: 'PIO1, 26', pin_signal: PIO1_26/FC2_CTS_SDA_SSEL0/SCT0_OUT3/CT_INP3/UTICK_CAP1/HS_SPI_SSEL3/PLU_IN5, direction: OUTPUT,
    gpio_init_state: 'true'}
  - {pin_num: '85', peripheral: GPIO, signal: 'PIO1, 27', pin_signal: PIO1_27/FC2_RTS_SCL_SSEL1/SD0_D4/CTIMER0_MAT3/CLKOUT/PLU_IN4, direction: OUTPUT}
  - {pin_num: '88', peripheral: GPIO, signal: 'PIO0, 5', pin_signal: PIO0_5/FC4_RXD_SDA_MOSI_DATA/CTIMER3_MAT0/SCT_GPI5/FC3_RTS_SCL_SSEL1/MCLK/SECURE_GPIO0_5, direction: INPUT}
  - {pin_num: '10', peripheral: GPIO, signal: 'PIO1, 9', pin_signal: PIO1_9/FC1_SCK/CT_INP4/SCT0_OUT2/FC4_CTS_SDA_SSEL0/ADC0_12, direction: INPUT, mode: pullUp}
  - {pin_num: '64', peripheral: GPIO, signal: 'PIO1, 18', pin_signal: PIO1_18/SD1_POW_EN/SCT0_OUT5/PLU_OUT0, direction: INPUT, mode: pullUp}
  - {pin_num: '61', peripheral: FLEXCOMM8, signal: HS_SPI_SCK, pin_signal: PIO1_2/CTIMER0_MAT3/SCT_GPI6/HS_SPI_SCK/USB1_PORTPWRN/PLU_OUT5}
  - {pin_num: '59', peripheral: FLEXCOMM8, signal: HS_SPI_SSEL1, pin_signal: PIO1_1/FC3_RXD_SDA_MOSI_DATA/CT_INP3/SCT_GPI5/HS_SPI_SSEL1/USB1_OVERCURRENTN/PLU_OUT4}
  - {pin_num: '60', peripheral: FLEXCOMM8, signal: HS_SPI_MOSI, pin_signal: PIO0_26/FC2_RXD_SDA_MOSI_DATA/CLKOUT/CT_INP14/SCT0_OUT5/USB0_IDVALUE/FC0_SCK/HS_SPI_MOSI/SECURE_GPIO0_26}
  - {pin_num: '71', peripheral: GPIO, signal: 'PIO0, 13', pin_signal: PIO0_13/FC1_CTS_SDA_SSEL0/UTICK_CAP0/CT_INP0/SCT_GPI0/FC1_RXD_SDA_MOSI_DATA/PLU_IN0/SECURE_GPIO0_13,
    identifier: Rotary_SW, direction: INPUT, mode: pullUp}
  - {pin_num: '3', peripheral: GPIO, signal: 'PIO1, 24', pin_signal: PIO1_24/FC2_RXD_SDA_MOSI_DATA/SCT0_OUT1/SD1_D1/FC3_SSEL3/PLU_OUT6, identifier: Rotary_A_Level,
    direction: INPUT, mode: pullUp}
  - {pin_num: '3', peripheral: PINT, signal: 'PINT, 0', pin_signal: PIO1_24/FC2_RXD_SDA_MOSI_DATA/SCT0_OUT1/SD1_D1/FC3_SSEL3/PLU_OUT6, identifier: Rotary_A_Rising}
  - {pin_num: '3', peripheral: PINT, signal: 'PINT, 1', pin_signal: PIO1_24/FC2_RXD_SDA_MOSI_DATA/SCT0_OUT1/SD1_D1/FC3_SSEL3/PLU_OUT6, identifier: Rotary_A_Falling}
  - {pin_num: '27', peripheral: GPIO, signal: 'PIO0, 27', pin_signal: PIO0_27/FC2_TXD_SCL_MISO_WS/CTIMER3_MAT2/SCT0_OUT6/FC7_RXD_SDA_MOSI_DATA/PLU_OUT0/SECURE_GPIO0_27,
    identifier: Rotary_B_Level, direction: INPUT, mode: pullUp}
  - {pin_num: '27', peripheral: PINT, signal: 'PINT, 2', pin_signal: PIO0_27/FC2_TXD_SCL_MISO_WS/CTIMER3_MAT2/SCT0_OUT6/FC7_RXD_SDA_MOSI_DATA/PLU_OUT0/SECURE_GPIO0_27,
    identifier: Rotary_B_Rising}
  - {pin_num: '27', peripheral: PINT, signal: 'PINT, 3', pin_signal: PIO0_27/FC2_TXD_SCL_MISO_WS/CTIMER3_MAT2/SCT0_OUT6/FC7_RXD_SDA_MOSI_DATA/PLU_OUT0/SECURE_GPIO0_27,
    identifier: Rotary_B_Falling}
  - {pin_num: '30', peripheral: CTIMER3, signal: 'MATCH, 2', pin_signal: PIO1_21/FC7_CTS_SDA_SSEL0/CTIMER3_MAT2/FC4_RXD_SDA_MOSI_DATA/PLU_OUT3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M33 (Core #0) */
void BOARD_InitPins(void)
{
    /* Enables the clock for the Input Mux.: Enable Clock. */
    CLOCK_EnableClock(kCLOCK_InputMux);
    /* Enables the clock for the I/O controller.: Enable Clock. */
    CLOCK_EnableClock(kCLOCK_Iocon);

    /* Enables the clock for the GPIO0 module */
    CLOCK_EnableClock(kCLOCK_Gpio0);

    /* Enables the clock for the GPIO1 module */
    CLOCK_EnableClock(kCLOCK_Gpio1);

    gpio_pin_config_t SW_ISP_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_5 (pin 88)  */
    GPIO_PinInit(BOARD_INITPINS_SW_ISP_GPIO, BOARD_INITPINS_SW_ISP_PORT, BOARD_INITPINS_SW_ISP_PIN, &SW_ISP_config);

    gpio_pin_config_t Rotary_SW_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_13 (pin 71)  */
    GPIO_PinInit(BOARD_INITPINS_Rotary_SW_GPIO, BOARD_INITPINS_Rotary_SW_PORT, BOARD_INITPINS_Rotary_SW_PIN, &Rotary_SW_config);

    gpio_pin_config_t Rotary_B_Level_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_27 (pin 27)  */
    GPIO_PinInit(BOARD_INITPINS_Rotary_B_Level_GPIO, BOARD_INITPINS_Rotary_B_Level_PORT, BOARD_INITPINS_Rotary_B_Level_PIN, &Rotary_B_Level_config);

    gpio_pin_config_t LED_Red_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PIO1_4 (pin 1)  */
    GPIO_PinInit(BOARD_INITPINS_LED_Red_GPIO, BOARD_INITPINS_LED_Red_PORT, BOARD_INITPINS_LED_Red_PIN, &LED_Red_config);

    gpio_pin_config_t LED_Blue_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PIO1_6 (pin 5)  */
    GPIO_PinInit(BOARD_INITPINS_LED_Blue_GPIO, BOARD_INITPINS_LED_Blue_PORT, BOARD_INITPINS_LED_Blue_PIN, &LED_Blue_config);

    gpio_pin_config_t LED_Green_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PIO1_7 (pin 9)  */
    GPIO_PinInit(BOARD_INITPINS_LED_Green_GPIO, BOARD_INITPINS_LED_Green_PORT, BOARD_INITPINS_LED_Green_PIN, &LED_Green_config);

    gpio_pin_config_t SW_User_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO1_9 (pin 10)  */
    GPIO_PinInit(BOARD_INITPINS_SW_User_GPIO, BOARD_INITPINS_SW_User_PORT, BOARD_INITPINS_SW_User_PIN, &SW_User_config);

    gpio_pin_config_t SW_Wake_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO1_18 (pin 64)  */
    GPIO_PinInit(BOARD_INITPINS_SW_Wake_GPIO, BOARD_INITPINS_SW_Wake_PORT, BOARD_INITPINS_SW_Wake_PIN, &SW_Wake_config);

    gpio_pin_config_t Rotary_A_Level_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO1_24 (pin 3)  */
    GPIO_PinInit(BOARD_INITPINS_Rotary_A_Level_GPIO, BOARD_INITPINS_Rotary_A_Level_PORT, BOARD_INITPINS_Rotary_A_Level_PIN, &Rotary_A_Level_config);

    gpio_pin_config_t TFT_Reset_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PIO1_26 (pin 68)  */
    GPIO_PinInit(BOARD_INITPINS_TFT_Reset_GPIO, BOARD_INITPINS_TFT_Reset_PORT, BOARD_INITPINS_TFT_Reset_PIN, &TFT_Reset_config);

    gpio_pin_config_t TFT_Data_or_Command_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO1_27 (pin 85)  */
    GPIO_PinInit(BOARD_INITPINS_TFT_Data_or_Command_GPIO, BOARD_INITPINS_TFT_Data_or_Command_PORT, BOARD_INITPINS_TFT_Data_or_Command_PIN, &TFT_Data_or_Command_config);
    /* PIO1_24 is selected for PINT input 0 */
    INPUTMUX_AttachSignal(INPUTMUX, 0U, kINPUTMUX_GpioPort1Pin24ToPintsel);
    /* PIO1_24 is selected for PINT input 1 */
    INPUTMUX_AttachSignal(INPUTMUX, 1U, kINPUTMUX_GpioPort1Pin24ToPintsel);
    /* PIO0_27 is selected for PINT input 2 */
    INPUTMUX_AttachSignal(INPUTMUX, 2U, kINPUTMUX_GpioPort0Pin27ToPintsel);
    /* PIO0_27 is selected for PINT input 3 */
    INPUTMUX_AttachSignal(INPUTMUX, 3U, kINPUTMUX_GpioPort0Pin27ToPintsel);

    IOCON->PIO[0][13] = ((IOCON->PIO[0][13] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT013 (pin 71) is configured as PIO0_13. */
                         | IOCON_PIO_FUNC(PIO0_13_FUNC_ALT0)

                         /* Selects function mode (on-chip pull-up/pull-down resistor control).
                          * : Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO0_13_MODE_PULL_UP)

                         /* Select Digital mode.
                          * : Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO0_13_DIGIMODE_DIGITAL));

    IOCON->PIO[0][26] = ((IOCON->PIO[0][26] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT026 (pin 60) is configured as HS_SPI_MOSI. */
                         | IOCON_PIO_FUNC(0x09u)

                         /* Select Digital mode.
                          * : Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO0_26_DIGIMODE_DIGITAL));

    IOCON->PIO[0][27] = ((IOCON->PIO[0][27] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT027 (pin 27) is configured as PIO0_27. */
                         | IOCON_PIO_FUNC(PIO0_27_FUNC_ALT0)

                         /* Selects function mode (on-chip pull-up/pull-down resistor control).
                          * : Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO0_27_MODE_PULL_UP)

                         /* Select Digital mode.
                          * : Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO0_27_DIGIMODE_DIGITAL));

    const uint32_t port0_pin29_config = (/* Pin is configured as FC0_RXD_SDA_MOSI_DATA */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN29 (coords: 92) is configured as FC0_RXD_SDA_MOSI_DATA */
    IOCON_PinMuxSet(IOCON, 0U, 29U, port0_pin29_config);

    const uint32_t port0_pin30_config = (/* Pin is configured as FC0_TXD_SCL_MISO_WS */
                                         IOCON_PIO_FUNC1 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN30 (coords: 94) is configured as FC0_TXD_SCL_MISO_WS */
    IOCON_PinMuxSet(IOCON, 0U, 30U, port0_pin30_config);

    IOCON->PIO[0][5] = ((IOCON->PIO[0][5] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT05 (pin 88) is configured as PIO0_5. */
                        | IOCON_PIO_FUNC(PIO0_5_FUNC_ALT0)

                        /* Select Digital mode.
                         * : Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO0_5_DIGIMODE_DIGITAL));

    IOCON->PIO[1][1] = ((IOCON->PIO[1][1] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT11 (pin 59) is configured as HS_SPI_SSEL1. */
                        | IOCON_PIO_FUNC(PIO1_1_FUNC_ALT5)

                        /* Select Digital mode.
                         * : Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO1_1_DIGIMODE_DIGITAL));

    IOCON->PIO[1][18] = ((IOCON->PIO[1][18] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT118 (pin 64) is configured as PIO1_18. */
                         | IOCON_PIO_FUNC(PIO1_18_FUNC_ALT0)

                         /* Selects function mode (on-chip pull-up/pull-down resistor control).
                          * : Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO1_18_MODE_PULL_UP)

                         /* Select Digital mode.
                          * : Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_18_DIGIMODE_DIGITAL));

    IOCON->PIO[1][2] = ((IOCON->PIO[1][2] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT12 (pin 61) is configured as HS_SPI_SCK. */
                        | IOCON_PIO_FUNC(PIO1_2_FUNC_ALT6)

                        /* Select Digital mode.
                         * : Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO1_2_DIGIMODE_DIGITAL));

    IOCON->PIO[1][21] = ((IOCON->PIO[1][21] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT121 (pin 30) is configured as CTIMER3_MAT2. */
                         | IOCON_PIO_FUNC(PIO1_21_FUNC_ALT3)

                         /* Select Digital mode.
                          * : Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_21_DIGIMODE_DIGITAL));

    IOCON->PIO[1][24] = ((IOCON->PIO[1][24] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT124 (pin 3) is configured as PIO1_24. */
                         | IOCON_PIO_FUNC(PIO1_24_FUNC_ALT0)

                         /* Selects function mode (on-chip pull-up/pull-down resistor control).
                          * : Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO1_24_MODE_PULL_UP)

                         /* Select Digital mode.
                          * : Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_24_DIGIMODE_DIGITAL));

    IOCON->PIO[1][26] = ((IOCON->PIO[1][26] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT126 (pin 68) is configured as PIO1_26. */
                         | IOCON_PIO_FUNC(PIO1_26_FUNC_ALT0)

                         /* Select Digital mode.
                          * : Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_26_DIGIMODE_DIGITAL));

    IOCON->PIO[1][27] = ((IOCON->PIO[1][27] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT127 (pin 85) is configured as PIO1_27. */
                         | IOCON_PIO_FUNC(PIO1_27_FUNC_ALT0)

                         /* Select Digital mode.
                          * : Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_27_DIGIMODE_DIGITAL));

    IOCON->PIO[1][4] = ((IOCON->PIO[1][4] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT14 (pin 1) is configured as PIO1_4. */
                        | IOCON_PIO_FUNC(PIO1_4_FUNC_ALT0)

                        /* Select Digital mode.
                         * : Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO1_4_DIGIMODE_DIGITAL));

    IOCON->PIO[1][6] = ((IOCON->PIO[1][6] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT16 (pin 5) is configured as PIO1_6. */
                        | IOCON_PIO_FUNC(PIO1_6_FUNC_ALT0)

                        /* Select Digital mode.
                         * : Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO1_6_DIGIMODE_DIGITAL));

    IOCON->PIO[1][7] = ((IOCON->PIO[1][7] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT17 (pin 9) is configured as PIO1_7. */
                        | IOCON_PIO_FUNC(PIO1_7_FUNC_ALT0)

                        /* Select Digital mode.
                         * : Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO1_7_DIGIMODE_DIGITAL));

    if (Chip_GetVersion()==1)
    {
        IOCON->PIO[1][9] = ((IOCON->PIO[1][9] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT19 (pin 10) is configured as PIO1_9. */
                        | IOCON_PIO_FUNC(PIO1_9_FUNC_ALT0)

                        /* Selects function mode (on-chip pull-up/pull-down resistor control).
                         * : Pull-up.
                         * Pull-up resistor enabled. */
                        | IOCON_PIO_MODE(PIO1_9_MODE_PULL_UP)

                        /* Select Digital mode.
                         * : Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO1_9_DIGIMODE_DIGITAL));
    }
    else
    {
        IOCON->PIO[1][9] = ((IOCON->PIO[1][9] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT19 (pin 10) is configured as PIO1_9. */
                        | IOCON_PIO_FUNC(PIO1_9_FUNC_ALT0)

                        /* Selects function mode (on-chip pull-up/pull-down resistor control).
                         * : Pull-up.
                         * Pull-up resistor enabled. */
                        | IOCON_PIO_MODE(PIO1_9_MODE_PULL_UP)

                        /* Select Digital mode.
                         * : Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO1_9_DIGIMODE_DIGITAL));
    }
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
