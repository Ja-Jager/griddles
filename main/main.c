#include "main.h"

#define TAG "ESP-EXAMPLE"

#define Manual_Temperature_Fahrenheit_Maximum 464
#define Manual_Temperature_Fahrenheit_Minimum 212

#define Manual_Temperature_Celsius_Maximum 240
#define Manual_Temperature_Celsius_Minimum 100

#define Temperature_Unit_Fahrenheit_for_main 1
#define Temperature_Unit_Celsius_for_main 0

#define Time_Needed_appear_ScreenSaver 30

lv_obj_t *label;

bool temperature_unit_main = Temperature_Unit_Fahrenheit_for_main;

screen_is_loaded_t current_screen_load = No_loaded;
// TaskHandle_t * handle_UI_Task;

/*******************************************************************************
 * Private functions
 *******************************************************************************/
void UI_task(void *pvParameters)
{
    // 上电读取NVS，修改语言
    set_language_by_nvs_for_power_on();

    // 自动操作初始化显示
    food_menu_item_config temporary_menu = menu_search_by_sequence(0); // 选择默认鸡块菜单
    double TargetTemperature = 450;

    // lv_obj_add_flag(ui_DropdownMotorLeftRightAuto, LV_OBJ_FLAG_HIDDEN);     /// Flags
    // lv_obj_add_flag(ui_DropdownMotorLeftRightManual, LV_OBJ_FLAG_HIDDEN);     /// Flags

    if (temperature_unit == Temperature_Unit_Fahrenheit)
    {
        Encoder_temperature_queue_write(((TargetTemperature - 273.15) * 1.80 + 32.00));
    }
    else
    {
        Encoder_temperature_queue_write((TargetTemperature - 273.15));
    }
    int32_t current_encoder = 0;
    int32_t previous_encoder = 0;

    // 显示初始化自動操作倒计时
    lv_label_set_text_fmt(ui_LabelSetTimeValue, _("%d:%d"), temporary_menu.cooking_timer_seconds / 60, temporary_menu.cooking_timer_seconds % 60); // 显示初始设定时间

    // 显示初始化手動操作倒计时
    lv_label_set_text_fmt(ui_LabelSensorTempValue2, "%s", _("03:00"));

    // 显示初始化手動操作设定时间
    lv_label_set_text(ui_LabelManualTimerSet, "03:00");

    // 显示初始化温度
    if (temperature_unit == Temperature_Unit_Fahrenheit_for_main)
    {
        lv_label_set_text_fmt(ui_LabelTargetTemperatureValue, "%d°F", (int32_t)(round)((temporary_menu.target_temperature - 273.15) * 1.80 + 32.00)); // 显示初始设定温度
    }
    else
    {
        lv_label_set_text_fmt(ui_LabelTargetTemperatureValue, "%d°C", (int32_t)(round)(temporary_menu.target_temperature - 273.15)); // 显示初始设定温度
    }

    // 显示版本号
    lv_label_set_text_fmt(ui_LabelHeaderVersionNumber, "%s", VERSION_NUMBER);
    lv_label_set_text_fmt(ui_LabelHeaderVersionNumber1, "%s", VERSION_NUMBER);

    /* 提取menu_config_json_str菜单名并写入 */
    cJSON *menu_config_json;
    menu_config_json = cJSON_Parse(menu_config_json_str_return());

    cJSON *food_menu = cJSON_GetObjectItemCaseSensitive(menu_config_json, "food_menu");
    int array_size = cJSON_GetArraySize(food_menu);

    char menu_roller_new_option_name[500] = "";
    for (int i = 0; i < array_size; i++)
    {
        cJSON *food = cJSON_GetArrayItem(food_menu, i);
        cJSON *food_name = cJSON_GetObjectItemCaseSensitive(food, "name");
        if (i == 0)
        {
            strcpy(menu_roller_new_option_name, food_name->valuestring);
        }
        else
        {
            strcat(menu_roller_new_option_name, "\n");
            strcat(menu_roller_new_option_name, food_name->valuestring);
        }
    }
    cJSON_Delete(menu_config_json);
    lv_roller_set_options(ui_MenuOptionRollerChoose, menu_roller_new_option_name, LV_ROLLER_MODE_NORMAL);
    lv_roller_set_options(ui_RollerDeleteMenuChoose, menu_roller_new_option_name, LV_ROLLER_MODE_NORMAL);
    lv_dropdown_set_options(ui_DropdownEditMenuChoose, menu_roller_new_option_name);
    /* Create a task for NTC thermistor */
    lv_timer_t *timer_thermistor_update = lv_timer_create(NTC_thermistor_update_UI, 100, NULL);

    /* Create a task for manual countdown */
    lv_timer_t *manual_countdown_update = lv_timer_create(manual_mode_countdown_update_UI, 100, NULL);

    /* 当前屏幕 */
    lv_obj_t *active_screen;
    uint16_t MenuRollerChooseSelectedOption = 0;

    // printf("Calibration: %d\n", NTC_thermistor_calibration_queue_read());
    lv_label_set_text_fmt(ui_Label_Print_Speed_Number, "%d K", NTC_thermistor_calibration_queue_read());
    lv_slider_set_value(ui_Slider_Print_Speed, NTC_thermistor_calibration_queue_read(), LV_ANIM_OFF);

    lv_obj_add_event_cb(ui_ScreenAuto, my_ScreenAuto_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenManual, my_ScreenManual_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenSetting, my_ScreenSetting_cb, LV_EVENT_ALL, NULL);
    while (1) 
    {     
        // Manual Mode
        // 手动操作倒计时剩余时间显示
        enum mode_select_state current_PID_mode = PID_mode_read();

        lv_label_set_text(ui_LabelAutoHeader, "Scroll to choose menu, Press to Start");//"滚动滑轮选择菜单，按下开始键启动倒计时"
        lv_label_set_text(ui_LabelAutoHeader1, "Press Start to turn on cooking.");//"按下开始键保持恒温"

        // 手动操作温度显示（旋钮）
        current_encoder = Encoder_queue_read();
        TargetTemperature = Encoder_temperature_queue_read();
        //获取屏幕名称
        
        if (current_encoder != previous_encoder)
        {
            active_screen = lv_scr_act();
            if((active_screen == ui_ScreenAuto) || (active_screen == ui_ScreenScreenSaverMenu))
            {
                if(lv_roller_get_selected(ui_MenuOptionRollerChoose) == 0)
                {
                    if((current_encoder - previous_encoder) < 0)
                    {
                        MenuRollerChooseSelectedOption = 0;
                    }
                    else
                    {
                        MenuRollerChooseSelectedOption = lv_roller_get_selected(ui_MenuOptionRollerChoose) + (current_encoder - previous_encoder);
                    }
                }
                else
                {
                    MenuRollerChooseSelectedOption = lv_roller_get_selected(ui_MenuOptionRollerChoose) + (current_encoder - previous_encoder);
                }
                lv_roller_set_selected(ui_MenuOptionRollerChoose, MenuRollerChooseSelectedOption, LV_ANIM_ON);
                vTaskDelay(1 / portTICK_PERIOD_MS);
                lv_event_send(ui_MenuOptionRollerChoose, LV_EVENT_VALUE_CHANGED, NULL);
            }
            else if(active_screen == ui_ScreenManual)
            {
                TargetTemperature = TargetTemperature + (double)(current_encoder - previous_encoder);
                if (temperature_unit == Temperature_Unit_Fahrenheit_for_main)
                {
                    if (TargetTemperature >= Manual_Temperature_Fahrenheit_Maximum)
                    {
                        TargetTemperature = Manual_Temperature_Fahrenheit_Maximum;
                    }
                    else if (TargetTemperature <= Manual_Temperature_Fahrenheit_Minimum)
                    {
                        TargetTemperature = Manual_Temperature_Fahrenheit_Minimum;
                    }
                }
                else
                {
                    if (TargetTemperature >= Manual_Temperature_Celsius_Maximum)
                    {
                        TargetTemperature = Manual_Temperature_Celsius_Maximum;
                    }
                    else if (TargetTemperature <= Manual_Temperature_Celsius_Minimum)
                    {
                        TargetTemperature = Manual_Temperature_Celsius_Minimum;
                    }
                }
            }  
        }
        // printf("TargetTemperature:\n%f\n", TargetTemperature);
        if (temperature_unit == Temperature_Unit_Fahrenheit_for_main)
        {
            lv_label_set_text_fmt(ui_LabelManualTargetTemperature, "%d°F", (int32_t)TargetTemperature);
        }
        else
        {
            lv_label_set_text_fmt(ui_LabelManualTargetTemperature, "%d°C", (int32_t)TargetTemperature);
        }
        lv_slider_set_value(ui_SliderManualTargetTemperature, (int32_t)TargetTemperature, LV_ANIM_ON);

        Encoder_temperature_queue_write(TargetTemperature);
        previous_encoder = current_encoder;

        if (current_PID_mode == mode_manual)
        {
            if (temperature_unit == Temperature_Unit_Fahrenheit_for_main)
            {
                PID_set_temperature_write((TargetTemperature - 32.00) / 1.800 + 273.15); // 发送手动操作设定温度给PID
            }
            else
            {
                PID_set_temperature_write(TargetTemperature + 273.15); // 发送手动操作设定温度给PID
            }
        }
        // printf("current_PID_mode:%d\n", current_PID_mode);
        vTaskDelay(150 / portTICK_PERIOD_MS);
    }
}

// *INDENT-OFF*
void app_lvgl_display(void)
{
    bsp_display_lock(0);

#ifdef LVGL_BENCHMARK
    lv_demo_benchmark();
#else
    ui_init();
#endif

    bsp_display_unlock();
}

void app_main(void)
{
    nvs_init();

    encoder_queue_init();

    // liftTube_spillOil_overHeat_init();
    /* Test menu read NVS when first power on */
    // menu_test_for_first_power_on("food_menu_nvs");

    // /* Initialize NTC_thermistor */
    // NTC_thermistor_init();
    Max6675_init();

    // /* Initialize PID calculate */
    PID_calculate_init();

    /* Initialize buzzer */
    buzzer_init();
    // buzzer(NOTE_G4, 0, 0, 0, 0);

    /* Initialize timer mode */
    countdown_init();

    /* Initialize manual mode */
    manual_mode_init();

    // /* Initialize PWM */
    softPwm_t softpwm =
        {
            .PWMPin = 4,
            .freq = 0.2,
        };
    softpwm_init(&softpwm);

    /* Initialize I2C (for touch) */
    bsp_i2c_init();
    /* Initialize display and LVGL */
    bsp_display_start();
    // bsp_display_rotate(bsp_display_start(), LV_DISP_ROT_180);

    /* Turn on display backlight */
    bsp_display_backlight_on();

    /* Add and show objects on display */
    app_lvgl_display();

    // xTaskCreate(memory_monitor_task, "memory_monitor_task", 1024 * 4, NULL, 2, NULL);

    // input_task_create();

#ifndef LVGL_BENCHMARK
    xTaskCreate(UI_task, "UI_task", 1024 * 16, NULL, 2, NULL);
    lv_init();
    lv_port_indev_init();
#endif
    ESP_LOGI(TAG, "Example initialization done.");
}
// *INDENT-ON*

