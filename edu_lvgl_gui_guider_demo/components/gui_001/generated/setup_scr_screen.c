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
	lv_obj_set_pos(ui->screen_counter, 70, 52);
	lv_obj_set_size(ui->screen_counter, 100, 0);

	//Write codes screen_plus
	ui->screen_plus = lv_btn_create(ui->screen, NULL);

	//Write style LV_BTN_PART_MAIN for screen_plus
	static lv_style_t style_screen_plus_main;
	lv_style_init(&style_screen_plus_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_plus_main
	lv_style_set_radius(&style_screen_plus_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_plus_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_plus_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_plus_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_plus_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_plus_main, LV_STATE_DEFAULT, lv_color_make(0x1e, 0x01, 0xb2));
	lv_style_set_border_width(&style_screen_plus_main, LV_STATE_DEFAULT, 5);
	lv_style_set_border_opa(&style_screen_plus_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_screen_plus_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_outline_opa(&style_screen_plus_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_plus, LV_BTN_PART_MAIN, &style_screen_plus_main);
	lv_obj_set_pos(ui->screen_plus, 10, 150);
	lv_obj_set_size(ui->screen_plus, 100, 50);
	ui->screen_plus_label = lv_label_create(ui->screen_plus, NULL);
	lv_label_set_text(ui->screen_plus_label, "Plus");
	lv_obj_set_style_local_text_color(ui->screen_plus_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->screen_plus_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_16);

	//Write codes screen_minus
	ui->screen_minus = lv_btn_create(ui->screen, NULL);

	//Write style LV_BTN_PART_MAIN for screen_minus
	static lv_style_t style_screen_minus_main;
	lv_style_init(&style_screen_minus_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_minus_main
	lv_style_set_radius(&style_screen_minus_main, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_screen_minus_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_minus_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_minus_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_minus_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_screen_minus_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_minus_main, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_screen_minus_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_screen_minus_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_outline_opa(&style_screen_minus_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_minus, LV_BTN_PART_MAIN, &style_screen_minus_main);
	lv_obj_set_pos(ui->screen_minus, 130, 150);
	lv_obj_set_size(ui->screen_minus, 100, 50);
	ui->screen_minus_label = lv_label_create(ui->screen_minus, NULL);
	lv_label_set_text(ui->screen_minus_label, "Minus");
	lv_obj_set_style_local_text_color(ui->screen_minus_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_obj_set_style_local_text_font(ui->screen_minus_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_16);

	//Init events for screen
	events_init_screen(ui);
}