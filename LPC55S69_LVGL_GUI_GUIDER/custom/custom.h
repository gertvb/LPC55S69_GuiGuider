/*
 * custom.h
 *
 *  Created on: July 29, 2020
 *      Author: nxf53801
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_

#include "gui_guider.h"

typedef struct
{
	lv_chart_series_t *ser0;
	lv_chart_series_t *ser1;
	lv_chart_series_t *ser2;
	lv_chart_series_t *ser3;
	lv_chart_series_t *ser4;
	lv_chart_series_t *ser5;
}lv_ui_chart_series;

extern lv_ui_chart_series guider_ui_chart_series;

void custom_init(lv_ui *ui);

#endif /* __CUSTOM_H_ */
