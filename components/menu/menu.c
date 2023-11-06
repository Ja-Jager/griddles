#include "menu.h"

QueueHandle_t handle_queue_menu_sequence;
QueueHandle_t handle_queue_name;
QueueHandle_t handle_queue_cooking_timer_seconds;
QueueHandle_t handle_queue_menu_create;

char menu_config_json_str[3100];

food_menu_item_config NULL_menu(void)
{
    food_menu_item_config NULL_match_menu;
    NULL_match_menu.menu_sequence = -1;
    return NULL_match_menu;
}

food_menu_item_config menu_search_by_sequence(int sequence)
{
    // ESP_LOGI("food menu test","enter menu search");

    cJSON *menu_config_json;
    menu_config_json = cJSON_Parse(menu_config_json_str);
    // ESP_LOGI("menu config json str","menu_config_json_str:%s", menu_config_json_str);

    cJSON *food_menu = cJSON_GetObjectItemCaseSensitive(menu_config_json, "food_menu");
    // ESP_LOGI("food menu test","read food menu");

    int array_size = cJSON_GetArraySize(food_menu);
    // ESP_LOGI("output array size", "array size:%d", array_size);
    if(array_size == 0)
    {
        return NULL_menu();
    }

    cJSON *food = cJSON_GetArrayItem(food_menu, sequence);       

    food_menu_item_config match_menu;
    cJSON *food_temperature = cJSON_GetObjectItemCaseSensitive(food, "temperature");

    // /*JSON的unit赋予返回的结构体*/
    // cJSON *food_temperature_unit = cJSON_GetObjectItemCaseSensitive(food_temperature, "unit");
    // match_menu.target_temperature_unit = food_temperature_unit->valuestring;

    /*JSON的target赋予返回的结构体*/
    cJSON *food_temperature_target = cJSON_GetObjectItemCaseSensitive(food_temperature, "target");
    match_menu.target_temperature = food_temperature_target->valuedouble;

    /*JSON的countdown赋予返回的结构体*/
    cJSON *food_countdown = cJSON_GetObjectItemCaseSensitive(food, "countdown");
    cJSON *food_countdown_total = cJSON_GetObjectItemCaseSensitive(food_countdown, "total");
    match_menu.cooking_timer_seconds = food_countdown_total->valueint;
    cJSON *food_countdown_force_heat_time = cJSON_GetObjectItemCaseSensitive(food_countdown, "timer_force_heat");
    match_menu.menu_force_heat_time = food_countdown_force_heat_time->valueint;

    cJSON_Delete(menu_config_json);
    return match_menu;
}

food_menu_item_config menu_search_by_name(char * menu_name)
{
    // ESP_LOGE("food menu test","enter menu search");

    cJSON *menu_config_json;
    menu_config_json = cJSON_Parse(menu_config_json_str);
    // ESP_LOGE("menu config json str","menu_config_json_str:\n%s\n", menu_config_json_str);

    cJSON *food_menu = cJSON_GetObjectItemCaseSensitive(menu_config_json, "food_menu");
    // ESP_LOGE("food menu test","read food menu");

    int array_size = cJSON_GetArraySize(food_menu);
    // ESP_LOGE("output array size", "array size:%d", array_size);
    for (int i = 0; i < array_size; i++) {
        // ESP_LOGE("array test","enter for loop");
        cJSON *food = cJSON_GetArrayItem(food_menu, i);       
        cJSON *food_name = cJSON_GetObjectItemCaseSensitive(food, "name");
        if (strcmp(food_name->valuestring, menu_name) == 0) {
            // ESP_LOGE("food name test","enter match food name");

            // TODO: Exception handling if CJSON get return NULL
            food_menu_item_config match_menu;
            cJSON *food_temperature = cJSON_GetObjectItemCaseSensitive(food, "temperature");

            /*JSON的target赋予返回的结构体*/
            cJSON *food_temperature_target = cJSON_GetObjectItemCaseSensitive(food_temperature, "target");
            match_menu.target_temperature = food_temperature_target->valuedouble;
            // ESP_LOGE("menu temperature", "menu by name temperature:\n%f\n", match_menu.target_temperature);

            /*JSON的countdown赋予返回的结构体*/
            cJSON *food_countdown = cJSON_GetObjectItemCaseSensitive(food, "countdown");
            cJSON *food_countdown_total = cJSON_GetObjectItemCaseSensitive(food_countdown, "total");
            match_menu.cooking_timer_seconds = food_countdown_total->valueint;
            cJSON *food_countdown_force_heat_time = cJSON_GetObjectItemCaseSensitive(food_countdown, "timer_force_heat");
            match_menu.menu_force_heat_time = food_countdown_force_heat_time->valueint;
            // ESP_LOGE("menu countdown", "menu by name countdown:\n%d\n", match_menu.cooking_timer_seconds);

            cJSON_Delete(menu_config_json);
            return match_menu;
        }

    }
    cJSON_Delete(menu_config_json);
    return NULL_menu();
}

esp_err_t menu_read_json_nvs(char *key)
{
    char nvs_menu_json[1550];
    esp_err_t err = nvs_read_str(key, &nvs_menu_json);

    // Deserialize
    strcpy(menu_config_json_str, nvs_menu_json);

    return err;
}

esp_err_t menu_write_json_nvs(char * key)
{
    esp_err_t err = nvs_write_str(key, menu_config_json_str);

    return err;
}

esp_err_t menu_test_for_first_power_on(char *key)
{
    char *nvs_menu_json;

    xQueueCreate(1, sizeof(menu_config_json_str));

    char *default_menu = "{\"food_menu\":[{\"name\":\"雞肶\",\"temperature\":{\"target\":449.82},\"countdown\":{\"total\":600,\"timer_force_heat\":10,\"buzzer\":[30,60,180,200]}},{\"name\":\"雞全翼\",\"temperature\":{\"unit\":\"fahrenheit\",\"target\":394.26},\"countdown\":{\"total\":480,\"timer_force_heat\":11,\"buzzer\":[60,150]}},{\"name\":\"豬扒\",\"temperature\":{\"unit\":\"fahrenheit\",\"target\":435.93},\"countdown\":{\"total\":420,\"timer_force_heat\":12,\"buzzer\":[60,150]}},{\"name\":\"薯仔\",\"temperature\":{\"unit\":\"fahrenheit\",\"target\":449.82},\"countdown\":{\"total\":240,\"timer_force_heat\":13,\"buzzer\":[60,150]}},{\"name\":\"春卷\",\"temperature\":{\"unit\":\"fahrenheit\",\"target\":394.26},\"countdown\":{\"total\":240,\"timer_force_heat\":14,\"buzzer\":[60,150]}}]}";
    int counter = 0;
    nvs_handle_t handle;
    esp_err_t err;
    
    while (counter < 2)
    {
        esp_err_t err = menu_read_json_nvs(key);
        // err = menu_read_json_nvs(key);
        counter++;
        if(err == ESP_OK)
        {
            ESP_LOGI("MENU_READ_ERROR","Menu succeeded to access nvs.");
            esp_err_t err = nvs_read_str(key, &nvs_menu_json);
            ESP_LOGI("nvs read str","read_menu_config_json_str:%S",nvs_menu_json);
            // Deserialize
            strcpy(menu_config_json_str, nvs_menu_json);



            return ESP_OK;
        }
        else if(err == ESP_ERR_NVS_NOT_FOUND)
        {
            ESP_LOGI("MENU_READ_ERROR","ESP_ERR_NVS_NOT_FOUND");

            strcpy(menu_config_json_str, default_menu);
            menu_write_json_nvs(key);

            counter++;
        }
    }
    // free(default_menu);
    return ESP_OK;
}

char * temperature_int_to_str(int temperature)
{
    // Convert temperature in int to char *, e.g. 180 to "180"
    int temperature_to_str_length = snprintf( NULL, 0, "%d", temperature);
    char* temperature_to_str = malloc( temperature_to_str_length + 1 );
    snprintf( temperature_to_str, temperature_to_str_length + 1, "%d", temperature);

    // Add degree symbol at the end, e.g. "180" to "180°"
    int temperature_to_str_degree_length = snprintf(NULL, 0, "%s°", temperature_to_str);
    char* temperature_to_str_degree = malloc(temperature_to_str_degree_length + 1);
    snprintf(temperature_to_str_degree, temperature_to_str_degree_length + 1, "%s°", temperature_to_str);

    free(temperature_to_str);

    return temperature_to_str_degree;
}

char * time_int_seconds_to_str(int second)
{
    int minute = second / 60;
	int second_mod = second % 60;

    // Convert 75 seconds to "1:15"
    int time_str_length = snprintf( NULL, 0, "%d:%d", minute, second_mod);
    char* time_str = malloc( time_str_length + 1 );
    snprintf(time_str, time_str_length + 1, "%d:%d", minute, second_mod);

    return time_str;
}

