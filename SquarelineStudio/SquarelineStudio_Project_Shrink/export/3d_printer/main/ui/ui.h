// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.3
// Project name: 3d_printer

#ifndef _3D_PRINTER_UI_H
#define _3D_PRINTER_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "lv_i18n.h"
#include "ui_helpers.h"
#include "ui_events.h"
void OpaOn_Animation(lv_obj_t * TargetObject, int delay);
void OpaOff_Animation(lv_obj_t * TargetObject, int delay);
void ScreenIn_Animation(lv_obj_t * TargetObject, int delay);
void MenuIn_Animation(lv_obj_t * TargetObject, int delay);
void MenuOut_Animation(lv_obj_t * TargetObject, int delay);
void ScreenOut_Animation(lv_obj_t * TargetObject, int delay);
// SCREEN: ui_ScreenManual
void ui_ScreenManual_screen_init(void);
extern lv_obj_t * ui_ScreenManual;
extern lv_obj_t * ui_MainBackground;
extern lv_obj_t * ui_LeftPanel;
extern lv_obj_t * ui_ScreenAutoBackgroundPicture1;
extern lv_obj_t * ui_NotificationPanel;
extern lv_obj_t * ui_ScreenAutoHeader1;
extern lv_obj_t * ui_LabelAutoHeader1;
extern lv_obj_t * ui_LabelHeaderVersionNumber;
extern lv_obj_t * ui_BTNAutoMenuPrint1;
void ui_event_BTNAutoMenuMove1(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuMove1;
void ui_event_BTNAutoMenuSetting1(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuSetting1;
extern lv_obj_t * ui_ScreenAutoContentPanel1;
extern lv_obj_t * ui_DisplayTempRemainCountdown2;
extern lv_obj_t * ui_TemperaturePanel1;
extern lv_obj_t * ui_LabelSensorTemperature4;
extern lv_obj_t * ui_LabelSensorTempValue1;
extern lv_obj_t * ui_Splitter3;
extern lv_obj_t * ui_TemperaturePanel2;
extern lv_obj_t * ui_LabelSensorTemperature5;
extern lv_obj_t * ui_LabelSensorTempValue2;
extern lv_obj_t * ui_Panel_Buttons_S1;
extern lv_obj_t * ui_BTNStartMenu1;
void ui_event_BTNStartMenuTop1(lv_event_t * e);
extern lv_obj_t * ui_BTNStartMenuTop1;
extern lv_obj_t * ui_ImageBTNStartMenu1;
extern lv_obj_t * ui_ArcTemperatureShow2;
extern lv_obj_t * ui_LabelSensorTemperature3;
extern lv_obj_t * ui_LabelManualTargetTemperature;
void ui_event_SliderManualTargetTemperature(lv_event_t * e);
extern lv_obj_t * ui_SliderManualTargetTemperature;
extern lv_obj_t * ui_ArcTemperatureShow1;
extern lv_obj_t * ui_LabelSensorTemperature1;
extern lv_obj_t * ui_LabelManualTimerSet;
void ui_event_BarManualTemperature1(lv_event_t * e);
extern lv_obj_t * ui_BarManualTemperature1;
// SCREEN: ui_ScreenAuto
void ui_ScreenAuto_screen_init(void);
extern lv_obj_t * ui_ScreenAuto;
extern lv_obj_t * ui_ScreenAutoBackgroundPicture;
extern lv_obj_t * ui_ScreenAutoHeader;
extern lv_obj_t * ui_LabelAutoHeader;
extern lv_obj_t * ui_LabelHeaderVersionNumber1;
void ui_event_BTNAutoMenuPrint(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuPrint;
extern lv_obj_t * ui_BTNAutoMenuMove;
void ui_event_BTNAutoMenuSetting(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuSetting;
extern lv_obj_t * ui_ScreenAutoContentPanel;
extern lv_obj_t * ui_DisplayTempRemainCountdown;
extern lv_obj_t * ui_DTRC0;
extern lv_obj_t * ui_LabelSensorTemperature;
extern lv_obj_t * ui_LabelSensorTempValue;
extern lv_obj_t * ui_Splitter1;
extern lv_obj_t * ui_DTRC2;
extern lv_obj_t * ui_LabelSetTime;
extern lv_obj_t * ui_LabelSetTimeValue;
extern lv_obj_t * ui_Panel_Buttons_S3;
extern lv_obj_t * ui_BTNStartMenu;
void ui_event_BTNStartMenuTop(lv_event_t * e);
extern lv_obj_t * ui_BTNStartMenuTop;
extern lv_obj_t * ui_ImageBTNStartMenu;
extern lv_obj_t * ui_MenuOptionRoller;
extern lv_obj_t * ui_IMGMenuOptionRoller;
void ui_event_MenuOptionRollerChoose(lv_event_t * e);
extern lv_obj_t * ui_MenuOptionRollerChoose;
extern lv_obj_t * ui_ArcTemperatureShow;
extern lv_obj_t * ui_DTRC3;
extern lv_obj_t * ui_LabelSensorTemperature2;
extern lv_obj_t * ui_LabelTargetTemperatureValue;
extern lv_obj_t * ui_BarCountDownTemperature;
// SCREEN: ui_ScreenSetting
void ui_ScreenSetting_screen_init(void);
extern lv_obj_t * ui_ScreenSetting;
extern lv_obj_t * ui_Background2;
void ui_event_BTNAutoMenuPrint2(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuPrint2;
void ui_event_BTNAutoMenuMove2(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuMove2;
extern lv_obj_t * ui_BTNAutoMenuSetting2;
extern lv_obj_t * ui_Panel_Header2;
extern lv_obj_t * ui_Label_Header2;
extern lv_obj_t * ui_S1_Content_Panel2;
extern lv_obj_t * ui_Roller_Material;
extern lv_obj_t * ui_Image3;
extern lv_obj_t * ui_Roller4;
extern lv_obj_t * ui_Label_Material;
extern lv_obj_t * ui_Roller_Bed_Temp;
extern lv_obj_t * ui_Image2;
extern lv_obj_t * ui_Roller3;
extern lv_obj_t * ui_Label_Bed_Temp1;
extern lv_obj_t * ui_Roller_Head_Temp;
extern lv_obj_t * ui_Image1;
void ui_event_Roller2(lv_event_t * e);
extern lv_obj_t * ui_Roller2;
extern lv_obj_t * ui_Label_Head_Temp1;
void ui_event_BTN_Heat_Head(lv_event_t * e);
extern lv_obj_t * ui_BTN_Heat_Head;
extern lv_obj_t * ui_Label_Reset22;
extern lv_obj_t * ui_BTN_Heat_Bed;
extern lv_obj_t * ui_Label_Heat_Bed;
extern lv_obj_t * ui_BTN_Remove_Filament;
extern lv_obj_t * ui_Label_Remove_Filament;
extern lv_obj_t * ui_Panel_Slider;
void ui_event_Slider_Print_Speed(lv_event_t * e);
extern lv_obj_t * ui_Slider_Print_Speed;
extern lv_obj_t * ui_Label_Print_Speed;
extern lv_obj_t * ui_Label_Print_Speed_Number;
extern lv_obj_t * ui_Swich_Group;
extern lv_obj_t * ui_Label_Light;
void ui_event_Switch_Light(lv_event_t * e);
extern lv_obj_t * ui_Switch_Light;
extern lv_obj_t * ui_Label_Celsius;
extern lv_obj_t * ui_Label_Farenheit;
extern lv_obj_t * ui_Label_Demo_Mode;
void ui_event_Switch_Demo_Mode(lv_event_t * e);
extern lv_obj_t * ui_Switch_Demo_Mode;
extern lv_obj_t * ui_Label_Fan_2;
extern lv_obj_t * ui_Switch_Fan_2;
extern lv_obj_t * ui_Label_Fan_3;
extern lv_obj_t * ui_Switch_Fan_3;
// SCREEN: ui_ScreenMenuConfiguration
void ui_ScreenMenuConfiguration_screen_init(void);
extern lv_obj_t * ui_ScreenMenuConfiguration;
extern lv_obj_t * ui_Background1;
void ui_event_BTNAutoMenuPrint3(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuPrint3;
void ui_event_BTNAutoMenuMove3(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuMove3;
extern lv_obj_t * ui_BTNAutoMenuSetting3;
extern lv_obj_t * ui_Panel_Header1;
extern lv_obj_t * ui_Label_Header1;
extern lv_obj_t * ui_S1_Content_Panel1;
void ui_event_AddMenuToJSON(lv_event_t * e);
extern lv_obj_t * ui_AddMenuToJSON;
extern lv_obj_t * ui_LabelNewMenu;
extern lv_obj_t * ui_Image5;
void ui_event_EditMenuToJSON(lv_event_t * e);
extern lv_obj_t * ui_EditMenuToJSON;
extern lv_obj_t * ui_LabelEditMenu;
extern lv_obj_t * ui_Image4;
void ui_event_DeleteMenuToJSON(lv_event_t * e);
extern lv_obj_t * ui_DeleteMenuToJSON;
extern lv_obj_t * ui_LabelDeleteMenu;
extern lv_obj_t * ui_Image6;
// SCREEN: ui_ScreenMenuConfigCreateMenu
void ui_ScreenMenuConfigCreateMenu_screen_init(void);
extern lv_obj_t * ui_ScreenMenuConfigCreateMenu;
extern lv_obj_t * ui_Background3;
void ui_event_BTNAutoMenuPrint4(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuPrint4;
void ui_event_BTNAutoMenuMove4(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuMove4;
extern lv_obj_t * ui_BTNAutoMenuSetting4;
extern lv_obj_t * ui_Panel_Header3;
extern lv_obj_t * ui_Label_Header3;
extern lv_obj_t * ui_ScreenAutoContentPanel2;
extern lv_obj_t * ui_PanelRollerCreateMenuChoose;
extern lv_obj_t * ui_LabelCreateMenuText;
extern lv_obj_t * ui_DropdownCreateMenuChoose;
extern lv_obj_t * ui_PanelCreateMenuButton;
extern lv_obj_t * ui_BTNCreateMenu;
void ui_event_BTNCreateMenuTop(lv_event_t * e);
extern lv_obj_t * ui_BTNCreateMenuTop;
extern lv_obj_t * ui_ImageBTNCreateMenu;
extern lv_obj_t * ui_ArcTemperatureShow3;
void ui_event_SliderCreateMenuTargetTemp(lv_event_t * e);
extern lv_obj_t * ui_SliderCreateMenuTargetTemp;
extern lv_obj_t * ui_MenuOptionRoller3;
extern lv_obj_t * ui_LabelSensorTemperature9;
extern lv_obj_t * ui_LabelCreateMenuTargetTemperature;
extern lv_obj_t * ui_ArcTemperatureShow4;
void ui_event_SliderCreateMenuTargetCountdown(lv_event_t * e);
extern lv_obj_t * ui_SliderCreateMenuTargetCountdown;
extern lv_obj_t * ui_LabelCreateMenuCountdownText;
extern lv_obj_t * ui_LabelCreateMenuCountdown;
// SCREEN: ui_ScreenMenuConfigDeleteMenu
void ui_ScreenMenuConfigDeleteMenu_screen_init(void);
extern lv_obj_t * ui_ScreenMenuConfigDeleteMenu;
extern lv_obj_t * ui_Background4;
void ui_event_BTNAutoMenuPrint5(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuPrint5;
void ui_event_BTNAutoMenuMove5(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuMove5;
extern lv_obj_t * ui_BTNAutoMenuSetting5;
extern lv_obj_t * ui_Panel_Header4;
extern lv_obj_t * ui_Label_Header4;
extern lv_obj_t * ui_ScreenMenuConfigDelMenu;
extern lv_obj_t * ui_PanelRollerDeleteMenuChoose;
extern lv_obj_t * ui_IMGRollerDeleteMenuChoose;
void ui_event_RollerDeleteMenuChoose(lv_event_t * e);
extern lv_obj_t * ui_RollerDeleteMenuChoose;
extern lv_obj_t * ui_PanelRollerDeleteMenuChooseBTN;
extern lv_obj_t * ui_BTNDeleteMenuChoose;
void ui_event_BTNDeleteMenuChooseTop(lv_event_t * e);
extern lv_obj_t * ui_BTNDeleteMenuChooseTop;
extern lv_obj_t * ui_ImageBTNDeleteMenuChoose;
// SCREEN: ui_ScreenMenuConfigEditMenuSelect
void ui_ScreenMenuConfigEditMenuSelect_screen_init(void);
extern lv_obj_t * ui_ScreenMenuConfigEditMenuSelect;
extern lv_obj_t * ui_Background6;
void ui_event_BTNAutoMenuPrint7(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuPrint7;
void ui_event_BTNAutoMenuMove7(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuMove7;
extern lv_obj_t * ui_BTNAutoMenuSetting7;
extern lv_obj_t * ui_Panel_Header6;
extern lv_obj_t * ui_Label_Header6;
extern lv_obj_t * ui_ScreenMenuConfigDelMenu1;
extern lv_obj_t * ui_DropdownEditMenuChoose;
extern lv_obj_t * ui_PanelRollerDeleteMenuChooseBTN1;
extern lv_obj_t * ui_BTNDeleteMenuChoose1;
void ui_event_BTNDeleteMenuChooseTop1(lv_event_t * e);
extern lv_obj_t * ui_BTNDeleteMenuChooseTop1;
extern lv_obj_t * ui_ImageBTNDeleteMenuChoose1;
// SCREEN: ui_ScreenMenuConfigEditMenu
void ui_ScreenMenuConfigEditMenu_screen_init(void);
extern lv_obj_t * ui_ScreenMenuConfigEditMenu;
extern lv_obj_t * ui_Background5;
void ui_event_BTNAutoMenuPrint6(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuPrint6;
void ui_event_BTNAutoMenuMove6(lv_event_t * e);
extern lv_obj_t * ui_BTNAutoMenuMove6;
extern lv_obj_t * ui_BTNAutoMenuSetting6;
extern lv_obj_t * ui_Panel_Header5;
extern lv_obj_t * ui_Label_Header5;
extern lv_obj_t * ui_ScreenAutoContentPanel3;
extern lv_obj_t * ui_PanelRollerEditMenuChoose;
extern lv_obj_t * ui_LabelEditMenuText;
extern lv_obj_t * ui_PanelEditMenuButton;
extern lv_obj_t * ui_BTNEditMenu;
void ui_event_BTNEditMenuTop(lv_event_t * e);
extern lv_obj_t * ui_BTNEditMenuTop;
extern lv_obj_t * ui_ImageBTNEditMenu;
extern lv_obj_t * ui_ArcTemperatureShow5;
void ui_event_SliderEditMenuTargetTemp(lv_event_t * e);
extern lv_obj_t * ui_SliderEditMenuTargetTemp;
extern lv_obj_t * ui_MenuOptionRoller4;
extern lv_obj_t * ui_LabelSensorTemperature6;
extern lv_obj_t * ui_LabelEditMenuTargetTemperature;
extern lv_obj_t * ui_PanelEditMenuCountdown;
void ui_event_SliderEditMenuTargetCountdown(lv_event_t * e);
extern lv_obj_t * ui_SliderEditMenuTargetCountdown;
extern lv_obj_t * ui_LabelEditMenuCountdownText;
extern lv_obj_t * ui_LabelEditMenuCountdown;
// SCREEN: ui_ScreenScreenSaverMenu
void ui_ScreenScreenSaverMenu_screen_init(void);
extern lv_obj_t * ui_ScreenScreenSaverMenu;
void ui_event_PanelMenu(lv_event_t * e);
extern lv_obj_t * ui_PanelMenu;
extern lv_obj_t * ui_LabelMenuName;
extern lv_obj_t * ui_LabelPressAnywhereToExit;
extern lv_obj_t * ui_Panel2;
extern lv_obj_t * ui_ScreenSaverLeftPanel;
extern lv_obj_t * ui_LabelScreenSaverCookingState;
extern lv_obj_t * ui_ScreenSaverRightPanel;
extern lv_obj_t * ui_LabelScreenSaverCookingCountdown;
extern lv_obj_t * ui_Splitter2;
// SCREEN: ui_ScreenDropFood
void ui_ScreenDropFood_screen_init(void);
extern lv_obj_t * ui_ScreenDropFood;
extern lv_obj_t * ui_PanelMenu1;
extern lv_obj_t * ui_LabelDropFood;
extern lv_obj_t * ui_LabelDropFoodReminder;
void ui_event_ButtonDropFoodDone(lv_event_t * e);
extern lv_obj_t * ui_ButtonDropFoodDone;
extern lv_obj_t * ui_LabelDropFoodDone;
extern lv_obj_t * ui_LabelDropFoodDoneSeconds;
extern lv_obj_t * ui____initial_actions0;

LV_IMG_DECLARE(
    ui_img_photoshoped_assets_chinese_backgorund_chinese_png);    // assets\Photoshoped_assets\Chinese\Backgorund_Chinese.png
LV_IMG_DECLARE(
    ui_img_photoshoped_assets_chinese_manual_chinese_png);    // assets\Photoshoped_assets\Chinese\Manual_Chinese.png
LV_IMG_DECLARE(
    ui_img_photoshoped_assets_chinese_timer_chinese_png);    // assets\Photoshoped_assets\Chinese\Timer_Chinese.png
LV_IMG_DECLARE(
    ui_img_photoshoped_assets_traditional_chinese_settings_zh_chinese_png);    // assets\Photoshoped_assets\Traditional_Chinese\Settings_ZH_Chinese.png
LV_IMG_DECLARE(ui_img_btn_print_down_png);    // assets\btn_print_down.png
LV_IMG_DECLARE(ui_img_btn_print_top_off_png);    // assets\btn_print_top_off.png
LV_IMG_DECLARE(ui_img_2126067643);    // assets\icons8-play-96.png
LV_IMG_DECLARE(ui_img_roller_bg_png);    // assets\roller_bg.png
LV_IMG_DECLARE(ui_img_photoshoped_assets_manual_glow_png);    // assets\Photoshoped_assets\Manual_glow.png
LV_IMG_DECLARE(ui_img_photoshoped_assets_timer_glow_png);    // assets\Photoshoped_assets\Timer_glow.png
LV_IMG_DECLARE(ui_img_btn_main_off_png);    // assets\btn_main_off.png
LV_IMG_DECLARE(ui_img_btn_main_on_png);    // assets\btn_main_on.png
LV_IMG_DECLARE(ui_img_1627854363);    // assets\icons8-plus-120.png
LV_IMG_DECLARE(ui_img_1688661777);    // assets\icons8-edit-120.png
LV_IMG_DECLARE(ui_img_1244952608);    // assets\icons8-delete-120.png
LV_IMG_DECLARE(ui_img_984416508);    // assets\icons8-add-90.png
LV_IMG_DECLARE(ui_img_821558544);    // assets\icons8-delete-90.png
LV_IMG_DECLARE(ui_img_1158544786);    // assets\icons8-pencil-90.png
LV_IMG_DECLARE(ui_img_1443512802);    // assets\icons8-save-90.png
LV_IMG_DECLARE(ui_img_icn_time_1_png);    // assets\icn_time_1.png
LV_IMG_DECLARE(ui_img_icn_time_2_png);    // assets\icn_time_2.png
LV_IMG_DECLARE(ui_img_526273827);    // assets\icons8-add-file-90.png
LV_IMG_DECLARE(ui_img_987395607);    // assets\icons8-delete-240.png
LV_IMG_DECLARE(ui_img_1405798654);    // assets\icons8-delete-30.png
LV_IMG_DECLARE(ui_img_772459689);    // assets\icons8-delete-480.png
LV_IMG_DECLARE(ui_img_565988525);    // assets\icons8-delete-60.png
LV_IMG_DECLARE(ui_img_1519923167);    // assets\icons8-delete-file-90.png
LV_IMG_DECLARE(ui_img_572867443);    // assets\icons8-done-120.png
LV_IMG_DECLARE(ui_img_1946231078);    // assets\icons8-edit-480.png
LV_IMG_DECLARE(ui_img_839169762);    // assets\icons8-edit-60.png
LV_IMG_DECLARE(ui_img_552494413);    // assets\icons8-play-100.png
LV_IMG_DECLARE(ui_img_1392977354);    // assets\icons8-play-48.png
LV_IMG_DECLARE(ui_img_2094120521);    // assets\icons8-play-50.png
LV_IMG_DECLARE(ui_img_1329794544);    // assets\icons8-plus-240.png
LV_IMG_DECLARE(ui_img_614800514);    // assets\icons8-plus-480.png
LV_IMG_DECLARE(ui_img_1722068059);    // assets\icons8-plus-90.png

LV_FONT_DECLARE(ui_font_Chinese_25_Bold);
LV_FONT_DECLARE(ui_font_Chinese_30_Bold);
LV_FONT_DECLARE(ui_font_Chinese_48_Bold);
LV_FONT_DECLARE(ui_font_Chinese_65_Bold);
LV_FONT_DECLARE(ui_font_Montserrat_64);
LV_FONT_DECLARE(ui_font_NumberDotFont);
LV_FONT_DECLARE(ui_font_Small_Font);
LV_FONT_DECLARE(ui_font_Chinese_20_Bold);
LV_FONT_DECLARE(ui_font_Chinese_60_Bold);
LV_FONT_DECLARE(ui_font_Chinese_70_Bold);
LV_FONT_DECLARE(ui_font_Chinese_Small);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif