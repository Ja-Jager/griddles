#include "esp_check.h"

/**
 * @brief Start menu countdown
 * @param cooking_timer_seconds Cooking countdown in seconds
 * @return esp error code
 */
esp_err_t menu_start_countdown(int cooking_timer_seconds);

/**
 * @brief Read menu remaining countdown time
 * @return Remaining cooking countdown in seconds
 */
int menu_read_remaining_countdown(void);

