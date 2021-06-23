/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "fsl_debug_console.h"
#include "custom.h"


static unsigned int counter = 0;
static char buf[4];


extern lv_ui guider_ui; //lv_ui defined in guider.h
extern lv_ui_chart_series guider_ui_chart_series; //lv_ui_chart_series defined in custom.h

static lv_group_t* g;

void events_init(lv_ui *ui)
{
    g = lv_group_create();

    lv_indev_t* cur_drv = NULL;
    for (;;)
    {
        cur_drv = lv_indev_get_next(cur_drv);
        if (!cur_drv)
        {
            break;
        }

        if (cur_drv->driver.type == LV_INDEV_TYPE_KEYPAD)
        {
            lv_indev_set_group(cur_drv, g);
        }

        if (cur_drv->driver.type == LV_INDEV_TYPE_ENCODER)
        {
            lv_indev_set_group(cur_drv, g);
        }
    }

    lv_group_add_obj(g, ui->screen_plus);
    lv_group_add_obj(g, ui->screen_minus);
    lv_group_add_obj(g, ui->screen_slider_1);
}

static void screen_plusevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_LONG_PRESSED_REPEAT:
	{
				counter++;
				
				if (counter > 100)
					counter = 100;
		
				sprintf(buf,  "%d" , counter);
				lv_obj_set_style_local_text_font(guider_ui.screen_counter, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_48);
				lv_label_set_text(guider_ui.screen_counter, buf);
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser1, 5 * lv_slider_get_value(guider_ui.screen_slider_1));
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser2, 5 * lv_slider_get_left_value(guider_ui.screen_slider_1));
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser0, counter);
		
	}
		break;
	case LV_EVENT_CLICKED:
	{
				counter++;
				
				if (counter > 100)
					counter = 100;
		
				sprintf(buf,  "%d" , counter);
				lv_obj_set_style_local_text_font(guider_ui.screen_counter, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_48);
				lv_label_set_text(guider_ui.screen_counter, buf);
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser1, 5 * lv_slider_get_value(guider_ui.screen_slider_1));
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser2, 5 * lv_slider_get_left_value(guider_ui.screen_slider_1));
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser0, counter);
		
	}
		break;
	default:
		break;
	}
}

static void screen_minusevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_LONG_PRESSED_REPEAT:
	{
				if(counter) counter--;
				sprintf(buf,  "%d" , counter);
				lv_obj_set_style_local_text_font(guider_ui.screen_counter, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_48);
				lv_label_set_text(guider_ui.screen_counter, buf);
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser1, 5 * lv_slider_get_value(guider_ui.screen_slider_1));
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser2, 5 * lv_slider_get_left_value(guider_ui.screen_slider_1));
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser0, counter);
		
	}
		break;
	case LV_EVENT_CLICKED:
	{
				if(counter) counter--;
				sprintf(buf,  "%d" , counter);
				lv_obj_set_style_local_text_font(guider_ui.screen_counter, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_48);
				lv_label_set_text(guider_ui.screen_counter, buf);
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser1, 5 * lv_slider_get_value(guider_ui.screen_slider_1));
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser2, 5 * lv_slider_get_left_value(guider_ui.screen_slider_1));
				lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser0, counter);
		
	}
		break;
	default:
		break;
	}
}

static void screen_slider_1event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
			    //When the rotary knob is turned
			    //PRINTF("LV_EVENT_VALUE_CHANGED\n");
			    lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser1, 5 * lv_slider_get_value(guider_ui.screen_slider_1));
		        lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser2, 5 * lv_slider_get_left_value(guider_ui.screen_slider_1));
		    	lv_chart_set_next(guider_ui.screen_chart_1, guider_ui_chart_series.ser0, counter);
		
	}
		break;
	default:
		break;
	}
}

void events_init_screen(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_plus, screen_plusevent_handler);
	lv_obj_set_event_cb(ui->screen_minus, screen_minusevent_handler);
	lv_obj_set_event_cb(ui->screen_slider_1, screen_slider_1event_handler);
}

/*static void screen_sliderevent_handler(lv_obj_t * obj, lv_event_t event)
{
    //Just to see what are all the possible events that can be triggered for a widget
	switch (event)
	{
		case LV_EVENT_PRESSED:
		{
		    PRINTF("LV_EVENT_PRESSED\n");
		}
		break;
		case LV_EVENT_PRESSING:
		{
		    PRINTF("LV_EVENT_PRESSING\n");
		}
		break;
		case LV_EVENT_PRESS_LOST:
		{
		    PRINTF("LV_EVENT_PRESS_LOST\n");
		}
		break;
		case LV_EVENT_SHORT_CLICKED:
		{
		    PRINTF("LV_EVENT_SHORT_CLICKED\n");
		}
		break;
		case LV_EVENT_LONG_PRESSED:
		{
		    PRINTF("LV_EVENT_LONG_PRESSED\n");
		}
		break;
		case LV_EVENT_LONG_PRESSED_REPEAT:
		{
		    PRINTF("LV_EVENT_LONG_PRESSED_REPEAT\n");
		}
		break;
		case LV_EVENT_CLICKED:
		{
		    PRINTF("LV_EVENT_CLICKED\n");
		}
		break;
		case LV_EVENT_RELEASED:
		{
		    PRINTF("LV_EVENT_RELEASED\n");
		}
		break;
		case LV_EVENT_DRAG_BEGIN:
		{
		    PRINTF("LV_EVENT_DRAG_BEGIN\n");
		}
		break;
		case LV_EVENT_DRAG_END:
		{
		    PRINTF("LV_EVENT_DRAG_END\n");
		}
		break;
		case LV_EVENT_DRAG_THROW_BEGIN:
		{
		    PRINTF("LV_EVENT_DRAG_THROW_BEGIN\n");
		}
		break;
		case LV_EVENT_GESTURE:
		{
		    PRINTF("LV_EVENT_GESTURE\n");
		}
		break;
		case LV_EVENT_KEY:
		{
		    PRINTF("LV_EVENT_KEY\n");
		    uint32_t * key = lv_event_get_data();

		    switch (* key)
			{
				case LV_KEY_UP:
				{
				    PRINTF("LV_KEY_UP\n");
				}
				break;
				case LV_KEY_DOWN:
				{
				    PRINTF("LV_KEY_DOWN\n");
				}
				break;
				case LV_KEY_RIGHT:
				{
				    PRINTF("LV_KEY_RIGHT\n");//rotary turn
				}
				break;
				case LV_KEY_LEFT:
				{
				    PRINTF("LV_KEY_LEFT\n");//rotary turn
				}
				break;
				case LV_KEY_ESC:
				{
				    PRINTF("LV_KEY_ESC\n");
				}
				break;
				case LV_KEY_DEL:
				{
				    PRINTF("LV_KEY_DEL\n");
				}
				break;
				case LV_KEY_BACKSPACE:
				{
				    PRINTF("LV_KEY_BACKSPACE\n");
				}
				break;
				case LV_KEY_ENTER:
				{
				    PRINTF("LV_KEY_ENTER\n");
				}
				break;
				case LV_KEY_NEXT:
				{
				    PRINTF("LV_KEY_NEXT\n");
				}
				break;
				case LV_KEY_PREV:
				{
				    PRINTF("LV_KEY_PREV\n");
				}
				break;
				case LV_KEY_HOME:
				{
				    PRINTF("LV_KEY_HOME\n");
				}
				break;
				case LV_KEY_END:
				{
				    PRINTF("LV_KEY_END\n");
				}
				break;
				default:
				break;
				*key = 0;
			}
		}
		break;
		case LV_EVENT_FOCUSED:
		{
		    PRINTF("LV_EVENT_FOCUSED\n");
		}
		break;
		case LV_EVENT_DEFOCUSED:
		{
		    PRINTF("LV_EVENT_DEFOCUSED\n");
		}
		break;
		case LV_EVENT_LEAVE:
		{
		    PRINTF("LV_EVENT_LEAVE\n");
		}
		break;
		case LV_EVENT_VALUE_CHANGED:
		{
			//This one when the knob is dragged
		    PRINTF("LV_EVENT_VALUE_CHANGED\n");//also from rotary
		}
		break;
		case LV_EVENT_INSERT:
		{
		    PRINTF("LV_EVENT_INSERT\n");
		}
		break;
		case LV_EVENT_REFRESH:
		{
		    PRINTF("LV_EVENT_REFRESH\n");
		}
		break;
		case LV_EVENT_APPLY:
		{
		    PRINTF("LV_EVENT_APPLY\n");
		}
		break;
		case LV_EVENT_CANCEL:
		{
		    PRINTF("LV_EVENT_CANCEL\n");
		}
		break;
		case LV_EVENT_DELETE:
		{
		    PRINTF("LV_EVENT_DELETE\n");
		}
		break;
		case _LV_EVENT_LAST:
		{
		    PRINTF("_LV_EVENT_LAST\n");
		}
		break;
		default:
		break;
	}
} */
