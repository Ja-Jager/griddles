// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.1
// LVGL version: 8.3.3
// Project name: 3d_printer

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void OpaOn_Animation(lv_obj_t * TargetObject, int delay);
void OpaOff_Animation(lv_obj_t * TargetObject, int delay);
void ScreenIn_Animation(lv_obj_t * TargetObject, int delay);
void MenuIn_Animation(lv_obj_t * TargetObject, int delay);
void MenuOut_Animation(lv_obj_t * TargetObject, int delay);
void ScreenOut_Animation(lv_obj_t * TargetObject, int delay);

// SCREEN: ui_ScreenManual
void ui_ScreenManual_screen_init(void);
lv_obj_t * ui_ScreenManual;
lv_obj_t * ui_MainBackground;
lv_obj_t * ui_LeftPanel;
lv_obj_t * ui_ScreenAutoBackgroundPicture1;
lv_obj_t * ui_NotificationPanel;
lv_obj_t * ui_ScreenAutoHeader1;
lv_obj_t * ui_LabelAutoHeader1;
lv_obj_t * ui_LabelHeaderVersionNumber;
lv_obj_t * ui_BTNAutoMenuPrint1;
void ui_event_BTNAutoMenuMove1(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuMove1;
void ui_event_BTNAutoMenuSetting1(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuSetting1;
lv_obj_t * ui_ScreenAutoContentPanel1;
lv_obj_t * ui_DisplayTempRemainCountdown2;
lv_obj_t * ui_TemperaturePanel1;
lv_obj_t * ui_LabelSensorTemperature4;
lv_obj_t * ui_LabelSensorTempValue1;
lv_obj_t * ui_Splitter3;
lv_obj_t * ui_TemperaturePanel2;
lv_obj_t * ui_LabelSensorTemperature5;
lv_obj_t * ui_LabelSensorTempValue2;
lv_obj_t * ui_Panel_Buttons_S1;
lv_obj_t * ui_BTNStartMenu1;
void ui_event_BTNStartMenuTop1(lv_event_t * e);
lv_obj_t * ui_BTNStartMenuTop1;
lv_obj_t * ui_ImageBTNStartMenu1;
lv_obj_t * ui_ArcTemperatureShow2;
lv_obj_t * ui_LabelSensorTemperature3;
lv_obj_t * ui_LabelManualTargetTemperature;
void ui_event_SliderManualTargetTemperature(lv_event_t * e);
lv_obj_t * ui_SliderManualTargetTemperature;
lv_obj_t * ui_ArcTemperatureShow1;
lv_obj_t * ui_LabelSensorTemperature1;
lv_obj_t * ui_LabelManualTimerSet;
void ui_event_BarManualTemperature1(lv_event_t * e);
lv_obj_t * ui_BarManualTemperature1;
void ui_event_DropdownMotorLeftRightManual(lv_event_t * e);
lv_obj_t * ui_DropdownMotorLeftRightManual;

// SCREEN: ui_ScreenAuto
void ui_ScreenAuto_screen_init(void);
lv_obj_t * ui_ScreenAuto;
lv_obj_t * ui_ScreenAutoBackgroundPicture;
lv_obj_t * ui_ScreenAutoHeader;
lv_obj_t * ui_LabelAutoHeader;
lv_obj_t * ui_LabelHeaderVersionNumber1;
void ui_event_BTNAutoMenuPrint(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuPrint;
lv_obj_t * ui_BTNAutoMenuMove;
void ui_event_BTNAutoMenuSetting(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuSetting;
lv_obj_t * ui_ScreenAutoContentPanel;
lv_obj_t * ui_DisplayTempRemainCountdown;
lv_obj_t * ui_DTRC0;
lv_obj_t * ui_LabelSensorTemperature;
lv_obj_t * ui_LabelSensorTempValue;
lv_obj_t * ui_Splitter1;
lv_obj_t * ui_DTRC2;
lv_obj_t * ui_LabelSetTime;
lv_obj_t * ui_LabelSetTimeValue;
lv_obj_t * ui_Panel_Buttons_S3;
lv_obj_t * ui_BTNStartMenu;
void ui_event_BTNStartMenuTop(lv_event_t * e);
lv_obj_t * ui_BTNStartMenuTop;
lv_obj_t * ui_ImageBTNStartMenu;
lv_obj_t * ui_MenuOptionRoller;
lv_obj_t * ui_IMGMenuOptionRoller;
void ui_event_MenuOptionRollerChoose(lv_event_t * e);
lv_obj_t * ui_MenuOptionRollerChoose;
lv_obj_t * ui_ArcTemperatureShow;
lv_obj_t * ui_DTRC3;
lv_obj_t * ui_LabelSensorTemperature2;
lv_obj_t * ui_LabelTargetTemperatureValue;
lv_obj_t * ui_BarCountDownTemperature;
void ui_event_DropdownMotorLeftRightAuto(lv_event_t * e);
lv_obj_t * ui_DropdownMotorLeftRightAuto;

// SCREEN: ui_ScreenSetting
void ui_ScreenSetting_screen_init(void);
lv_obj_t * ui_ScreenSetting;
lv_obj_t * ui_Background2;
void ui_event_BTNAutoMenuPrint2(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuPrint2;
void ui_event_BTNAutoMenuMove2(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuMove2;
lv_obj_t * ui_BTNAutoMenuSetting2;
lv_obj_t * ui_Panel_Header2;
lv_obj_t * ui_Label_Header2;
lv_obj_t * ui_S1_Content_Panel2;
lv_obj_t * ui_Roller_Material;
lv_obj_t * ui_Image3;
lv_obj_t * ui_Roller4;
lv_obj_t * ui_Label_Material;
lv_obj_t * ui_Roller_Bed_Temp;
lv_obj_t * ui_Image2;
lv_obj_t * ui_Roller3;
lv_obj_t * ui_Label_Bed_Temp1;
lv_obj_t * ui_Roller_Head_Temp;
lv_obj_t * ui_Image1;
void ui_event_Roller2(lv_event_t * e);
lv_obj_t * ui_Roller2;
lv_obj_t * ui_Label_Head_Temp1;
void ui_event_BTN_Heat_Head(lv_event_t * e);
lv_obj_t * ui_BTN_Heat_Head;
lv_obj_t * ui_Label_Reset22;
lv_obj_t * ui_BTN_Heat_Bed;
lv_obj_t * ui_Label_Heat_Bed;
lv_obj_t * ui_BTN_Remove_Filament;
lv_obj_t * ui_Label_Remove_Filament;
lv_obj_t * ui_Panel_Slider;
void ui_event_Slider_Print_Speed(lv_event_t * e);
lv_obj_t * ui_Slider_Print_Speed;
lv_obj_t * ui_Label_Print_Speed;
lv_obj_t * ui_Label_Print_Speed_Number;
lv_obj_t * ui_Swich_Group;
lv_obj_t * ui_Label_Light;
void ui_event_Switch_Light(lv_event_t * e);
lv_obj_t * ui_Switch_Light;
lv_obj_t * ui_Label_Celsius;
lv_obj_t * ui_Label_Farenheit;
lv_obj_t * ui_Label_Demo_Mode;
void ui_event_Switch_Demo_Mode(lv_event_t * e);
lv_obj_t * ui_Switch_Demo_Mode;
lv_obj_t * ui_Label_Fan_2;
lv_obj_t * ui_Switch_Fan_2;
lv_obj_t * ui_Label_Fan_3;
lv_obj_t * ui_Switch_Fan_3;

// SCREEN: ui_ScreenMenuConfiguration
void ui_ScreenMenuConfiguration_screen_init(void);
lv_obj_t * ui_ScreenMenuConfiguration;
lv_obj_t * ui_Background1;
void ui_event_BTNAutoMenuPrint3(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuPrint3;
void ui_event_BTNAutoMenuMove3(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuMove3;
lv_obj_t * ui_BTNAutoMenuSetting3;
lv_obj_t * ui_Panel_Header1;
lv_obj_t * ui_Label_Header1;
lv_obj_t * ui_S1_Content_Panel1;
void ui_event_AddMenuToJSON(lv_event_t * e);
lv_obj_t * ui_AddMenuToJSON;
lv_obj_t * ui_LabelNewMenu;
lv_obj_t * ui_Image5;
void ui_event_EditMenuToJSON(lv_event_t * e);
lv_obj_t * ui_EditMenuToJSON;
lv_obj_t * ui_LabelEditMenu;
lv_obj_t * ui_Image4;
void ui_event_DeleteMenuToJSON(lv_event_t * e);
lv_obj_t * ui_DeleteMenuToJSON;
lv_obj_t * ui_LabelDeleteMenu;
lv_obj_t * ui_Image6;

// SCREEN: ui_ScreenMenuConfigCreateMenu
void ui_ScreenMenuConfigCreateMenu_screen_init(void);
lv_obj_t * ui_ScreenMenuConfigCreateMenu;
lv_obj_t * ui_Background3;
void ui_event_BTNAutoMenuPrint4(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuPrint4;
void ui_event_BTNAutoMenuMove4(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuMove4;
lv_obj_t * ui_BTNAutoMenuSetting4;
lv_obj_t * ui_Panel_Header3;
lv_obj_t * ui_Label_Header3;
lv_obj_t * ui_ScreenAutoContentPanel2;
lv_obj_t * ui_PanelRollerCreateMenuChoose;
lv_obj_t * ui_LabelCreateMenuText;
lv_obj_t * ui_DropdownCreateMenuChoose;
lv_obj_t * ui_PanelCreateMenuButton;
lv_obj_t * ui_BTNCreateMenu;
void ui_event_BTNCreateMenuTop(lv_event_t * e);
lv_obj_t * ui_BTNCreateMenuTop;
lv_obj_t * ui_ImageBTNCreateMenu;
lv_obj_t * ui_ArcTemperatureShow3;
void ui_event_SliderCreateMenuTargetTemp(lv_event_t * e);
lv_obj_t * ui_SliderCreateMenuTargetTemp;
lv_obj_t * ui_MenuOptionRoller3;
lv_obj_t * ui_LabelSensorTemperature9;
lv_obj_t * ui_LabelCreateMenuTargetTemperature;
lv_obj_t * ui_ArcTemperatureShow4;
void ui_event_SliderCreateMenuTargetCountdown(lv_event_t * e);
lv_obj_t * ui_SliderCreateMenuTargetCountdown;
lv_obj_t * ui_LabelCreateMenuCountdownText;
lv_obj_t * ui_LabelCreateMenuCountdown;

// SCREEN: ui_ScreenMenuConfigDeleteMenu
void ui_ScreenMenuConfigDeleteMenu_screen_init(void);
lv_obj_t * ui_ScreenMenuConfigDeleteMenu;
lv_obj_t * ui_Background4;
void ui_event_BTNAutoMenuPrint5(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuPrint5;
void ui_event_BTNAutoMenuMove5(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuMove5;
lv_obj_t * ui_BTNAutoMenuSetting5;
lv_obj_t * ui_Panel_Header4;
lv_obj_t * ui_Label_Header4;
lv_obj_t * ui_ScreenMenuConfigDelMenu;
lv_obj_t * ui_PanelRollerDeleteMenuChoose;
lv_obj_t * ui_IMGRollerDeleteMenuChoose;
void ui_event_RollerDeleteMenuChoose(lv_event_t * e);
lv_obj_t * ui_RollerDeleteMenuChoose;
lv_obj_t * ui_PanelRollerDeleteMenuChooseBTN;
lv_obj_t * ui_BTNDeleteMenuChoose;
void ui_event_BTNDeleteMenuChooseTop(lv_event_t * e);
lv_obj_t * ui_BTNDeleteMenuChooseTop;
lv_obj_t * ui_ImageBTNDeleteMenuChoose;

// SCREEN: ui_ScreenMenuConfigEditMenuSelect
void ui_ScreenMenuConfigEditMenuSelect_screen_init(void);
lv_obj_t * ui_ScreenMenuConfigEditMenuSelect;
lv_obj_t * ui_Background6;
void ui_event_BTNAutoMenuPrint7(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuPrint7;
void ui_event_BTNAutoMenuMove7(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuMove7;
lv_obj_t * ui_BTNAutoMenuSetting7;
lv_obj_t * ui_Panel_Header6;
lv_obj_t * ui_Label_Header6;
lv_obj_t * ui_ScreenMenuConfigDelMenu1;
lv_obj_t * ui_DropdownEditMenuChoose;
lv_obj_t * ui_PanelRollerDeleteMenuChooseBTN1;
lv_obj_t * ui_BTNDeleteMenuChoose1;
void ui_event_BTNDeleteMenuChooseTop1(lv_event_t * e);
lv_obj_t * ui_BTNDeleteMenuChooseTop1;
lv_obj_t * ui_ImageBTNDeleteMenuChoose1;

// SCREEN: ui_ScreenMenuConfigEditMenu
void ui_ScreenMenuConfigEditMenu_screen_init(void);
lv_obj_t * ui_ScreenMenuConfigEditMenu;
lv_obj_t * ui_Background5;
void ui_event_BTNAutoMenuPrint6(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuPrint6;
void ui_event_BTNAutoMenuMove6(lv_event_t * e);
lv_obj_t * ui_BTNAutoMenuMove6;
lv_obj_t * ui_BTNAutoMenuSetting6;
lv_obj_t * ui_Panel_Header5;
lv_obj_t * ui_Label_Header5;
lv_obj_t * ui_ScreenAutoContentPanel3;
lv_obj_t * ui_PanelRollerEditMenuChoose;
lv_obj_t * ui_LabelEditMenuText;
lv_obj_t * ui_PanelEditMenuButton;
lv_obj_t * ui_BTNEditMenu;
void ui_event_BTNEditMenuTop(lv_event_t * e);
lv_obj_t * ui_BTNEditMenuTop;
lv_obj_t * ui_ImageBTNEditMenu;
lv_obj_t * ui_ArcTemperatureShow5;
void ui_event_SliderEditMenuTargetTemp(lv_event_t * e);
lv_obj_t * ui_SliderEditMenuTargetTemp;
lv_obj_t * ui_MenuOptionRoller4;
lv_obj_t * ui_LabelSensorTemperature6;
lv_obj_t * ui_LabelEditMenuTargetTemperature;
lv_obj_t * ui_PanelEditMenuCountdown;
void ui_event_SliderEditMenuTargetCountdown(lv_event_t * e);
lv_obj_t * ui_SliderEditMenuTargetCountdown;
lv_obj_t * ui_LabelEditMenuCountdownText;
lv_obj_t * ui_LabelEditMenuCountdown;

// SCREEN: ui_ScreenScreenSaverMenu
void ui_ScreenScreenSaverMenu_screen_init(void);
lv_obj_t * ui_ScreenScreenSaverMenu;
void ui_event_PanelMenu(lv_event_t * e);
lv_obj_t * ui_PanelMenu;
lv_obj_t * ui_LabelMenuName;
lv_obj_t * ui_LabelPressAnywhereToExit;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_ScreenSaverLeftPanel;
lv_obj_t * ui_LabelScreenSaverCookingState;
lv_obj_t * ui_ScreenSaverRightPanel;
lv_obj_t * ui_LabelScreenSaverCookingCountdown;
lv_obj_t * ui_Splitter2;

// SCREEN: ui_ScreenDropFood
void ui_ScreenDropFood_screen_init(void);
lv_obj_t * ui_ScreenDropFood;
lv_obj_t * ui_PanelMenu1;
lv_obj_t * ui_LabelDropFood;
lv_obj_t * ui_LabelDropFoodReminder;
void ui_event_ButtonDropFoodDone(lv_event_t * e);
lv_obj_t * ui_ButtonDropFoodDone;
lv_obj_t * ui_LabelDropFoodDone;
lv_obj_t * ui_LabelDropFoodDoneSeconds;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_icn_time_[2] = {&ui_img_icn_time_1_png, &ui_img_icn_time_2_png};
const lv_img_dsc_t * ui_imgset_1976485245[1] = {&ui_img_984416508};
const lv_img_dsc_t * ui_imgset_99520626[1] = {&ui_img_526273827};
const lv_img_dsc_t * ui_imgset_312482397[6] = {&ui_img_1244952608, &ui_img_987395607, &ui_img_1405798654, &ui_img_772459689, &ui_img_565988525, &ui_img_821558544};
const lv_img_dsc_t * ui_imgset_1704232224[1] = {&ui_img_1519923167};
const lv_img_dsc_t * ui_imgset_692459370[1] = {&ui_img_572867443};
const lv_img_dsc_t * ui_imgset_336342142[3] = {&ui_img_1688661777, &ui_img_1946231078, &ui_img_839169762};
const lv_img_dsc_t * ui_imgset_475981303[1] = {&ui_img_1158544786};
const lv_img_dsc_t * ui_imgset_313891012[4] = {&ui_img_552494413, &ui_img_1392977354, &ui_img_2094120521, &ui_img_2126067643};
const lv_img_dsc_t * ui_imgset_801595910[4] = {&ui_img_1627854363, &ui_img_1329794544, &ui_img_614800514, &ui_img_1722068059};
const lv_img_dsc_t * ui_imgset_1754692625[1] = {&ui_img_1443512802};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void OpaOn_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 10);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void OpaOff_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 200);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 255, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void ScreenIn_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 300);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_start(&PropertyAnimation_0);

}
void MenuIn_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_start(&PropertyAnimation_0);

}
void MenuOut_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 150);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 255, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void ScreenOut_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 200);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 255, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_BTNAutoMenuMove1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenAuto, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenAuto_screen_init);
    }
}
void ui_event_BTNAutoMenuSetting1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenSetting, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenSetting_screen_init);
    }
}
void ui_event_BTNStartMenuTop1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        MenuStartCookingButtonManual(e);
    }
}
void ui_event_SliderManualTargetTemperature(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        ManualSetTargetTemperature(e);
    }
}
void ui_event_BarManualTemperature1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        ManualSetCountdownTime(e);
    }
}
void ui_event_DropdownMotorLeftRightManual(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        CallDropdownMotorLeftRightManual(e);
    }
}
void ui_event_BTNAutoMenuPrint(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenManual, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenManual_screen_init);
    }
}
void ui_event_BTNAutoMenuSetting(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenSetting, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenSetting_screen_init);
    }
}
void ui_event_BTNStartMenuTop(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        MenuStartCookingButtonAuto(e);
    }
}
void ui_event_MenuOptionRollerChoose(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        Roller_Option_Menu_Change(e);
    }
}
void ui_event_DropdownMotorLeftRightAuto(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        CallDropdownMotorLeftRightAuto(e);
    }
}
void ui_event_BTNAutoMenuPrint2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenManual, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenManual_screen_init);
    }
}
void ui_event_BTNAutoMenuMove2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenAuto, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenAuto_screen_init);
    }
}
void ui_event_Roller2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        Change_Language_From_Settings(e);
    }
}
void ui_event_BTN_Heat_Head(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenMenuConfiguration, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0,
                          &ui_ScreenMenuConfiguration_screen_init);
        _ui_state_modify(ui_BTN_Heat_Head, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
    }
}
void ui_event_Slider_Print_Speed(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        _ui_slider_set_text_value(ui_Label_Print_Speed_Number, target, "", " K");
        TemperatureCalibrationSlider(e);
    }
}
void ui_event_Switch_Light(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        Temperature_Unit_Change(e);
    }
}
void ui_event_Switch_Demo_Mode(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        DemoModeOnOFF(e);
    }
}
void ui_event_Switch_Calibration_Temperature(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED)
    {
        TemperatureCalibrationOnOFF(e);
    }
}
void ui_event_BTNAutoMenuPrint3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenManual, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenManual_screen_init);
    }
}
void ui_event_BTNAutoMenuMove3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenAuto, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenAuto_screen_init);
    }
}
void ui_event_AddMenuToJSON(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenMenuConfigCreateMenu, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0,
                          &ui_ScreenMenuConfigCreateMenu_screen_init);
    }
}
void ui_event_EditMenuToJSON(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenMenuConfigEditMenuSelect, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0,
                          &ui_ScreenMenuConfigEditMenuSelect_screen_init);
    }
}
void ui_event_DeleteMenuToJSON(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenMenuConfigDeleteMenu, LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0,
                          &ui_ScreenMenuConfigDeleteMenu_screen_init);
    }
}
void ui_event_BTNAutoMenuPrint4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenManual, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenManual_screen_init);
    }
}
void ui_event_BTNAutoMenuMove4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenAuto, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenAuto_screen_init);
    }
}
void ui_event_BTNCreateMenuTop(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenMenuConfiguration, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0,
                          &ui_ScreenMenuConfiguration_screen_init);
        CreateNewMenu(e);
    }
}
void ui_event_SliderCreateMenuTargetTemp(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        CreateMenuChangeTemperature(e);
    }
}
void ui_event_SliderCreateMenuTargetCountdown(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        CreateMenuSetCountdownTime(e);
    }
}
void ui_event_BTNAutoMenuPrint5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenManual, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenManual_screen_init);
    }
}
void ui_event_BTNAutoMenuMove5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenAuto, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenAuto_screen_init);
    }
}
void ui_event_RollerDeleteMenuChoose(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        Roller_Option_Menu_Change(e);
    }
}
void ui_event_BTNDeleteMenuChooseTop(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenMenuConfiguration, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0,
                          &ui_ScreenMenuConfiguration_screen_init);
        DeleteCurrentMenu(e);
    }
}
void ui_event_BTNAutoMenuPrint7(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenManual, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenManual_screen_init);
    }
}
void ui_event_BTNAutoMenuMove7(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenAuto, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenAuto_screen_init);
    }
}
void ui_event_BTNDeleteMenuChooseTop1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenMenuConfigEditMenu, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0,
                          &ui_ScreenMenuConfigEditMenu_screen_init);
        EditCurrentMenuSelect(e);
    }
}
void ui_event_BTNAutoMenuPrint6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenManual, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenManual_screen_init);
    }
}
void ui_event_BTNAutoMenuMove6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenAuto, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenAuto_screen_init);
    }
}
void ui_event_BTNEditMenuTop(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenMenuConfiguration, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0,
                          &ui_ScreenMenuConfiguration_screen_init);
        EditCurrentMenu(e);
    }
}
void ui_event_SliderEditMenuTargetTemp(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        EditMenuTargetTemperatureSlider(e);
    }
}
void ui_event_SliderEditMenuTargetCountdown(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        EditSetCountdownTime(e);
    }
}
void ui_event_PanelMenu(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        Screensaver_Menu_Event(e);
    }
}
void ui_event_ButtonDropFoodDone(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        DropFoodReminderDone(e);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_ScreenManual_screen_init();
    ui_ScreenAuto_screen_init();
    ui_ScreenSetting_screen_init();
    ui_ScreenMenuConfiguration_screen_init();
    ui_ScreenMenuConfigCreateMenu_screen_init();
    ui_ScreenMenuConfigDeleteMenu_screen_init();
    ui_ScreenMenuConfigEditMenuSelect_screen_init();
    ui_ScreenMenuConfigEditMenu_screen_init();
    ui_ScreenScreenSaverMenu_screen_init();
    ui_ScreenDropFood_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_ScreenManual);
}
