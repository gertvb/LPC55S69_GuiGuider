/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*!
 * @brief Enables digital function */
#define IOCON_PIO_DIGITAL_EN 0x0100u
/*!
 * @brief Selects pin function 1 */
#define IOCON_PIO_FUNC1 0x01u
/*!
 * @brief Input function is not inverted */
#define IOCON_PIO_INV_DI 0x00u
/*!
 * @brief No addition pin function */
#define IOCON_PIO_MODE_INACT 0x00u
/*!
 * @brief Open drain is disabled */
#define IOCON_PIO_OPENDRAIN_DI 0x00u
/*!
 * @brief Standard mode, output slew rate control is enabled */
#define IOCON_PIO_SLEW_STANDARD 0x00u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO0_13_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO0_13_FUNC_ALT0 0x00u
/*!
 * @brief Selects function mode (on-chip pull-up/pull-down resistor control).: Pull-up. Pull-up resistor enabled. */
#define PIO0_13_MODE_PULL_UP 0x02u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO0_26_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO0_27_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO0_27_FUNC_ALT0 0x00u
/*!
 * @brief Selects function mode (on-chip pull-up/pull-down resistor control).: Pull-up. Pull-up resistor enabled. */
#define PIO0_27_MODE_PULL_UP 0x02u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO0_5_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO0_5_FUNC_ALT0 0x00u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_18_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO1_18_FUNC_ALT0 0x00u
/*!
 * @brief Selects function mode (on-chip pull-up/pull-down resistor control).: Pull-up. Pull-up resistor enabled. */
#define PIO1_18_MODE_PULL_UP 0x02u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_1_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 5. */
#define PIO1_1_FUNC_ALT5 0x05u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_21_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 3. */
#define PIO1_21_FUNC_ALT3 0x03u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_24_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO1_24_FUNC_ALT0 0x00u
/*!
 * @brief Selects function mode (on-chip pull-up/pull-down resistor control).: Pull-up. Pull-up resistor enabled. */
#define PIO1_24_MODE_PULL_UP 0x02u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_26_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO1_26_FUNC_ALT0 0x00u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_27_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO1_27_FUNC_ALT0 0x00u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_2_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 6. */
#define PIO1_2_FUNC_ALT6 0x06u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_4_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO1_4_FUNC_ALT0 0x00u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_6_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO1_6_FUNC_ALT0 0x00u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_7_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO1_7_FUNC_ALT0 0x00u
/*!
 * @brief Select Digital mode.: Enable Digital mode. Digital input is enabled. */
#define PIO1_9_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 0. */
#define PIO1_9_FUNC_ALT0 0x00u
/*!
 * @brief Selects function mode (on-chip pull-up/pull-down resistor control).: Pull-up. Pull-up resistor enabled. */
#define PIO1_9_MODE_PULL_UP 0x02u

/*! @name PIO1_4 (number 1), LED_Red
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_LED_Red_GPIO GPIO                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_LED_Red_GPIO_PIN_MASK (1U << 4U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_LED_Red_PORT 1U                  /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_LED_Red_PIN 4U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_LED_Red_PIN_MASK (1U << 4U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PIO1_6 (number 5), LED_Blue
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_LED_Blue_GPIO GPIO                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_LED_Blue_GPIO_PIN_MASK (1U << 6U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_LED_Blue_PORT 1U                  /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_LED_Blue_PIN 6U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_LED_Blue_PIN_MASK (1U << 6U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PIO1_7 (number 9), LED_Green
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_LED_Green_GPIO GPIO                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_LED_Green_GPIO_PIN_MASK (1U << 7U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_LED_Green_PORT 1U                  /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_LED_Green_PIN 7U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_LED_Green_PIN_MASK (1U << 7U)      /*!<@brief PORT pin mask */
                                                          /* @} */

/*! @name PIO1_26 (number 68), TFT_Reset
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_TFT_Reset_GPIO GPIO                 /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_TFT_Reset_GPIO_PIN_MASK (1U << 26U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_TFT_Reset_PORT 1U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_TFT_Reset_PIN 26U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_TFT_Reset_PIN_MASK (1U << 26U)      /*!<@brief PORT pin mask */
                                                           /* @} */

/*! @name PIO1_27 (number 85), TFT_Data_or_Command
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_TFT_Data_or_Command_GPIO GPIO                 /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_TFT_Data_or_Command_GPIO_PIN_MASK (1U << 27U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_TFT_Data_or_Command_PORT 1U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_TFT_Data_or_Command_PIN 27U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_TFT_Data_or_Command_PIN_MASK (1U << 27U)      /*!<@brief PORT pin mask */
                                                                     /* @} */

/*! @name PIO0_5 (number 88), SW_ISP
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SW_ISP_GPIO GPIO                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_SW_ISP_GPIO_PIN_MASK (1U << 5U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_SW_ISP_PORT 0U                  /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_SW_ISP_PIN 5U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_SW_ISP_PIN_MASK (1U << 5U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PIO1_9 (number 10), SW_User
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SW_User_GPIO GPIO                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_SW_User_GPIO_PIN_MASK (1U << 9U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_SW_User_PORT 1U                  /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_SW_User_PIN 9U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_SW_User_PIN_MASK (1U << 9U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PIO1_18 (number 64), SW_Wake
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SW_Wake_GPIO GPIO                 /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_SW_Wake_GPIO_PIN_MASK (1U << 18U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_SW_Wake_PORT 1U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_SW_Wake_PIN 18U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_SW_Wake_PIN_MASK (1U << 18U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PIO0_13 (number 71), Rotary_SW
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_Rotary_SW_GPIO GPIO                 /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_Rotary_SW_GPIO_PIN_MASK (1U << 13U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_Rotary_SW_PORT 0U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_Rotary_SW_PIN 13U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_Rotary_SW_PIN_MASK (1U << 13U)      /*!<@brief PORT pin mask */
                                                           /* @} */

/*! @name PIO1_24 (number 3), Rotary_A
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_Rotary_A_Level_GPIO GPIO                 /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_Rotary_A_Level_GPIO_PIN_MASK (1U << 24U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_Rotary_A_Level_PORT 1U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_Rotary_A_Level_PIN 24U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_Rotary_A_Level_PIN_MASK (1U << 24U)      /*!<@brief PORT pin mask */
                                                                /* @} */

/*! @name PIO1_24 (number 3), Rotary_A
  @{ */
#define BOARD_INITPINS_Rotary_A_Rising_PORT 1U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_Rotary_A_Rising_PIN 24U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_Rotary_A_Rising_PIN_MASK (1U << 24U)      /*!<@brief PORT pin mask */
                                                                 /* @} */

/*! @name PIO1_24 (number 3), Rotary_A
  @{ */
#define BOARD_INITPINS_Rotary_A_Falling_PORT 1U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_Rotary_A_Falling_PIN 24U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_Rotary_A_Falling_PIN_MASK (1U << 24U)      /*!<@brief PORT pin mask */
                                                                  /* @} */

/*! @name PIO0_27 (number 27), Rotary_B
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_Rotary_B_Level_GPIO GPIO                 /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_Rotary_B_Level_GPIO_PIN_MASK (1U << 27U) /*!<@brief GPIO pin mask */
#define BOARD_INITPINS_Rotary_B_Level_PORT 0U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_Rotary_B_Level_PIN 27U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_Rotary_B_Level_PIN_MASK (1U << 27U)      /*!<@brief PORT pin mask */
                                                                /* @} */

/*! @name PIO0_27 (number 27), Rotary_B
  @{ */
#define BOARD_INITPINS_Rotary_B_Rising_PORT 0U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_Rotary_B_Rising_PIN 27U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_Rotary_B_Rising_PIN_MASK (1U << 27U)      /*!<@brief PORT pin mask */
                                                                 /* @} */

/*! @name PIO0_27 (number 27), Rotary_B
  @{ */
#define BOARD_INITPINS_Rotary_B_Falling_PORT 0U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_Rotary_B_Falling_PIN 27U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_Rotary_B_Falling_PIN_MASK (1U << 27U)      /*!<@brief PORT pin mask */
                                                                  /* @} */

/*! @name PIO1_21 (number 30), TFT_Backlight
  @{ */
#define BOARD_INITPINS_TFT_Backlight_PORT 1U                   /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_TFT_Backlight_PIN 21U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_TFT_Backlight_PIN_MASK (1U << 21U)      /*!<@brief PORT pin mask */
                                                               /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void); /* Function assigned for the Cortex-M33 (Core #0) */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
