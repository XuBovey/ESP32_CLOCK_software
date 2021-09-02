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
//#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *main;
	lv_obj_t *main_bg_img;
	lv_obj_t *main_lmeter_temp;
	lv_obj_t *main_lmeter_humidity;
	lv_obj_t *main_label_temp;
	lv_obj_t *main_label_humidity;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_main(lv_ui *ui);
LV_IMG_DECLARE(_Aisha_alpha_240x240);

#ifdef __cplusplus
}
#endif
#endif
