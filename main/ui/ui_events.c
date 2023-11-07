// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: 3d_printer

// LVGL
#include "ui.h"
#include "stdio.h"
#include "Count_zero.h"
#include "manual_mode.h"
#include "encoder.h"
#include "menu.h"
#include "PID.h"
#include "math.h"
#include "ui_events.h"
#include "string.h"
#include "nvs_component.h"
#include "esp_log.h"

QueueHandle_t handle_queue_locate_language;

#define Manual_countdown_interval 10

#define Temperature_Fahrenheit_Upper 464
#define Temperature_Fahrenheit_Lower 212

#define Temperature_Celsius_Upper 240
#define Temperature_Celsius_Lower 100

#define Temperature_Unit_Fahrenheit 1
#define Temperature_Unit_Celsius 0

// 温度单位
bool temperature_unit = Temperature_Unit_Fahrenheit;

lv_obj_t * mbox_preheating = NULL;
// lv_obj_t * mbox_cooling;

const char * btns_preheating[] = {"Discontinue", "Continue", ""};
// const char * btns_cooling[] = {"Stop", "Quit Cooling", ""};

void ui_event_init(void)
{
	// refresh_lv_i18n_label_text();

	// handle_queue_locate_language = xQueueCreate(1, sizeof(char *));
	// xQueueOverwrite(handle_queue_locate_language, &current_locate_language);
}

char *Locate_Language_read(void)
{
	char *current_locate_language = 0;
    xQueuePeek(handle_queue_locate_language, &current_locate_language, 0);
    return current_locate_language;
}

void Locate_Language_write(char *current_locate_language)
{
	xQueueOverwrite(handle_queue_locate_language, &current_locate_language);
}

// 手动模式
// 手动模式开始按键触发
void MenuStartCookingButtonManual(lv_event_t *e)
{
	// Your code here
	if(manual_mode_start_mailbox_write() == mode_manual)
	{
		lv_obj_whether_ban_animation(ui_BarManualTemperature1, 1);
	}
	else
	{
		lv_obj_whether_ban_animation(ui_BarManualTemperature1, 0);
	}
}

//手动模式设定温度滑条变化触发
void ManualSetTargetTemperature(lv_event_t * e)
{
	// Your code here
	lv_obj_t *manual_temperature_slider = lv_event_get_target(e);
	int32_t manual_target_temperature = lv_slider_get_value(manual_temperature_slider);
	Encoder_temperature_queue_write(manual_target_temperature);
	if(temperature_unit == Temperature_Unit_Fahrenheit)
	{
		lv_label_set_text_fmt(ui_LabelManualTargetTemperature, "%ld°F", manual_target_temperature);
	}
	else
	{
		lv_label_set_text_fmt(ui_LabelManualTargetTemperature, "%ld°C", manual_target_temperature);
	}

	lv_slider_set_value(ui_SliderManualTargetTemperature, manual_target_temperature, LV_ANIM_ON);
}

//手动模式设定时间滑条变化触发
void ManualSetCountdownTime(lv_event_t *e)
{
	// Your code here
	lv_obj_t *manual_countdown_slider = lv_event_get_target(e);
	int manual_countdown_time = (int)lv_slider_get_value(manual_countdown_slider) * Manual_countdown_interval;
	manual_countdown_time_write(manual_countdown_time);
	// char *current_Locate_Language = Locate_Language_read();

	// Change 设定倒计时的值
	if(manual_countdown_time == 0)
	{
		lv_label_set_text_fmt(ui_LabelManualTimerSet, "%s", _("Continuous Heat"));
	}
	else
	{
		lv_label_set_text_fmt(ui_LabelManualTimerSet, _("%d:%d"), manual_countdown_time / 60, manual_countdown_time % 60);
	}
}

// 自动模式
// 自动模式开始按键触发
void MenuStartCookingButtonAuto(lv_event_t *e)
{
	// Your code here
	if(timer_start_button_event() == mode_timer)
	{
		force_heat_countdown_queue_write(menu_search_by_sequence(lv_roller_get_selected(ui_MenuOptionRollerChoose)).menu_force_heat_time);
		// lv_obj_whether_ban_animation(ui_MenuOptionRollerChoose, 1);
	}
	else
	{
		// lv_obj_whether_ban_animation(ui_MenuOptionRollerChoose, 0);
	}
}

// 自动模式滚轮滚动触发
void Roller_Option_Menu_Change(lv_event_t *e)
{
	// Your code here
	enum mode_select_state current_PID_mode = PID_mode_read();
	enum timer_countdown_state current_countdown_state = read_countdown_start();

	lv_obj_t *roller = lv_event_get_target(e);
	char buf[32];

	lv_roller_get_selected_str(roller, buf, sizeof(buf));
	food_menu_item_config temporary_menu = menu_search_by_name(buf);
	// char *name = ;


	if ((current_PID_mode == mode_null) || (current_PID_mode == mode_manual))
	// if(current_countdown_state == Timer_Countdown_Stop)
	{
		//自动操作的温度显示和bar位置
		if(temperature_unit == Temperature_Unit_Fahrenheit)
		{
			lv_label_set_text_fmt(ui_LabelTargetTemperatureValue, "%d°F", (int32_t)(round((temporary_menu.target_temperature - 273.15) * 1.80 + 32.00)));	// 显示自动操作设定温度
			lv_bar_set_value(ui_BarCountDownTemperature, (int32_t)(round((temporary_menu.target_temperature - 273.15) * 1.80 + 32.00)), LV_ANIM_ON);	// Menu Target Temperature Bar
		}
		else
		{
			lv_label_set_text_fmt(ui_LabelTargetTemperatureValue, "%d°C", (int32_t)(round(temporary_menu.target_temperature - 273.15)));	// 显示自动操作设定温度
			lv_bar_set_value(ui_BarCountDownTemperature, (int32_t)(round(temporary_menu.target_temperature - 273.15)), LV_ANIM_ON);	// Menu Target Temperature Bar
		}
												
		//自动操作的倒计时显示
		lv_label_set_text_fmt(ui_LabelSetTimeValue, _("%d:%d"), temporary_menu.cooking_timer_seconds / 60, temporary_menu.cooking_timer_seconds % 60); // 显示自动操作设定时间
													
		//自动操作的设置界面的强制加热显示及文本显示
		lv_slider_set_value(ui_Slider_Print_Speed, temporary_menu.menu_force_heat_time, LV_ANIM_OFF);
		lv_label_set_text_fmt(ui_Label_Print_Speed_Number, "%d C°", temporary_menu.menu_force_heat_time);

		force_heat_countdown_queue_write(temporary_menu.menu_force_heat_time);
		count_zero_second_queue_write(temporary_menu.cooking_timer_seconds);																		// 发送自动操作总时长
		countdown_temperature_write_for_ui_events(temporary_menu.target_temperature);
		// PID_set_temperature_write((float)temporary_menu.target_temperature); //发送自动操作设定温度给PID
	}
	if (current_countdown_state == Timer_Countdown_Start)
	{
		// PID_set_temperature_write((float)temporary_menu.target_temperature); // 发送自动操作设定温度给PID
	}
}

// User Preference

