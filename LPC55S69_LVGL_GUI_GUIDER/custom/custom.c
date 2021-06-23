/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */
extern lv_ui_chart_series guider_ui_chart_series; //lv_ui_chart_series defined in custom.h

void custom_init(lv_ui *ui)
{
    /* Add your codes here */

	lv_slider_set_left_value(ui->screen_slider_1,4,false);
	lv_slider_set_type(ui->screen_slider_1, LV_SLIDER_TYPE_RANGE);

    guider_ui_chart_series.ser0 = lv_chart_add_series(ui->screen_chart_1, lv_color_make(0xff,  127, 0x00));
    guider_ui_chart_series.ser1 = lv_chart_add_series(ui->screen_chart_1, lv_color_make(0xff, 0xff, 0x00));
    guider_ui_chart_series.ser2 = lv_chart_add_series(ui->screen_chart_1, lv_color_make(0x00, 0xff, 0xff));
    //guider_ui_chart_series.ser3 = lv_chart_add_series(ui->screen_chart_1, lv_color_make(0xff, 0x00, 0xff));
    //guider_ui_chart_series.ser4 = lv_chart_add_series(ui->screen_chart_1, lv_color_make(0xff, 0x00, 0x00));
    //guider_ui_chart_series.ser5 = lv_chart_add_series(ui->screen_chart_1, lv_color_make(0xff,  191, 0x00));
    lv_chart_set_point_count(ui->screen_chart_1, 25);
}
