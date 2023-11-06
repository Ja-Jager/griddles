// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.3
// Project name: 3d_printer

#include "../ui.h"

void ui_ScreenMenuConfigEditMenu_screen_init(void)
{
    ui_ScreenMenuConfigEditMenu = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ui_ScreenMenuConfigEditMenu, lv_color_hex(0x191D26), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenMenuConfigEditMenu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Background5 = lv_img_create(ui_ScreenMenuConfigEditMenu);
    lv_img_set_src(ui_Background5, &ui_img_photoshoped_assets_chinese_backgorund_chinese_png);
    lv_obj_set_width(ui_Background5, 800);
    lv_obj_set_height(ui_Background5, 480);
    lv_obj_set_align(ui_Background5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Background5, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags

    ui_BTNAutoMenuPrint6 = lv_img_create(ui_ScreenMenuConfigEditMenu);
    lv_img_set_src(ui_BTNAutoMenuPrint6, &ui_img_photoshoped_assets_manual_glow_png);
    lv_obj_set_width(ui_BTNAutoMenuPrint6, 79);
    lv_obj_set_height(ui_BTNAutoMenuPrint6, 160);
    lv_obj_add_flag(ui_BTNAutoMenuPrint6, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_BTNAutoMenuPrint6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_opa(ui_BTNAutoMenuPrint6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BTNAutoMenuMove6 = lv_img_create(ui_ScreenMenuConfigEditMenu);
    lv_img_set_src(ui_BTNAutoMenuMove6, &ui_img_photoshoped_assets_timer_glow_png);
    lv_obj_set_width(ui_BTNAutoMenuMove6, 79);
    lv_obj_set_height(ui_BTNAutoMenuMove6, 162);
    lv_obj_set_align(ui_BTNAutoMenuMove6, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_BTNAutoMenuMove6, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_BTNAutoMenuMove6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_opa(ui_BTNAutoMenuMove6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BTNAutoMenuSetting6 = lv_img_create(ui_ScreenMenuConfigEditMenu);
    lv_img_set_src(ui_BTNAutoMenuSetting6, &ui_img_photoshoped_assets_traditional_chinese_settings_zh_chinese_png);
    lv_obj_set_width(ui_BTNAutoMenuSetting6, 79);
    lv_obj_set_height(ui_BTNAutoMenuSetting6, 160);
    lv_obj_set_align(ui_BTNAutoMenuSetting6, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_BTNAutoMenuSetting6, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_BTNAutoMenuSetting6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_opa(ui_BTNAutoMenuSetting6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel_Header5 = lv_obj_create(ui_ScreenMenuConfigEditMenu);
    lv_obj_set_width(ui_Panel_Header5, 665);
    lv_obj_set_height(ui_Panel_Header5, 39);
    lv_obj_set_x(ui_Panel_Header5, -30);
    lv_obj_set_y(ui_Panel_Header5, 0);
    lv_obj_set_align(ui_Panel_Header5, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_Panel_Header5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel_Header5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel_Header5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Panel_Header5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Panel_Header5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel_Header5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label_Header5 = lv_label_create(ui_Panel_Header5);
    lv_obj_set_width(ui_Label_Header5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label_Header5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label_Header5, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Label_Header5, _("User Menu: Edit | Spec"));
    lv_label_set_recolor(ui_Label_Header5, "true");
    lv_obj_set_style_text_color(ui_Label_Header5, lv_color_hex(0x9098AA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label_Header5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label_Header5, &ui_font_Chinese_25_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ScreenAutoContentPanel3 = lv_obj_create(ui_ScreenMenuConfigEditMenu);
    lv_obj_set_width(ui_ScreenAutoContentPanel3, 720);
    lv_obj_set_height(ui_ScreenAutoContentPanel3, 430);
    lv_obj_set_align(ui_ScreenAutoContentPanel3, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_clear_flag(ui_ScreenAutoContentPanel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenAutoContentPanel3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenAutoContentPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_ScreenAutoContentPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_ScreenAutoContentPanel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ScreenAutoContentPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ScreenAutoContentPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ScreenAutoContentPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ScreenAutoContentPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ScreenAutoContentPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelRollerEditMenuChoose = lv_obj_create(ui_ScreenAutoContentPanel3);
    lv_obj_set_height(ui_PanelRollerEditMenuChoose, 215);
    lv_obj_set_width(ui_PanelRollerEditMenuChoose, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_x(ui_PanelRollerEditMenuChoose, -30);
    lv_obj_set_y(ui_PanelRollerEditMenuChoose, 15);
    lv_obj_set_align(ui_PanelRollerEditMenuChoose, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_PanelRollerEditMenuChoose, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelRollerEditMenuChoose, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelRollerEditMenuChoose, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_PanelRollerEditMenuChoose, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_PanelRollerEditMenuChoose, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelRollerEditMenuChoose, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_PanelRollerEditMenuChoose, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_PanelRollerEditMenuChoose, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_PanelRollerEditMenuChoose, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_PanelRollerEditMenuChoose, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelEditMenuText = lv_label_create(ui_PanelRollerEditMenuChoose);
    lv_obj_set_width(ui_LabelEditMenuText, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelEditMenuText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelEditMenuText, -1);
    lv_obj_set_y(ui_LabelEditMenuText, 7);
    lv_obj_set_align(ui_LabelEditMenuText, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_LabelEditMenuText, "點擊\n選取菜單");
    lv_obj_set_style_text_color(ui_LabelEditMenuText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelEditMenuText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelEditMenuText, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelEditMenuText, &ui_font_Chinese_25_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelEditMenuButton = lv_obj_create(ui_ScreenAutoContentPanel3);
    lv_obj_set_width(ui_PanelEditMenuButton, 180);
    lv_obj_set_height(ui_PanelEditMenuButton, 180);
    lv_obj_set_x(ui_PanelEditMenuButton, -31);
    lv_obj_set_y(ui_PanelEditMenuButton, -18);
    lv_obj_set_align(ui_PanelEditMenuButton, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_clear_flag(ui_PanelEditMenuButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelEditMenuButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelEditMenuButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_PanelEditMenuButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_PanelEditMenuButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelEditMenuButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_PanelEditMenuButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_PanelEditMenuButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_PanelEditMenuButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_PanelEditMenuButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BTNEditMenu = lv_img_create(ui_PanelEditMenuButton);
    lv_img_set_src(ui_BTNEditMenu, &ui_img_btn_print_down_png);
    lv_obj_set_width(ui_BTNEditMenu, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_BTNEditMenu, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_BTNEditMenu, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BTNEditMenu, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags

    ui_BTNEditMenuTop = lv_img_create(ui_BTNEditMenu);
    lv_img_set_src(ui_BTNEditMenuTop, &ui_img_btn_print_top_off_png);
    lv_obj_set_width(ui_BTNEditMenuTop, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_BTNEditMenuTop, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_BTNEditMenuTop, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BTNEditMenuTop, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_set_style_radius(ui_BTNEditMenuTop, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_BTNEditMenuTop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_BTNEditMenuTop, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_BTNEditMenuTop, lv_color_hex(0x00D2FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_opa(ui_BTNEditMenuTop, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui_BTNEditMenuTop, 9, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_spread(ui_BTNEditMenuTop, 3, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_x(ui_BTNEditMenuTop, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_y(ui_BTNEditMenuTop, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_color(ui_BTNEditMenuTop, lv_color_hex(0x00D2FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(ui_BTNEditMenuTop, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_BTNEditMenuTop, 5, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_BTNEditMenuTop, 5, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui_BTNEditMenuTop, lv_color_hex(0x67799B), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui_BTNEditMenuTop, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_ImageBTNEditMenu = lv_img_create(ui_BTNEditMenuTop);
    lv_img_set_src(ui_ImageBTNEditMenu, &ui_img_1443512802);
    lv_obj_set_width(ui_ImageBTNEditMenu, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_ImageBTNEditMenu, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_ImageBTNEditMenu, 0);
    lv_obj_set_y(ui_ImageBTNEditMenu, 1);
    lv_obj_set_align(ui_ImageBTNEditMenu, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImageBTNEditMenu, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_img_set_zoom(ui_ImageBTNEditMenu, 200);
    lv_obj_set_style_img_recolor(ui_ImageBTNEditMenu, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_ImageBTNEditMenu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ArcTemperatureShow5 = lv_obj_create(ui_ScreenAutoContentPanel3);
    lv_obj_set_width(ui_ArcTemperatureShow5, 450);
    lv_obj_set_height(ui_ArcTemperatureShow5, 180);
    lv_obj_set_x(ui_ArcTemperatureShow5, -100);
    lv_obj_set_y(ui_ArcTemperatureShow5, -110);
    lv_obj_set_align(ui_ArcTemperatureShow5, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ArcTemperatureShow5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ArcTemperatureShow5, lv_color_hex(0x191D26), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ArcTemperatureShow5, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ArcTemperatureShow5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_ArcTemperatureShow5, lv_color_hex(0x414B62), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_ArcTemperatureShow5, 100, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SliderEditMenuTargetTemp = lv_slider_create(ui_ArcTemperatureShow5);
    lv_slider_set_range(ui_SliderEditMenuTargetTemp, 200, 400);
    lv_slider_set_value(ui_SliderEditMenuTargetTemp, 350, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_SliderEditMenuTargetTemp) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(
            ui_SliderEditMenuTargetTemp, 0, LV_ANIM_OFF);
    lv_obj_set_height(ui_SliderEditMenuTargetTemp, 35);
    lv_obj_set_width(ui_SliderEditMenuTargetTemp, lv_pct(100));
    lv_obj_set_align(ui_SliderEditMenuTargetTemp, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_bg_color(ui_SliderEditMenuTargetTemp, lv_color_hex(0x222733), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderEditMenuTargetTemp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_SliderEditMenuTargetTemp, lv_color_hex(0x191D26), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_SliderEditMenuTargetTemp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_SliderEditMenuTargetTemp, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_SliderEditMenuTargetTemp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SliderEditMenuTargetTemp, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SliderEditMenuTargetTemp, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SliderEditMenuTargetTemp, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SliderEditMenuTargetTemp, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_SliderEditMenuTargetTemp, lv_color_hex(0x1DE8FF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderEditMenuTargetTemp, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_SliderEditMenuTargetTemp, lv_color_hex(0x0962B7),
                                   LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_SliderEditMenuTargetTemp, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_SliderEditMenuTargetTemp, lv_color_hex(0x7689AC), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderEditMenuTargetTemp, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_SliderEditMenuTargetTemp, lv_color_hex(0x556483), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_SliderEditMenuTargetTemp, LV_GRAD_DIR_VER, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_SliderEditMenuTargetTemp, lv_color_hex(0x28DCFD), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_SliderEditMenuTargetTemp, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_SliderEditMenuTargetTemp, 1, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_SliderEditMenuTargetTemp, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_SliderEditMenuTargetTemp, -2, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_SliderEditMenuTargetTemp, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SliderEditMenuTargetTemp, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SliderEditMenuTargetTemp, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SliderEditMenuTargetTemp, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SliderEditMenuTargetTemp, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_MenuOptionRoller4 = lv_obj_create(ui_ArcTemperatureShow5);
    lv_obj_set_width(ui_MenuOptionRoller4, lv_pct(70));
    lv_obj_set_height(ui_MenuOptionRoller4, lv_pct(70));
    lv_obj_set_align(ui_MenuOptionRoller4, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_MenuOptionRoller4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MenuOptionRoller4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MenuOptionRoller4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MenuOptionRoller4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MenuOptionRoller4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_MenuOptionRoller4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_MenuOptionRoller4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_MenuOptionRoller4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_MenuOptionRoller4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_MenuOptionRoller4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSensorTemperature6 = lv_label_create(ui_MenuOptionRoller4);
    lv_obj_set_width(ui_LabelSensorTemperature6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSensorTemperature6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelSensorTemperature6, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_LabelSensorTemperature6, _("Set Temp"));
    lv_label_set_recolor(ui_LabelSensorTemperature6, "true");
    lv_obj_set_style_text_color(ui_LabelSensorTemperature6, lv_color_hex(0x9098AA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelSensorTemperature6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelSensorTemperature6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelSensorTemperature6, &ui_font_Chinese_25_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelEditMenuTargetTemperature = lv_label_create(ui_MenuOptionRoller4);
    lv_obj_set_width(ui_LabelEditMenuTargetTemperature, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelEditMenuTargetTemperature, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelEditMenuTargetTemperature, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_LabelEditMenuTargetTemperature, "350°F");
    lv_obj_set_style_text_color(ui_LabelEditMenuTargetTemperature, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelEditMenuTargetTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelEditMenuTargetTemperature, &ui_font_Montserrat_64, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelEditMenuCountdown = lv_obj_create(ui_ScreenAutoContentPanel3);
    lv_obj_set_width(ui_PanelEditMenuCountdown, 450);
    lv_obj_set_height(ui_PanelEditMenuCountdown, 180);
    lv_obj_set_x(ui_PanelEditMenuCountdown, -101);
    lv_obj_set_y(ui_PanelEditMenuCountdown, -26);
    lv_obj_set_align(ui_PanelEditMenuCountdown, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_PanelEditMenuCountdown, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelEditMenuCountdown, lv_color_hex(0x191D26), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelEditMenuCountdown, 160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelEditMenuCountdown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_PanelEditMenuCountdown, lv_color_hex(0x414B62), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_PanelEditMenuCountdown, 100, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SliderEditMenuTargetCountdown = lv_slider_create(ui_PanelEditMenuCountdown);
    lv_slider_set_range(ui_SliderEditMenuTargetCountdown, 0, 90);
    lv_slider_set_value(ui_SliderEditMenuTargetCountdown, 18, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_SliderEditMenuTargetCountdown) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(
            ui_SliderEditMenuTargetCountdown, 0, LV_ANIM_OFF);
    lv_obj_set_height(ui_SliderEditMenuTargetCountdown, 35);
    lv_obj_set_width(ui_SliderEditMenuTargetCountdown, lv_pct(100));
    lv_obj_set_align(ui_SliderEditMenuTargetCountdown, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_bg_color(ui_SliderEditMenuTargetCountdown, lv_color_hex(0x222733), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderEditMenuTargetCountdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_SliderEditMenuTargetCountdown, lv_color_hex(0x191D26),
                                   LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_SliderEditMenuTargetCountdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_SliderEditMenuTargetCountdown, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_SliderEditMenuTargetCountdown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SliderEditMenuTargetCountdown, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SliderEditMenuTargetCountdown, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SliderEditMenuTargetCountdown, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SliderEditMenuTargetCountdown, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_SliderEditMenuTargetCountdown, lv_color_hex(0x1DE8FF),
                              LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderEditMenuTargetCountdown, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_SliderEditMenuTargetCountdown, lv_color_hex(0x0962B7),
                                   LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_SliderEditMenuTargetCountdown, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_SliderEditMenuTargetCountdown, lv_color_hex(0x7689AC), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderEditMenuTargetCountdown, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_SliderEditMenuTargetCountdown, lv_color_hex(0x556483),
                                   LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_SliderEditMenuTargetCountdown, LV_GRAD_DIR_VER, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_SliderEditMenuTargetCountdown, lv_color_hex(0x28DCFD),
                                  LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_SliderEditMenuTargetCountdown, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_SliderEditMenuTargetCountdown, 1, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_SliderEditMenuTargetCountdown, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_SliderEditMenuTargetCountdown, -2, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_SliderEditMenuTargetCountdown, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SliderEditMenuTargetCountdown, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SliderEditMenuTargetCountdown, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SliderEditMenuTargetCountdown, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SliderEditMenuTargetCountdown, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_LabelEditMenuCountdownText = lv_label_create(ui_PanelEditMenuCountdown);
    lv_obj_set_width(ui_LabelEditMenuCountdownText, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelEditMenuCountdownText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelEditMenuCountdownText, 0);
    lv_obj_set_y(ui_LabelEditMenuCountdownText, -5);
    lv_obj_set_align(ui_LabelEditMenuCountdownText, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_LabelEditMenuCountdownText, _("Set Countdown"));
    lv_label_set_recolor(ui_LabelEditMenuCountdownText, "true");
    lv_obj_set_style_text_color(ui_LabelEditMenuCountdownText, lv_color_hex(0x9098AA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelEditMenuCountdownText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelEditMenuCountdownText, &ui_font_Chinese_25_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelEditMenuCountdown = lv_label_create(ui_PanelEditMenuCountdown);
    lv_obj_set_width(ui_LabelEditMenuCountdown, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelEditMenuCountdown, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelEditMenuCountdown, 0);
    lv_obj_set_y(ui_LabelEditMenuCountdown, -10);
    lv_obj_set_align(ui_LabelEditMenuCountdown, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelEditMenuCountdown, "03:00");
    lv_label_set_recolor(ui_LabelEditMenuCountdown, "true");
    lv_obj_set_style_text_color(ui_LabelEditMenuCountdown, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelEditMenuCountdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelEditMenuCountdown, &ui_font_Montserrat_64, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_BTNAutoMenuPrint6, ui_event_BTNAutoMenuPrint6, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BTNAutoMenuMove6, ui_event_BTNAutoMenuMove6, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BTNEditMenuTop, ui_event_BTNEditMenuTop, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SliderEditMenuTargetTemp, ui_event_SliderEditMenuTargetTemp, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SliderEditMenuTargetCountdown, ui_event_SliderEditMenuTargetCountdown, LV_EVENT_ALL, NULL);

}
