/**
 * @file menu.h
 * @author Hays Chan
 * @date 3 Feb 2023
 * @brief File containing definition of food menu
 */

#include "esp_check.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "cJSON.h"
#include "nvs_component.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <stdio.h>
#include <string.h>
#include "esp_log.h"

/**
 * @brief Structure for a food menu item, e.g. French Fries, nuggets, chicken.
 * @param menu_sequence The menu number. 菜单序列号, 第几个菜单
 * @param target_temperature_celsius The target temperature setting in celsius
 * @param cooking_timer_seconds The countdown timer of food cooking in seconds
 * @note menu_sequence should count from 0
 */
typedef struct food_menu_item_config_struct {
    int menu_sequence; /** The menu number. (第几个菜单). count from 0 */
    double target_temperature; /** The target temperature setting in celsius */
    char *target_temperature_unit; /** The unit of target temperature */
    int cooking_timer_seconds; /** The countdown timer of food cooking in seconds */
    char * menu_name; /* menu name, e.g. 炸鸡, 薯条 */
    int menu_force_heat_time;
} food_menu_item_config;

/**
 * @brief Start the cooking process of a menu, e.g. French Fries, nuggets, chicken.
 * @param menu Structure of food menu item configuration
 * @return esp error code
 */
esp_err_t menu_start_cooking(food_menu_item_config menu);

/**
 * @brief Create and store new menu in NVS
 * @param target_temperature_celsius The target temperature setting in celsius
 * @param cooking_timer_seconds The countdown timer of food cooking in seconds
 * @return Pointer of `food_menu_item_config`
 * @note Store as `food_menu_item_config` type in NVS
 */
esp_err_t menu_create(int target_temperature_celsius, int cooking_timer_seconds);

/**
 * @brief Can't search matching menu in NVS
 * @return Struct: `food_menu_item_config` The sequence of struct is -1, show exception
*/
food_menu_item_config NULL_menu(void);

/**
 * @brief Search menu in NVS
 * @note According to menu sequence written by customer, traverse all menu to find the matching menu and return its structure
 * @param menu_name :int, the sequence customer written
 * @return Struct: `food_menu_item_config`
 */
food_menu_item_config menu_search_by_sequence(int sequence);

/**
 * @brief Search menu in NVS
 * @note According to menu name written by customer, traverse all menu to find the matching menu and return its structure
 * @param menu_name :CHAR *, the name customer written
 * @return Struct: `food_menu_item_config`
 */
food_menu_item_config menu_search_by_name(char * menu_name);

/**
 * @brief Update menu roller
 * @note Use `lv_roller_set_options(ui_rlrParameters, opts, LV_ROLLER_MODE_NORMAL)`, 
 *          opts is a char [], options are seprated by newline
 * Should look like "炸鸡\n薯条\n牛肉\n鸡块\n麦乐鸡\n"
 * @return Char pointer (string)
 * @see https://forum.squareline.io/t/how-to-create-a-dynamic-roller-that-draws-options-from-a-source/852
 */
char *menu_roller_name_json_to_string(void);

/**
 * @brief Overwrite existing menu in NVS
 * @param target_temperature_celsius The target temperature setting in celsius
 * @param cooking_timer_seconds The countdown timer of food cooking in seconds
 * @return esp error code
 */
esp_err_t menu_overwrite(int target_temperature_celsius, int cooking_timer_seconds);

/**
 * @brief Read menu json from nvs
 * @note Writes to global cJSON variable `menu_config_json`
 * @return esp error code
 */
esp_err_t menu_read_json_nvs(char *key);

/**
 * @brief Write latest json to nvs
 * @param key Key for food menu JSON in nvs, e.g. "food_menu"
 * @note Writes global cJSON variable `menu_config_json` to nvs
 * @return esp error code
 */
esp_err_t menu_write_json_nvs(char * key);

/**
* @brief Test mune read NVS when first power on
* @note  If the munu's json string exits, write into menu_config_json. If failed, default menu json string write into nvs and menu_config_json.
* @return ESP_OK:succeeded
*/
esp_err_t menu_test_for_first_power_on(char *key);


/**
* @brief Convert temperature from int to char * with ° degree symbol
* @param temperature int type. Accepts celsius and fahrenheit.
* @return char *. e.g. input 180, output "180°"
*/
char * temperature_int_to_str(int temperature);

/**
* @brief Convert second from int to char * with : symbol
* @param second int type. 
* @return char *. e.g. input 75, output "75°"
*/
char * time_int_seconds_to_str(int second);

// char *menu_name, int temperature, char *unit, int seconds
/**
 * @brief Create a menu which is consisted of menu name, temperature, temperature unit and countdown.
 * @param root A pointer to string which is the json string. 
 * @param menu_name Name of the menu created newly.
 * @param temperature Temperature of the menu created newly.
 * @param unit Temperature unit of the menu created newly.
 * @param seconds Seconds of the menu created newly.
 * @return type: esp_err_t ESP_OK
*/ 
esp_err_t create_menu(food_menu_item_config menu_create);

/**
 * @brief Delete a existing menu which is consisted of menu name, temperature, temperature unit and countdown.
 * @param root A pointer to string which is the json string. 
 * @param menu_name Name of the menu to be deleted.
 * @return type: esp_err_t ESP_OK
*/
esp_err_t delete_menu_by_name(char *name);

// char *name, int temperature, char *unit, int seconds
/**
 * @brief Modify a existing menu which is consisted of menu name, temperature, temperature unit and countdown.
 * @param root A pointer to string which is the json string. 
 * @param menu_name Name of the menu to be modified.
 * @param temperature Temperature of the menu to be modified.
 * @param unit Temperature unit of the menu to be modified.
 * @param seconds Seconds of the menu to be modified.
 * @return type: esp_err_t ESP_OK
*/
void modify_menu_by_struct(food_menu_item_config menu_modify);

char *menu_config_json_str_return(void);

void menu_modify_refresh_menu_config_json_str(char *current_menu_config_json_str);

