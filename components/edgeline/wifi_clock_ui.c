#include "wifi_clock_ui.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * start;
lv_obj_t * aisha;
lv_obj_t * screen_main;
lv_obj_t * tme_panel;
lv_obj_t * time_lable;
lv_obj_t * weather;
lv_obj_t * sensor;

///////////////////// IMAGES ////////////////////
LV_IMG_DECLARE(img_aisha_png);   // assets\Aisha.png

///////////////////// FUNCTIONS ////////////////////
#define BAR_PROPERTY_VALUE 0
#define BAR_PROPERTY_VALUE_WITH_ANIM 1

void SetBarProperty(lv_obj_t * target, int id, int val)
{
    if(id == BAR_PROPERTY_VALUE_WITH_ANIM) lv_bar_set_value(target, val, LV_ANIM_ON);
    if(id == BAR_PROPERTY_VALUE) lv_bar_set_value(target, val, LV_ANIM_OFF);
}

#define BASIC_PROPERTY_POSITION_X 0
#define BASIC_PROPERTY_POSITION_Y 1
#define BASIC_PROPERTY_WIDTH 2
#define BASIC_PROPERTY_HEIGHT 3
#define BASIC_PROPERTY_CLICKABLE 4
#define BASIC_PROPERTY_HIDDEN 5
#define BASIC_PROPERTY_DRAGABLE 6
#define BASIC_PROPERTY_DISABLED 7

void SetBasicProperty(lv_obj_t * target, int id, int val)
{
    if(id == BASIC_PROPERTY_POSITION_X) lv_obj_set_x(target, val);
    if(id == BASIC_PROPERTY_POSITION_Y) lv_obj_set_y(target, val);
    if(id == BASIC_PROPERTY_WIDTH) lv_obj_set_width(target, val);
    if(id == BASIC_PROPERTY_HEIGHT) lv_obj_set_height(target, val);
}

void SetBasicPropertyB(lv_obj_t * target, int id, bool val)
{
    if(id == BASIC_PROPERTY_CLICKABLE) lv_obj_set_click(target, val);
    if(id == BASIC_PROPERTY_HIDDEN) lv_obj_set_hidden(target, val);
    if(id == BASIC_PROPERTY_DRAGABLE) lv_obj_set_drag(target, val);
    if(id == BASIC_PROPERTY_DISABLED) {
        if(val) lv_obj_add_state(target, LV_STATE_DISABLED);
        else lv_obj_clear_state(target, LV_STATE_DISABLED);
    }
}

#define BUTTON_PROPERTY_TOGGLE 0
#define BUTTON_PROPERTY_CHECKED 1

void SetButtonProperty(lv_obj_t * target, int id, bool val)
{
    if(id == BUTTON_PROPERTY_TOGGLE) lv_btn_toggle(target);
    if(id == BUTTON_PROPERTY_CHECKED) lv_btn_set_state(target, val ? LV_BTN_STATE_CHECKED_RELEASED : LV_BTN_STATE_RELEASED);
}

#define DROPDOWN_PROPERTY_SELECTED 0

void SetDropdownProperty(lv_obj_t * target, int id, int val)
{
    if(id == DROPDOWN_PROPERTY_SELECTED) lv_dropdown_set_selected(target, val);
}

#define IMAGE_PROPERTY_IMAGE 0

void SetImageProperty(lv_obj_t * target, int id, uint8_t * val)
{
    if(id == IMAGE_PROPERTY_IMAGE) lv_img_set_src(target, val);
}

#define LABEL_PROPERTY_TEXT 0

void SetLabelProperty(lv_obj_t * target, int id, char * val)
{
    if(id == LABEL_PROPERTY_TEXT) lv_label_set_text(target, val);
}

#define ROLLER_PROPERTY_SELECTED 0
#define ROLLER_PROPERTY_SELECTED_WITH_ANIM 1

void SetRollerProperty(lv_obj_t * target, int id, int val)
{
    if(id == ROLLER_PROPERTY_SELECTED_WITH_ANIM) lv_roller_set_selected(target, val, LV_ANIM_ON);
    if(id == ROLLER_PROPERTY_SELECTED) lv_roller_set_selected(target, val, LV_ANIM_OFF);
}

#define SLIDER_PROPERTY_VALUE 0
#define SLIDER_PROPERTY_VALUE_WITH_ANIM 1

void SetSliderProperty(lv_obj_t * target, int id, int val)
{
    if(id == SLIDER_PROPERTY_VALUE_WITH_ANIM) lv_slider_set_value(target, val, LV_ANIM_ON);
    if(id == SLIDER_PROPERTY_VALUE) lv_slider_set_value(target, val, LV_ANIM_OFF);
}

void ChangeScreen(lv_obj_t * target, int fademode, int spd, int delay)
{
    lv_scr_load_anim(target, fademode, spd, delay, false);
}

