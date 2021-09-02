/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
//#include "custom.h"


void setup_scr_main(lv_ui *ui){

	//Write codes main
	ui->main = lv_obj_create(NULL, NULL);

	//Write codes main_bg_img
	ui->main_bg_img = lv_img_create(ui->main, NULL);

	//Write style LV_IMG_PART_MAIN for main_bg_img
	static lv_style_t style_main_bg_img_main;
	lv_style_init(&style_main_bg_img_main);

	//Write style state: LV_STATE_DEFAULT for style_main_bg_img_main
	lv_style_set_image_recolor(&style_main_bg_img_main, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf5, 0xf5));
	lv_style_set_image_recolor_opa(&style_main_bg_img_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_main_bg_img_main, LV_STATE_DEFAULT, 200);
	lv_obj_add_style(ui->main_bg_img, LV_IMG_PART_MAIN, &style_main_bg_img_main);
	lv_obj_set_pos(ui->main_bg_img, 0, 0);
	lv_obj_set_size(ui->main_bg_img, 240, 240);
	lv_obj_set_click(ui->main_bg_img, true);
	lv_img_set_src(ui->main_bg_img,&_Aisha_alpha_240x240);
	lv_img_set_pivot(ui->main_bg_img, 0,0);
	lv_img_set_angle(ui->main_bg_img, 0);

	//Write codes main_lmeter_temp
	ui->main_lmeter_temp = lv_linemeter_create(ui->main, NULL);

	//Write style LV_LINEMETER_PART_MAIN for main_lmeter_temp
	static lv_style_t style_main_lmeter_temp_main;
	lv_style_init(&style_main_lmeter_temp_main);

	//Write style state: LV_STATE_DEFAULT for style_main_lmeter_temp_main
	lv_style_set_radius(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0xff));
	lv_style_set_line_width(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, 2);
	lv_style_set_line_opa(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, 255);
	lv_style_set_scale_grad_color(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0xff));
	lv_style_set_scale_end_color(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, lv_color_make(0xfc, 0xf7, 0xfc));
	lv_style_set_scale_width(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, 10);
	lv_style_set_scale_end_line_width(&style_main_lmeter_temp_main, LV_STATE_DEFAULT, 2);
	lv_obj_add_style(ui->main_lmeter_temp, LV_LINEMETER_PART_MAIN, &style_main_lmeter_temp_main);
	lv_obj_set_pos(ui->main_lmeter_temp, 10, 60);
	lv_obj_set_size(ui->main_lmeter_temp, 100, 100);
	lv_linemeter_set_scale(ui->main_lmeter_temp, 300, 20);
	lv_linemeter_set_range(ui->main_lmeter_temp, 0, 100);
	lv_linemeter_set_value(ui->main_lmeter_temp, 37);
	lv_linemeter_set_angle_offset(ui->main_lmeter_temp, 0);

	//Write codes main_lmeter_humidity
	ui->main_lmeter_humidity = lv_linemeter_create(ui->main, NULL);

	//Write style LV_LINEMETER_PART_MAIN for main_lmeter_humidity
	static lv_style_t style_main_lmeter_humidity_main;
	lv_style_init(&style_main_lmeter_humidity_main);

	//Write style state: LV_STATE_DEFAULT for style_main_lmeter_humidity_main
	lv_style_set_radius(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, 30);
	lv_style_set_bg_color(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, 0);
	lv_style_set_line_color(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0xff));
	lv_style_set_line_width(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, 2);
	lv_style_set_line_opa(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, 255);
	lv_style_set_scale_grad_color(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0xff));
	lv_style_set_scale_end_color(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_scale_width(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, 10);
	lv_style_set_scale_end_line_width(&style_main_lmeter_humidity_main, LV_STATE_DEFAULT, 4);
	lv_obj_add_style(ui->main_lmeter_humidity, LV_LINEMETER_PART_MAIN, &style_main_lmeter_humidity_main);
	lv_obj_set_pos(ui->main_lmeter_humidity, 130, 60);
	lv_obj_set_size(ui->main_lmeter_humidity, 100, 100);
	lv_linemeter_set_scale(ui->main_lmeter_humidity, 300, 20);
	lv_linemeter_set_range(ui->main_lmeter_humidity, 0, 100);
	lv_linemeter_set_value(ui->main_lmeter_humidity, 90);
	lv_linemeter_set_angle_offset(ui->main_lmeter_humidity, 0);

	//Write codes main_label_temp
	ui->main_label_temp = lv_label_create(ui->main, NULL);
	lv_label_set_text(ui->main_label_temp, "37");
	lv_label_set_long_mode(ui->main_label_temp, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_label_temp, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_label_temp
	static lv_style_t style_main_label_temp_main;
	lv_style_init(&style_main_label_temp_main);

	//Write style state: LV_STATE_DEFAULT for style_main_label_temp_main
	lv_style_set_radius(&style_main_label_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_label_temp_main, LV_STATE_DEFAULT, lv_color_make(0x30, 0x71, 0xe8));
	lv_style_set_bg_grad_color(&style_main_label_temp_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_label_temp_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_label_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_main_label_temp_main, LV_STATE_DEFAULT, lv_color_make(0x0e, 0xf1, 0xe2));
	lv_style_set_text_font(&style_main_label_temp_main, LV_STATE_DEFAULT, &lv_font_montserrat_28);
	lv_style_set_text_letter_space(&style_main_label_temp_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_main_label_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_label_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_label_temp_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_label_temp_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_label_temp, LV_LABEL_PART_MAIN, &style_main_label_temp_main);
	lv_obj_set_pos(ui->main_label_temp, 30, 110);
	lv_obj_set_size(ui->main_label_temp, 60, 0);

	//Write codes main_label_humidity
	ui->main_label_humidity = lv_label_create(ui->main, NULL);
	lv_label_set_text(ui->main_label_humidity, "60");
	lv_label_set_long_mode(ui->main_label_humidity, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->main_label_humidity, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for main_label_humidity
	static lv_style_t style_main_label_humidity_main;
	lv_style_init(&style_main_label_humidity_main);

	//Write style state: LV_STATE_DEFAULT for style_main_label_humidity_main
	lv_style_set_radius(&style_main_label_humidity_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_main_label_humidity_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_label_humidity_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_label_humidity_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_label_humidity_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_main_label_humidity_main, LV_STATE_DEFAULT, lv_color_make(0x02, 0xf3, 0xf7));
	lv_style_set_text_font(&style_main_label_humidity_main, LV_STATE_DEFAULT, &lv_font_montserrat_28);
	lv_style_set_text_letter_space(&style_main_label_humidity_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_main_label_humidity_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_main_label_humidity_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_main_label_humidity_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_main_label_humidity_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->main_label_humidity, LV_LABEL_PART_MAIN, &style_main_label_humidity_main);
	lv_obj_set_pos(ui->main_label_humidity, 150, 110);
	lv_obj_set_size(ui->main_label_humidity, 60, 0);
}
