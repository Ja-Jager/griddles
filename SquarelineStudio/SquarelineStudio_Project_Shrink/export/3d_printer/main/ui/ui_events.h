// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.3
// Project name: 3d_printer

#ifndef _UI_EVENTS_H
#define _UI_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

void MenuStartCookingButtonManual(lv_event_t * e);
void ManualSetTargetTemperature(lv_event_t * e);
void ManualSetCountdownTime(lv_event_t * e);
void MenuStartCookingButtonAuto(lv_event_t * e);
void Roller_Option_Menu_Change(lv_event_t * e);
void Change_Language_From_Settings(lv_event_t * e);
void Temperature_Unit_Change(lv_event_t * e);
void DemoModeOnOFF(lv_event_t * e);
void CreateNewMenu(lv_event_t * e);
void CreateMenuChangeTemperature(lv_event_t * e);
void CreateMenuSetCountdownTime(lv_event_t * e);
void Roller_Option_Menu_Change(lv_event_t * e);
void DeleteCurrentMenu(lv_event_t * e);
void EditCurrentMenuSelect(lv_event_t * e);
void EditCurrentMenu(lv_event_t * e);
void EditMenuTargetTemperatureSlider(lv_event_t * e);
void EditSetCountdownTime(lv_event_t * e);
void Screensaver_Menu_Event(lv_event_t * e);
void DropFoodReminderDone(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif