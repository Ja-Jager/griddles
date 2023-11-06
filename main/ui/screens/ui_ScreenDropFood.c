// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.1
// LVGL version: 8.3.3
// Project name: 3d_printer

#include "../ui.h"

void ui_ScreenDropFood_screen_init(void)
{
    ui_ScreenDropFood = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenDropFood, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_PanelMenu1 = lv_obj_create(ui_ScreenDropFood);
    lv_obj_set_width(ui_PanelMenu1, lv_pct(100));
    lv_obj_set_height(ui_PanelMenu1, lv_pct(100));
    lv_obj_set_align(ui_PanelMenu1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelMenu1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PanelMenu1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelMenu1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelMenu1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelMenu1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelDropFood = lv_label_create(ui_PanelMenu1);
    lv_obj_set_width(ui_LabelDropFood, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDropFood, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelDropFood, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelDropFood, _("Drop Food"));
    lv_obj_set_style_text_font(ui_LabelDropFood, &ui_font_Chinese_70_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelDropFoodReminder = lv_label_create(ui_PanelMenu1);
    lv_obj_set_width(ui_LabelDropFoodReminder, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDropFoodReminder, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelDropFoodReminder, 0);
    lv_obj_set_y(ui_LabelDropFoodReminder, lv_pct(10));
    lv_obj_set_align(ui_LabelDropFoodReminder, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_LabelDropFoodReminder, _("Reminder"));
    lv_obj_set_style_text_font(ui_LabelDropFoodReminder, &ui_font_Chinese_48_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonDropFoodDone = lv_btn_create(ui_PanelMenu1);
    lv_obj_set_width(ui_ButtonDropFoodDone, lv_pct(30));
    lv_obj_set_height(ui_ButtonDropFoodDone, lv_pct(19));
    lv_obj_set_align(ui_ButtonDropFoodDone, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_ButtonDropFoodDone, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonDropFoodDone, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelDropFoodDone = lv_label_create(ui_ButtonDropFoodDone);
    lv_obj_set_width(ui_LabelDropFoodDone, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDropFoodDone, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelDropFoodDone, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_LabelDropFoodDone, _("Done"));
    lv_obj_set_style_text_font(ui_LabelDropFoodDone, &ui_font_Chinese_30_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelDropFoodDoneSeconds = lv_label_create(ui_ButtonDropFoodDone);
    lv_obj_set_width(ui_LabelDropFoodDoneSeconds, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDropFoodDoneSeconds, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelDropFoodDoneSeconds, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_LabelDropFoodDoneSeconds, "(sec)");
    lv_obj_set_style_text_font(ui_LabelDropFoodDoneSeconds, &ui_font_Chinese_30_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ButtonDropFoodDone, ui_event_ButtonDropFoodDone, LV_EVENT_ALL, NULL);

}