void SetOpacity(lv_obj_t * target, int val)
{
    lv_obj_set_style_local_opa_scale(target, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, val);
}

void anim_callback_set_x(lv_anim_t * a, lv_anim_value_t v)
{
    lv_obj_set_x(a->user_data, v);
}

void anim_callback_set_y(lv_anim_t * a, lv_anim_value_t v)
{
    lv_obj_set_y(a->user_data, v);
}

void anim_callback_set_width(lv_anim_t * a, lv_anim_value_t v)
{
    lv_obj_set_width(a->user_data, v);
}

void anim_callback_set_height(lv_anim_t * a, lv_anim_value_t v)
{
    lv_obj_set_height(a->user_data, v);
}

///////////////////// ANIMATIONS ////////////////////
void Animation1_Animation(lv_obj_t * TargetObject, int delay)
{

}

///////////////////// FUNCTIONS2 ////////////////////
static void tme_panel_eventhandler(lv_obj_t * obj, lv_event_t event)
{
}
static void weather_eventhandler(lv_obj_t * obj, lv_event_t event)
{
}
static void sensor_eventhandler(lv_obj_t * obj, lv_event_t event)
{
}

///////////////////// SCREENS ////////////////////
void BuildPages(void)
{
    start = lv_obj_create(NULL, NULL);

    aisha = lv_img_create(start, NULL);
    lv_img_set_src(aisha, &img_aisha_png);
    lv_obj_set_click(aisha, false);
    lv_obj_set_hidden(aisha, false);
    lv_obj_set_size(aisha, 240, 240);
    lv_obj_align(aisha, start, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_drag(aisha, false);

    lv_obj_clear_state(aisha, LV_STATE_DISABLED);

    screen_main = lv_obj_create(NULL, NULL);

    tme_panel = lv_obj_create(screen_main, NULL);
    lv_obj_set_click(tme_panel, true);
    lv_obj_set_hidden(tme_panel, false);
    lv_obj_clear_state(tme_panel, LV_STATE_DISABLED);
    lv_obj_set_size(tme_panel, 210, 120);  // force: 0
    lv_obj_align(tme_panel, screen_main, LV_ALIGN_CENTER, 0, -50); // force: 210
    lv_obj_set_drag(tme_panel, false);
    lv_obj_set_event_cb(tme_panel, tme_panel_eventhandler);
    lv_obj_set_style_local_bg_color(tme_panel, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(93 * 256 * 256 + 64 * 256 + 231));
    lv_obj_set_style_local_bg_opa(tme_panel, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);

    time_lable = lv_label_create(screen_main, NULL);
    lv_label_set_long_mode(time_lable, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(time_lable, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(time_lable, "2021-8-25\n14:45:10");
    lv_obj_set_size(time_lable, 132, 60);  // force: 0
    lv_obj_set_click(time_lable, false);
    lv_obj_set_hidden(time_lable, false);
    lv_obj_clear_state(time_lable, LV_STATE_DISABLED);
    lv_obj_set_drag(time_lable, false);
    lv_obj_set_style_local_text_color(time_lable, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(245 * 256 * 256 + 245 * 256 + 248));
    lv_obj_set_style_local_text_opa(time_lable, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(time_lable, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_28);

    lv_obj_align(time_lable, screen_main, LV_ALIGN_CENTER, 0, -50); // force: 132

    weather = lv_obj_create(screen_main, NULL);
    lv_obj_set_click(weather, true);
    lv_obj_set_hidden(weather, false);
    lv_obj_clear_state(weather, LV_STATE_DISABLED);
    lv_obj_set_size(weather, 100, 77);  // force: -55
    lv_obj_align(weather, screen_main, LV_ALIGN_CENTER, -55, 60); // force: 100
    lv_obj_set_drag(weather, false);
    lv_obj_set_event_cb(weather, weather_eventhandler);
    lv_obj_set_style_local_bg_color(weather, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(141 * 256 * 256 + 119 * 256 + 247));
    lv_obj_set_style_local_bg_opa(weather, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);

    sensor = lv_obj_create(screen_main, NULL);
    lv_obj_set_click(sensor, true);
    lv_obj_set_hidden(sensor, false);
    lv_obj_clear_state(sensor, LV_STATE_DISABLED);
    lv_obj_set_size(sensor, 100, 77);  // force: 55
    lv_obj_align(sensor, screen_main, LV_ALIGN_CENTER, 55, 60); // force: 100
    lv_obj_set_drag(sensor, false);
    lv_obj_set_event_cb(sensor, sensor_eventhandler);
    lv_obj_set_style_local_bg_color(sensor, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(141 * 256 * 256 + 119 * 256 + 247));
    lv_obj_set_style_local_bg_opa(sensor, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);

}