// 温度单位切换按键触发
void Temperature_Unit_Change(lv_event_t *e)
{
	// 获取 Unit Switch 状态
	temperature_unit = Temperature_Unit_Fahrenheit;
	lv_obj_t * Temperature_Unit_Switch = lv_event_get_target(e);
	// True being on (Fahrenheit), False being off (Celsius)
	bool Temperature_Unit_State = lv_obj_has_state(Temperature_Unit_Switch, LV_STATE_CHECKED);
	temperature_unit = Temperature_Unit_State;

	// Your code here
	int32_t lower_limit = Temperature_Fahrenheit_Lower; 
	int32_t upper_limit = Temperature_Fahrenheit_Upper;

	//读取自动操作设定温度
	char buf[25];
	lv_roller_get_selected_str(ui_MenuOptionRollerChoose, buf, sizeof(buf));
	food_menu_item_config temporary_menu = menu_search_by_name(buf);

	//读取手动操作设定温度
	long manual_target_temperature = (long)lv_slider_get_value(ui_SliderManualTargetTemperature);

	//读取新增菜单设定温度
	long create_menu_target_temperature = (long)lv_slider_get_value(ui_SliderCreateMenuTargetTemp);
	// printf("create_menu_target_temperature:\n%d\n", create_menu_target_temperature);
	
	//读取修改菜单设定温度
	lv_dropdown_get_selected_str(ui_DropdownEditMenuChoose, buf, sizeof(buf));
	food_menu_item_config temporary_edit_menu = menu_search_by_name(buf);

	if(temperature_unit == Temperature_Unit_Celsius) //摄氏度处理
	{
		//设置摄氏度温度范围
		lower_limit = Temperature_Celsius_Lower;
		upper_limit = Temperature_Celsius_Upper;

		//自动操作设定温度立刻显示
		lv_label_set_text_fmt(ui_LabelTargetTemperatureValue, "%d°C", (int32_t)(round)(temporary_menu.target_temperature - 273.15));	// 显示自动操作设定温度
		
		//手动操作设定温度立刻显示
		Encoder_temperature_queue_write(round((manual_target_temperature -32)/1.8));

		int32_t current_manual_target_temperature = (int32_t)(round)((manual_target_temperature -32)/1.8);
		// printf("current_manual_target_temperature:\n%ld°C\n", current_manual_target_temperature);
		lv_label_set_text_fmt(ui_LabelManualTargetTemperature, "%ld°C", current_manual_target_temperature);

		//新增菜单设定温度立刻显示
		lv_label_set_text_fmt(ui_LabelCreateMenuTargetTemperature, "%d°C", (int32_t)(round)((create_menu_target_temperature -32)/1.8));
		// printf("ui_LabelManualTargetTemperature:\n%d\n", (int32_t)((manual_target_temperature -32)/1.8));
		
		//修改菜单设定温度立刻显示
		lv_label_set_text_fmt(ui_LabelEditMenuTargetTemperature, "%d°C", (int32_t)(round)(temporary_edit_menu.target_temperature - 273.15));	// 显示自动操作设定温度
	}
	else if (temperature_unit == Temperature_Unit_Fahrenheit) //华氏度处理
	{
		//设置华氏度温度范围
		lower_limit = Temperature_Fahrenheit_Lower;
		upper_limit = Temperature_Fahrenheit_Upper;

		//自动操作设定温度立刻显示
		lv_label_set_text_fmt(ui_LabelTargetTemperatureValue, "%d°F", (int32_t)(round)((temporary_menu.target_temperature - 273.15) * 1.80 + 32.00));	// 显示自动操作设定温度
		
		//手动操作设定温度立刻显示
		Encoder_temperature_queue_write(round((manual_target_temperature * 1.8) + 32));
		lv_label_set_text_fmt(ui_LabelManualTargetTemperature, "%d°F", (int32_t)(round)((manual_target_temperature * 1.8) + 32));

		//新增菜单设定温度立刻显示
		lv_label_set_text_fmt(ui_LabelCreateMenuTargetTemperature, "%d°F", (int32_t)(round)((create_menu_target_temperature * 1.8) + 32));
		// printf("ui_LabelManualTargetTemperature:\n%d\n", (int32_t)((manual_target_temperature * 1.8) + 32));

		//修改菜单设定温度立刻显示
		lv_label_set_text_fmt(ui_LabelEditMenuTargetTemperature, "%d°F", (int32_t)(round)((temporary_edit_menu.target_temperature - 273.15) * 1.80 + 32.00));
	}
	
	//注意：示数可以放在设定范围之前，但滑条只能放在设定范围之后
	// 操作界面
	lv_slider_set_range(ui_SliderManualTargetTemperature, lower_limit, upper_limit); // 手动模式设定范围
	lv_bar_set_range(ui_BarCountDownTemperature, lower_limit, upper_limit); // 倒计时模式设定范围
	// 设定界面
	lv_slider_set_range(ui_SliderCreateMenuTargetTemp, lower_limit, upper_limit); // 新增菜单设定范围
	lv_slider_set_range(ui_SliderEditMenuTargetTemp, lower_limit, upper_limit); //修改菜单设定范围

	if(temperature_unit == Temperature_Unit_Celsius) //设定范围后，slider和bar的立刻定位
	{
		//自动操作倒计时bar立刻定位
		lv_bar_set_value(ui_BarCountDownTemperature, (int32_t)(round)(temporary_menu.target_temperature - 273.15), LV_ANIM_ON);	// Menu Target Temperature Bar
		//新增菜单设定温度滑条立刻定位
		lv_slider_set_value(ui_SliderCreateMenuTargetTemp, (int32_t)(round)((create_menu_target_temperature -32)/1.8), LV_ANIM_ON);
		//修改菜单设定温度滑条立刻定位
		lv_slider_set_value(ui_SliderEditMenuTargetTemp, (int32_t)(round)(temporary_edit_menu.target_temperature - 273.15), LV_ANIM_ON);
	}
	else if (temperature_unit == Temperature_Unit_Fahrenheit)
	{
		//自动操作倒计时bar立刻定位
		lv_bar_set_value(ui_BarCountDownTemperature, (int32_t)(round)((temporary_menu.target_temperature - 273.15) * 1.80 + 32.00), LV_ANIM_ON);	// Menu Target Temperature Bar
		//新增菜单设定温度滑条立刻定位
		lv_slider_set_value(ui_SliderCreateMenuTargetTemp, (int32_t)(round)((create_menu_target_temperature * 1.8) + 32), LV_ANIM_ON);
		//修改菜单设定温度滑条立刻定位
		lv_slider_set_value(ui_SliderEditMenuTargetTemp, (int32_t)(round)((temporary_edit_menu.target_temperature - 273.15) * 1.80 + 32.00), LV_ANIM_ON);
	}
}

