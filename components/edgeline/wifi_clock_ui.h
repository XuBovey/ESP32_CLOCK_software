#ifndef WIFI_CLOCK_UI_H
#define WIFI_CLOCK_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "src/lv_misc/lv_anim.h"

extern lv_obj_t * start;
extern lv_obj_t * aisha;
extern lv_obj_t * screen_main;
extern lv_obj_t * tme_panel;
extern lv_obj_t * time_lable;
extern lv_obj_t * weather;
extern lv_obj_t * sensor;


LV_IMG_DECLARE(img_aisha_png);   // assets\Aisha.png

void BuildPages(void);
void ChangeScreen(lv_obj_t * target, int fademode, int spd, int delay);
void SetLabelProperty(lv_obj_t * target, int id, char * val);

/***************************************

BuildPages();
ChangeScreen(start, LV_SCR_LOAD_ANIM_NONE, 0, 0);
ChangeScreen(screen_main, LV_SCR_LOAD_ANIM_FADE_ON, 500, 500);

 ***************************************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
