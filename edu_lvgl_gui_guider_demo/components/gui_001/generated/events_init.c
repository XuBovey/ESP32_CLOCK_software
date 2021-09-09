/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl/lvgl.h"
static unsigned int counter = 0;
static char buf[4];


void events_init(lv_ui *ui)
{
}

static void screen_plusevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_CLICKED:
	{
		counter++;
		sprintf(buf,  "%d" , counter);
		lv_obj_set_style_local_text_font(guider_ui.screen_counter, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_48);
		lv_label_set_text(guider_ui.screen_counter, buf);
		
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
	case LV_EVENT_CLICKED:
	{
		if(counter) counter--;
		sprintf(buf,  "%d" , counter);
		lv_obj_set_style_local_text_font(guider_ui.screen_counter, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_48);
		lv_label_set_text(guider_ui.screen_counter, buf);
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
}