// 演示模式按键触发
void DemoModeOnOFF(lv_event_t * e)
{

	// Your code here
	// enum use_state current_use_state = demo_mode;
	// lv_obj_t * demo_mode_switch = lv_event_get_target(e);
	// bool demo_mode_on = lv_obj_has_state(demo_mode_switch, LV_STATE_CHECKED); // with `true` being on
	// if(demo_mode_on)
	// {
	// 	current_use_state = demo_mode;
	// 	// use_state_write(current_use_state);
	// 	// 更改 enum 为 demo_mode
	// }
	// else
	// {
	// 	current_use_state = production_mode;
	// 	// use_state_write(current_use_state);
	// 	// 更改 enum 为 production_mode
	// }
}

void Change_Language_From_Settings(lv_event_t * e)
{
    // Extract the roller's selected language text, such as "繁中", "简中", "English"
    char locale_name[32];
    lv_roller_get_selected_str(ui_Roller2, locale_name, sizeof(locale_name));
	ESP_LOGE("lv_i18n","locale_name is %s", locale_name);

    // Map the roller's language text to ISO locale name
    const char* locale = NULL;
    if (strcmp(locale_name, "繁體中文") == 0) {
        locale = "zh-hk";
    } else if (strcmp(locale_name, "简体中文") == 0) {
        locale = "zh-cn";
    } else if (strcmp(locale_name, "English") == 0) {
        locale = "en";
    }
    else if (strcmp(locale_name, "Español") == 0) {
        locale = "es";
    }
    else if (strcmp(locale_name, "Français") == 0) {
        locale = "fr";
    }
	else if (strcmp(locale_name, "Indonesian") == 0) {
        locale = "id";
    }
	ESP_LOGE("lv_i18n","Matched locale is %s", locale);
    /**
     * @note The ISO locale names correspond to different languages and regions.
     *       For example, "en" stands for English, "zh-cn" stands for Chinese (China),
     *       "zh-hk" stands for Chinese (Hong Kong), and "es" stands for Spanish.
     *       For a detailed mapping, please refer to: https://www.andiamo.co.uk/resources/iso-language-codes/
     */

    if (locale != NULL) {
        // Set the active locale using lv_i18n API
		int result = lv_i18n_set_locale(locale);
		if (result == 0) {
			ESP_LOGI("lv_i18n", "Set locale success");
		} else {
			ESP_LOGE("lv_i18n", "Set locale failed");
		}
		refresh_lv_i18n_label_text();
		nvs_write_str("locale_name", locale);

		// Locate_Language_write(locale);
		if(lv_slider_get_value(ui_BarManualTemperature1) == 0)
		{
			lv_label_set_text_fmt(ui_LabelManualTimerSet, "%s", _("Continuous Heat"));
		}
        ESP_LOGE("lv_i18n", "All LVGL internationalized label text successfully refreshed.");
    }
}

void refresh_lv_i18n_label_text(void)
{
    // lv_label_set_text(ui_LabelAutoHeader, _("Scroll to choose menu, Press to Start"));
    lv_label_set_text(ui_LabelSensorTemperature, _("Temp"));
    lv_label_set_text(ui_LabelSetTime, _("Countdown"));
    lv_label_set_text(ui_LabelSetTimeValue, _("Heat"));
	lv_label_set_text(ui_LabelSensorTempValue2, _("Heat"));
    lv_label_set_text(ui_LabelSensorTemperature2, _("Set Temp"));
    lv_label_set_text(ui_LabelAutoHeader1, _("Press to Start"));
    lv_label_set_text(ui_LabelSensorTemperature4, _("Temp"));
    lv_label_set_text(ui_LabelSensorTemperature5, _("Countdown"));
    lv_label_set_text(ui_LabelSensorTemperature3, _("Set Temp"));
    lv_label_set_text(ui_LabelSensorTemperature1, _("Set Countdown"));
    lv_label_set_text(ui_Label_Header3, _("User Menu: Create"));
    lv_label_set_text(ui_LabelCreateMenuText, _("Choose Menu"));
    lv_label_set_text(ui_LabelSensorTemperature9, _("Set Temp"));
    lv_label_set_text(ui_LabelCreateMenuCountdownText, _("Set Countdown"));
    lv_label_set_text(ui_Label_Header4, _("User Menu: Delete"));
    lv_label_set_text(ui_Label_Header5, _("User Menu: Edit | Spec"));
    lv_label_set_text(ui_LabelSensorTemperature6, _("Set Temp"));
    lv_label_set_text(ui_LabelEditMenuCountdownText, _("Set Countdown"));
    lv_label_set_text(ui_Label_Header6, _("User Menu: Edit | Select menu"));
    lv_label_set_text(ui_Label_Header1, _("User Menu: Create | Edit | Delete"));
    lv_label_set_text(ui_LabelNewMenu, _("Create\nMenu"));
    lv_label_set_text(ui_LabelEditMenu, _("Edit\nMenu"));
    lv_label_set_text(ui_LabelDeleteMenu, _("Delete\nMenu"));
    lv_label_set_text(ui_Label_Header2, _("Settings"));
    lv_label_set_text(ui_Label_Material, _("Self Clean (min)"));
    lv_label_set_text(ui_Label_Bed_Temp1, _("Power Mode"));
    lv_label_set_text(ui_Label_Head_Temp1, _("Language"));
    lv_label_set_text(ui_Label_Reset22, _("Menu"));
    lv_label_set_text(ui_Label_Heat_Bed, _("About"));
    lv_label_set_text(ui_Label_Remove_Filament, _("Reset"));
    lv_label_set_text(ui_Label_Print_Speed, _("Temperature Calibration"));
    lv_label_set_text(ui_Label_Light, _("Unit"));
    lv_label_set_text(ui_Label_Demo_Mode, _("Demo Mode"));
    lv_label_set_text(ui_Label_Fan_2, _("Hi Limit Cut-OFF"));
    lv_label_set_text(ui_Label_Fan_3, _("Touch Screen"));
	// lv_label_set_text(ui_LabelDropFoodReminder, _("Manual Operation"));
	// lv_label_set_text(ui_LabelDropFood, _("Drop Food"));
	// lv_label_set_text(ui_LabelPressAnywhereToExit, _("Press anywhere or any button to exit"));
}

// Menu Config: Create, Edit, Delete

//新增菜单键
void CreateNewMenu(lv_event_t *e)
{
	// Your code here
	/* 提取menu_config_json_str菜单名 */
	cJSON *menu_config_json;
	menu_config_json = cJSON_Parse(menu_config_json_str_return());

	cJSON *food_menu = cJSON_GetObjectItemCaseSensitive(menu_config_json, "food_menu");
	int array_size = cJSON_GetArraySize(food_menu);

	char menu_roller_new_option_name[500] = "";
	for (int i = 0; i < array_size; i++) {
		cJSON *food = cJSON_GetArrayItem(food_menu, i);       
		cJSON *food_name = cJSON_GetObjectItemCaseSensitive(food, "name");
		if(i == 0)
		{
			strcpy(menu_roller_new_option_name, food_name->valuestring);
		}
		else
		{
			strcat(menu_roller_new_option_name, "\n");
			strcat(menu_roller_new_option_name, food_name->valuestring);
		}
	}
	printf("menu_roller_new_option_name:\n%s\n", menu_roller_new_option_name);
	cJSON_Delete(menu_config_json);
	
	/* 提取dropdown菜单 */
	food_menu_item_config menu_new_create;
	if(temperature_unit == Temperature_Unit_Fahrenheit)
	{
		menu_new_create.target_temperature = (double)((lv_slider_get_value(ui_SliderCreateMenuTargetTemp) - 32.00) / 1.800 + 273.15);
	}
	else
	{
		menu_new_create.target_temperature = (double)(lv_slider_get_value(ui_SliderCreateMenuTargetTemp) + 273.15);
	}
	menu_new_create.cooking_timer_seconds = lv_slider_get_value(ui_SliderCreateMenuTargetCountdown) * Manual_countdown_interval;
	menu_new_create.menu_force_heat_time = lv_slider_get_value(ui_Slider_Print_Speed);
	menu_new_create.target_temperature_unit = "fahrenheit";
	if(temperature_unit == Temperature_Unit_Fahrenheit)
	{
		printf("temperature:\n%f°F\ncountdown:\n%d\ntemperature unit:\n%s\n", menu_new_create.target_temperature, menu_new_create.cooking_timer_seconds, menu_new_create.target_temperature_unit);
	}
	else
	{
		printf("temperature:\n%f°C\ncountdown:\n%d\ntemperature unit:\n%s\n", menu_new_create.target_temperature, menu_new_create.cooking_timer_seconds, menu_new_create.target_temperature_unit);
	}
	
	char menu_create_dropdown_new_option[16] = "";
	lv_dropdown_get_selected_str(ui_DropdownCreateMenuChoose, &menu_create_dropdown_new_option, 16);
	menu_new_create.menu_name = menu_create_dropdown_new_option;
	printf("name:\n%s\n", menu_create_dropdown_new_option);

	create_menu(menu_new_create);
	printf("create new menu: \n%s\n", menu_config_json_str_return());

	/* 添加菜单名入滚轮 */
	strcat(menu_roller_new_option_name, "\n");
	strcat(menu_roller_new_option_name, menu_create_dropdown_new_option);
	lv_roller_set_options(ui_MenuOptionRollerChoose, menu_roller_new_option_name, LV_ROLLER_MODE_NORMAL); //自动操作菜单列表
	lv_roller_set_options(ui_RollerDeleteMenuChoose, menu_roller_new_option_name, LV_ROLLER_MODE_NORMAL); //删除操作菜单列表
	lv_dropdown_set_options(ui_DropdownEditMenuChoose, menu_roller_new_option_name);
}

//新建菜单温度滑条
void CreateMenuChangeTemperature(lv_event_t * e)
{
	lv_obj_t *create_menu_temperature_slider = lv_event_get_target(e);
	int32_t create_menu_temperature = lv_slider_get_value(create_menu_temperature_slider);

	if(temperature_unit == Temperature_Unit_Fahrenheit)
	{
		// printf("create menu slider value(Fahrenheit):\n%d°F\n", create_menu_temperature);
		// printf("create menu slider value(Kelvin):\n%.2fK\n", ((create_menu_temperature - 32.00) / 1.800 + 273.15));
		lv_label_set_text_fmt(ui_LabelCreateMenuTargetTemperature, "%d°F", create_menu_temperature);
	}
	else
	{
		// printf("create menu slider value(Celsius):\n%d°C\n", create_menu_temperature);
		// printf("create menu slider value(Kelvin):\n%.2fK\n", (create_menu_temperature + 273.15));
		lv_label_set_text_fmt(ui_LabelCreateMenuTargetTemperature, "%d°C", create_menu_temperature);
	}

	lv_slider_set_value(ui_SliderCreateMenuTargetTemp, create_menu_temperature, LV_ANIM_ON);
}

//新建菜单倒计时滑条
void CreateMenuSetCountdownTime(lv_event_t * e)
{
	// Your code here
	lv_obj_t *create_menu_countdown_slider = lv_event_get_target(e);
	int32_t create_menu_countdown = lv_slider_get_value(create_menu_countdown_slider) * Manual_countdown_interval;

	lv_label_set_text_fmt(ui_LabelCreateMenuCountdown, "%d:%d", create_menu_countdown / 60, create_menu_countdown % 60);
}