void memory_monitor_task(void *pvParameters)
{
    uint32_t total, used, largest, free_heap;
    while (1)
    {
        total = getHeapSize();
        ESP_LOGI("HEAP INFO", "used heap:%ld", total);

        used = total - xPortGetFreeHeapSize();
        ESP_LOGI("HEAP INFO", "total free heap:%ld", used);

        largest = xPortGetMinimumEverFreeHeapSize();
        ESP_LOGI("HEAP INFO", "largest heap:%ld", largest);

        free_heap = xPortGetFreeHeapSize();
        ESP_LOGI("HEAP INFO", "Free heap:%ld", free_heap);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void NTC_thermistor_update_UI(lv_timer_t *timer)
{
    double temperature =0.0;
    temperature = NTC_thermistor_queue_read();
    // printf("temperature:\n%f\n", temperature);
    if(temperature_unit == Temperature_Unit_Fahrenheit_for_main)
    {
        #if CONFIG_SIMULATED_TEMPERATURE
            //办公室测温
            lv_label_set_text_fmt(ui_LabelSensorTempValue1, "%d°F", (int32_t)(round)((temperature - 173.15) * 1.80 + 32.00)); // Manual Screen Sensor Temperature
            lv_label_set_text_fmt(ui_LabelSensorTempValue, "%d°F", (int32_t)(round)((temperature - 173.15) * 1.80 + 32.00));  // Countdown Screen Sensor Temperature
        #else
            //真实测温
            lv_label_set_text_fmt(ui_LabelSensorTempValue1, "%d°F", (int32_t)(round)((temperature - 273.15) * 1.80 + 32.00)); // Manual Screen Sensor Temperature
            lv_label_set_text_fmt(ui_LabelSensorTempValue, "%d°F", (int32_t)(round)((temperature - 273.15) * 1.80 + 32.00));  // Countdown Screen Sensor Temperature
        #endif        
    }
    else
    {
        #if CONFIG_SIMULATED_TEMPERATURE
            //办公室测温
            lv_label_set_text_fmt(ui_LabelSensorTempValue1, "%d°C", (int32_t)(round)(temperature - 173.15)); // Manual Screen Sensor Temperature
            lv_label_set_text_fmt(ui_LabelSensorTempValue, "%d°C", (int32_t)(round)(temperature - 173.15));  // Countdown Screen Sensor Temperature
        #else
            //真实测温
            lv_label_set_text_fmt(ui_LabelSensorTempValue1, "%d°C", (int32_t)(round)(temperature - 273.15)); // Manual Screen Sensor Temperature
            lv_label_set_text_fmt(ui_LabelSensorTempValue, "%d°C", (int32_t)(round)(temperature - 273.15));  // Countdown Screen Sensor Temperature
        #endif
    }
}

/* manual mode timer */
void manual_mode_countdown_update_UI(lv_timer_t *timer)
{
    enum mode_select_state current_PID_mode = PID_mode_read();
    if (current_PID_mode == mode_manual) 
    {
        if(read_manual_approve_state() == manual_preheat_disapprove) // 无批准倒计时或倒计时时长为0:0的情况
        {
            if(manual_countdown_rest_time_read() <= 0)
            {
                lv_label_set_text_fmt(ui_LabelSensorTempValue2, "%s", _("∞"));
            }
            else
            {
                lv_label_set_text_fmt(ui_LabelSensorTempValue2, "%s", _("Heat")); // 手动剩余时间显示预热
            }    
        }
        else
        {
            if(manual_countdown_time_read() == 0)
            {
                lv_label_set_text_fmt(ui_LabelSensorTempValue2, "%s", _("∞"));
            }
            else
            {
                lv_label_set_text_fmt(ui_LabelSensorTempValue2, _("%d:%d"), manual_countdown_rest_time_minute(manual_countdown_rest_time_read()), manual_countdown_rest_time_second(manual_countdown_rest_time_read())); // 显示手动操作设定时间    
            }    
            if(read_manual_drop_approve() == manual_drop_disapprove)
            {
                // write_manual_drop_approve(manual_drop_wait_approve);
                // buzzer_occasion_queue_write(buzzer_drop_approve);
            }
        }
    }
    else 
    {
        // write_manual_drop_approve(manual_preheat_disapprove);
        // 显示手动操作倒计时总时长
        lv_label_set_text_fmt(ui_LabelSensorTempValue2, _("%d:%d"), (manual_countdown_time_read()/60), (manual_countdown_time_read()%60)); // 显示手动操作操作倒计时剩余时间    
        lv_obj_whether_ban_animation(ui_BarManualTemperature1, 0);
    }
}

uint32_t getHeapSize(void)
{
    multi_heap_info_t info;
    heap_caps_get_info(&info, MALLOC_CAP_INTERNAL);
    return info.total_free_bytes + info.total_allocated_bytes;
}

void my_ScreenAuto_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        current_screen_load = Auto_Loaded;
    }
}

void my_ScreenManual_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        current_screen_load = Manual_Loaded;
    }
}

void my_ScreenSetting_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        current_screen_load = Setting_Loaded;
    }
}

void set_language_by_nvs_for_power_on()
{
    // Set language
    lv_i18n_init(lv_i18n_language_pack);
    char *current_locate_language = "en";
	// char *current_locate_full_language = "English";
    uint16_t current_locate_selected_option = 0;
	if(nvs_read_str("locale_name", &current_locate_language) != ESP_OK)
	{
		current_locate_language = "en";
		nvs_write_str("locale_name", current_locate_language);
	}
	if (strcmp(current_locate_language, "zh-hk") == 0) {
        current_locate_selected_option = 1;
    } else if (strcmp(current_locate_language, "zh-cn") == 0) {
        current_locate_selected_option = 2;
    } else if (strcmp(current_locate_language, "en") == 0) {
        current_locate_selected_option = 0;
    }else if (strcmp(current_locate_language, "es") == 0) {
        current_locate_selected_option = 3;
    }else if (strcmp(current_locate_language, "fr") == 0) {
        current_locate_selected_option = 4;
    }else if (strcmp(current_locate_language, "id") == 0) {
        current_locate_selected_option = 5;
    }
    
    lv_i18n_set_locale(current_locate_language);
    refresh_lv_i18n_label_text();
    lv_roller_set_selected(ui_Roller2, current_locate_selected_option, LV_ANIM_ON);
    free(current_locate_language);
}
