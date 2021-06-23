/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *screen;
	lv_obj_t *screen_counter;
	lv_obj_t *screen_plus;
	lv_obj_t *screen_plus_label;
	lv_obj_t *screen_minus;
	lv_obj_t *screen_minus_label;
	lv_obj_t *screen_chart_1;
	lv_obj_t *screen_slider_1;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif