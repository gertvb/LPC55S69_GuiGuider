/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL, NULL);

	//Write codes screen_counter
	ui->screen_counter = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_counter, "0");
	lv_label_set_long_mode(ui->screen_counter, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_counter, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_counter
	static lv_style_t style_screen_counter_main;
	lv_style_init(&style_screen_counter_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_counter_main
	lv_style_set_radius(&style_screen_counter_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_counter_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_counter_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_counter_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_counter_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_counter_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_counter_main, LV_STATE_DEFAULT, &lv_font_simsun_48);
	lv_style_set_text_letter_space(&style_screen_counter_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_counter_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_counter_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_counter_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_counter_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_counter, LV_LABEL_PART_MAIN, &style_screen_counter_main);
	lv_obj_set_pos(ui->screen_counter, 110, 187);
	lv_obj_set_size(ui->screen_counter, 100, 0);

	//Write codes screen_plus
	ui->screen_plus = lv_btn_create(ui->screen, NULL);

	//Write style LV_BTN_PART_MAIN for screen_plus
	static lv_style_t style_screen_plus_main;
	lv_style_init(&style_screen_plus_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_plus_main
	lv_style_set_radius(&style_screen_plus_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_plus_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xff));
	lv_style_set_bg_grad_color(&style_screen_plus_main, LV_STATE_DEFAULT, lv_color_make(0x02, 0xff, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_plus_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_plus_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_plus_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_plus_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_screen_plus_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_screen_plus_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_outline_opa(&style_screen_plus_main, LV_STATE_DEFAULT, 0);

	//Write style state: LV_STATE_FOCUSED for style_screen_plus_main
	lv_style_set_radius(&style_screen_plus_main, LV_STATE_FOCUSED, 50);
	lv_style_set_bg_color(&style_screen_plus_main, LV_STATE_FOCUSED, lv_color_make(0x00, 0x02, 0xff));
	lv_style_set_bg_grad_color(&style_screen_plus_main, LV_STATE_FOCUSED, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_plus_main, LV_STATE_FOCUSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_plus_main, LV_STATE_FOCUSED, 255);
	lv_style_set_border_color(&style_screen_plus_main, LV_STATE_FOCUSED, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_plus_main, LV_STATE_FOCUSED, 3);
	lv_style_set_border_opa(&style_screen_plus_main, LV_STATE_FOCUSED, 255);
	lv_style_set_outline_color(&style_screen_plus_main, LV_STATE_FOCUSED, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_outline_opa(&style_screen_plus_main, LV_STATE_FOCUSED, 0);

	//Write style state: LV_STATE_PRESSED for style_screen_plus_main
	lv_style_set_radius(&style_screen_plus_main, LV_STATE_PRESSED, 50);
	lv_style_set_bg_color(&style_screen_plus_main, LV_STATE_PRESSED, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_plus_main, LV_STATE_PRESSED, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_plus_main, LV_STATE_PRESSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_plus_main, LV_STATE_PRESSED, 255);
	lv_style_set_border_color(&style_screen_plus_main, LV_STATE_PRESSED, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_plus_main, LV_STATE_PRESSED, 0);
	lv_style_set_border_opa(&style_screen_plus_main, LV_STATE_PRESSED, 0);
	lv_style_set_outline_color(&style_screen_plus_main, LV_STATE_PRESSED, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_outline_opa(&style_screen_plus_main, LV_STATE_PRESSED, 0);
	lv_obj_add_style(ui->screen_plus, LV_BTN_PART_MAIN, &style_screen_plus_main);
	lv_obj_set_pos(ui->screen_plus, 5, 185);
	lv_obj_set_size(ui->screen_plus, 100, 50);
	ui->screen_plus_label = lv_label_create(ui->screen_plus, NULL);
	lv_label_set_text(ui->screen_plus_label, "Plus");
	lv_obj_set_style_local_text_color(ui->screen_plus_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0x00));
	lv_obj_set_style_local_text_font(ui->screen_plus_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_34);

	//Write codes screen_minus
	ui->screen_minus = lv_btn_create(ui->screen, NULL);

	//Write style LV_BTN_PART_MAIN for screen_minus
	static lv_style_t style_screen_minus_main;
	lv_style_init(&style_screen_minus_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_minus_main
	lv_style_set_radius(&style_screen_minus_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_minus_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xff));
	lv_style_set_bg_grad_color(&style_screen_minus_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_minus_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_minus_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_minus_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_minus_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_screen_minus_main, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_color(&style_screen_minus_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_outline_opa(&style_screen_minus_main, LV_STATE_DEFAULT, 0);

	//Write style state: LV_STATE_FOCUSED for style_screen_minus_main
	lv_style_set_radius(&style_screen_minus_main, LV_STATE_FOCUSED, 50);
	lv_style_set_bg_color(&style_screen_minus_main, LV_STATE_FOCUSED, lv_color_make(0x00, 0x00, 0xff));
	lv_style_set_bg_grad_color(&style_screen_minus_main, LV_STATE_FOCUSED, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_minus_main, LV_STATE_FOCUSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_minus_main, LV_STATE_FOCUSED, 255);
	lv_style_set_border_color(&style_screen_minus_main, LV_STATE_FOCUSED, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_minus_main, LV_STATE_FOCUSED, 3);
	lv_style_set_border_opa(&style_screen_minus_main, LV_STATE_FOCUSED, 255);
	lv_style_set_outline_color(&style_screen_minus_main, LV_STATE_FOCUSED, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_outline_opa(&style_screen_minus_main, LV_STATE_FOCUSED, 0);

	//Write style state: LV_STATE_PRESSED for style_screen_minus_main
	lv_style_set_radius(&style_screen_minus_main, LV_STATE_PRESSED, 50);
	lv_style_set_bg_color(&style_screen_minus_main, LV_STATE_PRESSED, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_minus_main, LV_STATE_PRESSED, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_minus_main, LV_STATE_PRESSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_minus_main, LV_STATE_PRESSED, 255);
	lv_style_set_border_color(&style_screen_minus_main, LV_STATE_PRESSED, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_minus_main, LV_STATE_PRESSED, 0);
	lv_style_set_border_opa(&style_screen_minus_main, LV_STATE_PRESSED, 0);
	lv_style_set_outline_color(&style_screen_minus_main, LV_STATE_PRESSED, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_outline_opa(&style_screen_minus_main, LV_STATE_PRESSED, 0);
	lv_obj_add_style(ui->screen_minus, LV_BTN_PART_MAIN, &style_screen_minus_main);
	lv_obj_set_pos(ui->screen_minus, 215, 185);
	lv_obj_set_size(ui->screen_minus, 100, 50);
	ui->screen_minus_label = lv_label_create(ui->screen_minus, NULL);
	lv_label_set_text(ui->screen_minus_label, "Minus");
	lv_obj_set_style_local_text_color(ui->screen_minus_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0x00));
	lv_obj_set_style_local_text_font(ui->screen_minus_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_34);

	//Write codes screen_chart_1
	ui->screen_chart_1 = lv_chart_create(ui->screen, NULL);

	//Write style LV_CHART_PART_BG for screen_chart_1
	static lv_style_t style_screen_chart_1_bg;
	lv_style_init(&style_screen_chart_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen_chart_1_bg
	lv_style_set_bg_color(&style_screen_chart_1_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xff));
	lv_style_set_bg_grad_color(&style_screen_chart_1_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_chart_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_chart_1_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_left(&style_screen_chart_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_screen_chart_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_screen_chart_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_screen_chart_1_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->screen_chart_1, LV_CHART_PART_BG, &style_screen_chart_1_bg);

	//Write style LV_CHART_PART_SERIES_BG for screen_chart_1
	static lv_style_t style_screen_chart_1_series_bg;
	lv_style_init(&style_screen_chart_1_series_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen_chart_1_series_bg
	lv_style_set_line_color(&style_screen_chart_1_series_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0x00));
	lv_style_set_line_width(&style_screen_chart_1_series_bg, LV_STATE_DEFAULT, 1);
	lv_style_set_line_opa(&style_screen_chart_1_series_bg, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_chart_1, LV_CHART_PART_SERIES_BG, &style_screen_chart_1_series_bg);
	lv_obj_set_pos(ui->screen_chart_1, 5, 5);
	lv_obj_set_size(ui->screen_chart_1, 310, 146);
	lv_chart_set_type(ui->screen_chart_1,LV_CHART_TYPE_LINE);
	lv_chart_set_range(ui->screen_chart_1,0,100);
	lv_chart_set_div_line_count(ui->screen_chart_1, 3, 5);

	//Write codes screen_slider_1
	ui->screen_slider_1 = lv_slider_create(ui->screen, NULL);

	//Write style LV_SLIDER_PART_INDIC for screen_slider_1
	static lv_style_t style_screen_slider_1_indic;
	lv_style_init(&style_screen_slider_1_indic);

	//Write style state: LV_STATE_DEFAULT for style_screen_slider_1_indic
	lv_style_set_radius(&style_screen_slider_1_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_slider_1_indic, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xff));
	lv_style_set_bg_grad_color(&style_screen_slider_1_indic, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_slider_1_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_slider_1_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_slider_1, LV_SLIDER_PART_INDIC, &style_screen_slider_1_indic);

	//Write style LV_SLIDER_PART_BG for screen_slider_1
	static lv_style_t style_screen_slider_1_bg;
	lv_style_init(&style_screen_slider_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_screen_slider_1_bg
	lv_style_set_radius(&style_screen_slider_1_bg, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_slider_1_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_screen_slider_1_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_slider_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_slider_1_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_screen_slider_1_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_screen_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_screen_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_slider_1_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_slider_1_bg, LV_STATE_DEFAULT, 0);

	//Write style state: LV_STATE_FOCUSED for style_screen_slider_1_bg
	lv_style_set_outline_color(&style_screen_slider_1_bg, LV_STATE_FOCUSED, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_outline_opa(&style_screen_slider_1_bg, LV_STATE_FOCUSED, 255);

	//Write style state: LV_STATE_DISABLED for style_screen_slider_1_bg
	lv_style_set_outline_color(&style_screen_slider_1_bg, LV_STATE_DISABLED, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_screen_slider_1_bg, LV_STATE_DISABLED, 0);
	lv_obj_add_style(ui->screen_slider_1, LV_SLIDER_PART_BG, &style_screen_slider_1_bg);

	//Write style LV_SLIDER_PART_KNOB for screen_slider_1
	static lv_style_t style_screen_slider_1_knob;
	lv_style_init(&style_screen_slider_1_knob);

	//Write style state: LV_STATE_DEFAULT for style_screen_slider_1_knob
	lv_style_set_radius(&style_screen_slider_1_knob, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_slider_1_knob, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_screen_slider_1_knob, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_slider_1_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_slider_1_knob, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_FOCUSED for style_screen_slider_1_knob
	lv_style_set_radius(&style_screen_slider_1_knob, LV_STATE_FOCUSED, 50);
	lv_style_set_bg_color(&style_screen_slider_1_knob, LV_STATE_FOCUSED, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_slider_1_knob, LV_STATE_FOCUSED, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_slider_1_knob, LV_STATE_FOCUSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_slider_1_knob, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->screen_slider_1, LV_SLIDER_PART_KNOB, &style_screen_slider_1_knob);
	lv_obj_set_pos(ui->screen_slider_1, 13, 164);
	lv_obj_set_size(ui->screen_slider_1, 295, 8);
	lv_slider_set_range(ui->screen_slider_1,0, 20);
	lv_slider_set_value(ui->screen_slider_1,10,false);

	//Init events for screen
	events_init_screen(ui);
}