#include "wifi_clock_ui.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * screen_main;
lv_obj_t * aisha;
lv_obj_t * time_lable;

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

///////////////////// SCREENS ////////////////////
void BuildPages(void)
{
    screen_main = lv_obj_create(NULL, NULL);

    aisha = lv_img_create(screen_main, NULL);
    lv_img_set_src(aisha, &img_aisha_png);
    lv_obj_set_click(aisha, false);
    lv_obj_set_hidden(aisha, false);
    lv_obj_set_size(aisha, 240, 240);
    lv_obj_align(aisha, screen_main, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_drag(aisha, false);
    lv_obj_set_style_local_image_opa(aisha, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 128);

    lv_obj_clear_state(aisha, LV_STATE_DISABLED);

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
                                      lv_color_hex(252 * 256 * 256 + 250 * 256 + 250));
    lv_obj_set_style_local_text_opa(time_lable, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(time_lable, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_28);

    lv_obj_align(time_lable, screen_main, LV_ALIGN_CENTER, 0, 0); // force: 132

}