esp_err_t create_menu(food_menu_item_config menu_create)
{
    /* 新建object */
    cJSON *CJson_menu = cJSON_CreateObject();

    cJSON_AddStringToObject(CJson_menu, "name", menu_create.menu_name);

    cJSON *CJson_temperature = cJSON_CreateObject();
    cJSON_AddNumberToObject(CJson_temperature, "target", menu_create.target_temperature);
    cJSON_AddItemToObject(CJson_menu, "temperature", CJson_temperature);

    cJSON *CJson_countdown = cJSON_CreateObject();
    cJSON_AddNumberToObject(CJson_countdown, "total", menu_create.cooking_timer_seconds);
    cJSON_AddNumberToObject(CJson_countdown, "timer_force_heat", menu_create.menu_force_heat_time);
    cJSON_AddItemToObject(CJson_menu, "countdown", CJson_countdown);

    char *create_new_menu = cJSON_Print(CJson_menu);
    printf("CJson create new menu:\n%s\n", create_new_menu);

    /* 提取主菜单并加入新菜单 */
    cJSON *CJson_root = cJSON_Parse(menu_config_json_str);
    cJSON *food_menu = cJSON_GetObjectItemCaseSensitive(CJson_root, "food_menu");
    cJSON_AddItemToArray(food_menu, CJson_menu); 
    char *new_menu_config_json_str = cJSON_Print(CJson_root);
    strcpy(menu_config_json_str, new_menu_config_json_str);
    nvs_write_str("food_menu_nvs", menu_config_json_str);    

    cJSON_free(create_new_menu);
    cJSON_free(new_menu_config_json_str);
    cJSON_Delete(CJson_root);
    return ESP_OK;
}

esp_err_t delete_menu_by_name(char *name)
{
    cJSON *CJson_root = cJSON_Parse(menu_config_json_str);
    cJSON *food_menu = cJSON_GetObjectItemCaseSensitive(CJson_root, "food_menu");
    int array_size = cJSON_GetArraySize(food_menu);

    for (int i = 0; i < array_size; i++) {
        cJSON *food = cJSON_GetArrayItem(food_menu, i);       
        cJSON *food_name = cJSON_GetObjectItemCaseSensitive(food, "name");

        if (strcmp(food_name->valuestring, name) == 0) 
        {
            cJSON_DeleteItemFromArray(food_menu, i);
            printf("deleting succeed.\n"); 
            char *current_menu_config_json_str = cJSON_Print(CJson_root);
            strcpy(menu_config_json_str, current_menu_config_json_str);
            nvs_write_str("food_menu_nvs", menu_config_json_str);    
            cJSON_Delete(CJson_root);
            cJSON_free(current_menu_config_json_str);
            return ESP_OK;
        }
    }
    cJSON_Delete(CJson_root);

    return ESP_OK;
}

void modify_menu_by_struct(food_menu_item_config menu_modify)
{
    cJSON *menu_config_json;
    menu_config_json = cJSON_Parse(menu_config_json_str);
    // ESP_LOGE("menu config json str","menu_config_json_str:\n%s\n", menu_config_json_str);

    cJSON *food_menu = cJSON_GetObjectItemCaseSensitive(menu_config_json, "food_menu");
    // ESP_LOGE("food menu test","read food menu");

    int array_size = cJSON_GetArraySize(food_menu);
    // ESP_LOGE("output array size", "array size:%d", array_size);
    for (int i = 0; i < array_size; i++) {
        // ESP_LOGE("array test","enter for loop");
        cJSON *food = cJSON_GetArrayItem(food_menu, i);       
        cJSON *food_name = cJSON_GetObjectItemCaseSensitive(food, "name");
        if (strcmp(food_name->valuestring, menu_modify.menu_name) == 0) {
            // food_menu_item_config match_menu;
            cJSON *food_temperature = cJSON_GetObjectItemCaseSensitive(food, "temperature");
            cJSON *food_new_temperature_target;
            food_new_temperature_target = cJSON_CreateNumber(menu_modify.target_temperature);
            cJSON_ReplaceItemInObject(food_temperature, "target", food_new_temperature_target);

            cJSON *food_countdown = cJSON_GetObjectItemCaseSensitive(food, "countdown");
            cJSON *food_new_countdown_total;
            food_new_countdown_total = cJSON_CreateNumber(menu_modify.cooking_timer_seconds);
            cJSON_ReplaceItemInObject(food_countdown, "total", food_new_countdown_total);

            cJSON *food_new_countdown_force_heat;
            food_new_countdown_force_heat = cJSON_CreateNumber(menu_modify.menu_force_heat_time);
            cJSON_ReplaceItemInObject(food_countdown, "timer_force_heat", food_new_countdown_force_heat);

            // char *match_buf[3100] = cJSON_Print(menu_config_json);
            strcpy(&menu_config_json_str, cJSON_Print(menu_config_json));
            // ESP_LOGE("menu config json str","menu_config_json_str:\n%s\n", menu_config_json_str);
            // cJSON_Delete(menu_config_json);
        }
    }
    nvs_write_str("food_menu_nvs", menu_config_json_str);    
    cJSON_Delete(menu_config_json);
}

char *menu_config_json_str_return(void)
{
    return menu_config_json_str;
}

void menu_modify_refresh_menu_config_json_str(char *current_menu_config_json_str)
{
    strcpy(menu_config_json_str, current_menu_config_json_str);
}