// 删除菜单按键
void DeleteCurrentMenu(lv_event_t * e)
{
	// Your code here
	/* 提取roller菜单名 */
	char buf[32];
	lv_roller_get_selected_str(ui_RollerDeleteMenuChoose, buf, sizeof(buf));
	printf("selected name:\n%s\n", buf);

	/* 根据菜单名删除菜单 */
	delete_menu_by_name(&buf);

	/* 提取menu_config_json_str菜单名 */
	cJSON *menu_config_json;
	menu_config_json = cJSON_Parse(menu_config_json_str_return());

	cJSON *food_menu = cJSON_GetObjectItemCaseSensitive(menu_config_json, "food_menu");
	int array_size = cJSON_GetArraySize(food_menu);

	char menu_roller_new_option_name[500] = "";
	for (int i = 0; i < array_size; i++) {
		cJSON *food = cJSON_GetArrayItem(food_menu, i);       
		cJSON *food_name = cJSON_GetObjectItemCaseSensitive(food, "name");
		// printf("current_menu_roller_option_name:\n%s\n", food_name->valuestring);
		if(i == 0)
		{
			strcpy(menu_roller_new_option_name, food_name->valuestring);
		}
		else
		{
			strcat(menu_roller_new_option_name, "\n");
			strcat(menu_roller_new_option_name, food_name->valuestring);
		}
	}
	printf("menu_roller_new_option_name:\n%s\n", menu_roller_new_option_name);
	cJSON_Delete(menu_config_json);

	/* 添加菜单进自动操作界面，删除界面滚轮 */
	lv_roller_set_options(ui_MenuOptionRollerChoose, menu_roller_new_option_name, LV_ROLLER_MODE_NORMAL);  //自动操作界面菜单列表
	lv_roller_set_options(ui_RollerDeleteMenuChoose, menu_roller_new_option_name, LV_ROLLER_MODE_NORMAL);  //删除界面菜单列表
	lv_dropdown_set_options(ui_DropdownEditMenuChoose, menu_roller_new_option_name); //修改界面菜单列表
}

// 修改菜单最终确定键
void EditCurrentMenu(lv_event_t * e)
{
	// Your code here
	/* 提取Dropdown菜单名 */
	food_menu_item_config current_modify_menu;

	char buf[32];
	lv_dropdown_get_selected_str(ui_DropdownEditMenuChoose, buf, sizeof(buf));	
	current_modify_menu.menu_name = &buf;
	// printf("current_modify_menu.menu_name: %s\n", current_modify_menu.menu_name);
	
	if(temperature_unit == Temperature_Unit_Fahrenheit)
	{
		current_modify_menu.target_temperature = (double)((lv_slider_get_value(ui_SliderEditMenuTargetTemp) - 32.00) / 1.800 + 273.15);
	}
	else
	{
		current_modify_menu.target_temperature = (double)(lv_slider_get_value(ui_SliderEditMenuTargetTemp) + 273.15);
	}
	// printf("current_modify_menu.target_temperature: %f\n", current_modify_menu.target_temperature);

	current_modify_menu.cooking_timer_seconds = (int)lv_slider_get_value(ui_SliderEditMenuTargetCountdown) * Manual_countdown_interval;
	// printf("current_modify_menu.cooking_timer_seconds: %d\n", current_modify_menu.cooking_timer_seconds);
	current_modify_menu.menu_force_heat_time = lv_slider_get_value(ui_Slider_Print_Speed);
	modify_menu_by_struct(current_modify_menu);
	// printf("button A\n");
}

// 修改菜单目标温度滑条触发
void EditMenuTargetTemperatureSlider(lv_event_t * e)
{
    // Your code here
	lv_obj_t *edit_menu_target_temperature_slider = lv_event_get_target(e);
	int32_t edit_menu_target_temperature = lv_slider_get_value(edit_menu_target_temperature_slider);
	if(temperature_unit == Temperature_Unit_Fahrenheit)
	{
		lv_label_set_text_fmt(ui_LabelEditMenuTargetTemperature, "%ld°F", edit_menu_target_temperature);
	}
	else
	{
		lv_label_set_text_fmt(ui_LabelEditMenuTargetTemperature, "%ld°C", edit_menu_target_temperature);
	}

	lv_slider_set_value(ui_SliderEditMenuTargetTemp, edit_menu_target_temperature, LV_ANIM_ON);
}

// 修改菜单目标时间滑条触发
void EditSetCountdownTime(lv_event_t * e)
{
    // Your code here
	lv_obj_t *edit_menu_target_countdown_slider = lv_event_get_target(e);
	int edit_menu_target_countdown_time = (int)lv_slider_get_value(edit_menu_target_countdown_slider) * Manual_countdown_interval;
	
	// Change 设定倒计时的值
	lv_label_set_text_fmt(ui_LabelEditMenuCountdown, "%d:%d", edit_menu_target_countdown_time / 60, edit_menu_target_countdown_time % 60);
}

// 修改菜单选择目标菜单滚轮触发
void EditCurrentMenuSelect(lv_event_t * e)
{
    // Your code here
	char buf[32];
	lv_dropdown_get_selected_str(ui_DropdownEditMenuChoose, buf, sizeof(buf));
	food_menu_item_config temporary_menu = menu_search_by_name(buf);

	//修改菜单操作的温度显示和slider位置
	if(temperature_unit == Temperature_Unit_Fahrenheit)
	{
		lv_label_set_text_fmt(ui_LabelEditMenuTargetTemperature, "%d°F", (int32_t)(round((temporary_menu.target_temperature - 273.15) * 1.80 + 32.00)));	// 显示自动操作设定温度
		lv_slider_set_value(ui_SliderEditMenuTargetTemp, (int32_t)(round((temporary_menu.target_temperature - 273.15) * 1.80 + 32.00)), LV_ANIM_ON);	// Menu Target Temperature Bar
	}
	else
	{
		lv_label_set_text_fmt(ui_LabelEditMenuTargetTemperature, "%d°C", (int32_t)(round(temporary_menu.target_temperature - 273.15)));	// 显示自动操作设定温度
		lv_slider_set_value(ui_SliderEditMenuTargetTemp, (int32_t)(round(temporary_menu.target_temperature - 273.15)), LV_ANIM_ON);	// Menu Target Temperature Bar
	}
											
	//自动操作的倒计时显示
	lv_label_set_text_fmt(ui_LabelEditMenuCountdown, "%d:%d", temporary_menu.cooking_timer_seconds / 60, temporary_menu.cooking_timer_seconds % 60); // 显示自动操作设定时间
	lv_slider_set_value(ui_SliderEditMenuTargetCountdown, (temporary_menu.cooking_timer_seconds / Manual_countdown_interval), LV_ANIM_ON);
}

// 屏保任意键关闭触发
void Screensaver_Menu_Event(lv_event_t * e)
{
	if(lv_scr_act() == ui_ScreenScreenSaverMenu)
	{
		_ui_screen_change(&ui_ScreenAuto, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenAuto_screen_init);
	}
}

// 投放按键触发
void DropFoodReminderDone(lv_event_t * e)
{
	if(countdown_drop_approve_read() == Timer_Drop_Wait_Disapprove)
	{
		countdown_drop_approve_write(Timer_Drop_Approve);
		_ui_screen_change(&ui_ScreenAuto, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenAuto_screen_init);
	}
	else if(read_manual_drop_approve() == manual_drop_wait_approve)
	{
		// write_manual_drop_approve(manual_drop_approve);
		_ui_screen_change(&ui_ScreenManual, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ScreenManual_screen_init);
	}
}

// 手动模式升降机选择
void CallDropdownMotorLeftRightManual(lv_event_t * e)
{
	// // Your code here
	// u_int16_t manual_motor_switch_case = 2;
	// if(PID_mode_read() == mode_null)
	// {
	// 	manual_motor_switch_case = lv_dropdown_get_selected(ui_DropdownMotorLeftRightManual);
	// 	printf("manual_motor_switch_case = %d\n", manual_motor_switch_case);
	// 	switch(manual_motor_switch_case)
	// 	{
	// 		case 0: motor_left_right_queue_write(motor_left); break;
	// 		case 1: motor_left_right_queue_write(motor_right); break;
	// 		case 2: motor_left_right_queue_write(motor_both); break;
	// 	}
	// }	
}

// 自动模式升降机选择
void CallDropdownMotorLeftRightAuto(lv_event_t * e)
{
	// // Your code here
	// u_int16_t auto_motor_switch_case = 2;
	// if(PID_mode_read() == mode_null)
	// {
	// 	auto_motor_switch_case = lv_dropdown_get_selected(ui_DropdownMotorLeftRightAuto);
	// 	printf("auto_motor_switch_case = %d\n", auto_motor_switch_case);
	// 	switch(auto_motor_switch_case)
	// 	{
	// 		case 0: motor_left_right_queue_write(motor_left); break;
	// 		case 1: motor_left_right_queue_write(motor_right); break;
	// 		case 2: motor_left_right_queue_write(motor_both); break;
	// 	}
	// }
}

esp_err_t lv_obj_whether_ban_animation(const lv_obj_t * obj, bool animation_will_be_ban)
{
	if((animation_will_be_ban == 0) && (lv_obj_has_state(obj, LV_STATE_DISABLED)))
	{
		lv_obj_clear_state(obj, LV_STATE_DISABLED);
		return ESP_OK;
	}
	else if((animation_will_be_ban == 1) && (lv_obj_has_state(obj, LV_STATE_DISABLED) == 0))
	{
		lv_obj_add_state(obj, LV_STATE_DISABLED);
		return ESP_OK;
	}
	return ESP_OK;
}
