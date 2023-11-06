#include "Count_zero.h"
#include "menu.h"
#include "PID.h"
#include "NTC_thermistor.h"
#include "buzzer.h"
// #include "ui_events.h"

QueueHandle_t cooking_time_remaining_Mailbox;				 // Queue handle of rest countdown time
QueueHandle_t countdown_state_Mailbox;						 // Queue handle of countdown state
QueueHandle_t handle_queue_Count_zero_cooking_timer_seconds; // Queue handle of countdown target time
QueueHandle_t handle_queue_Count_zero_temperature;
QueueHandle_t handle_countdown_approve_state;
QueueHandle_t handle_countdown_drop_approve;
QueueHandle_t handle_queue_force_heat_state;
QueueHandle_t handle_queue_force_heat_countdown;
QueueHandle_t handle_queue_real_time_PWM;

void countdownTask(void *pvParameters)
{
	// Initialize PID mode by reading PID mode from PID components.
	enum mode_select_state PID_mode = PID_mode_read();

	// Initialize countdown state queue by Writing stop into queue.
	enum timer_countdown_state current_countdown_state = Timer_Countdown_Stop;
	xQueueOverwrite(countdown_state_Mailbox, &current_countdown_state);

	// Initialize a target time from default menu into queue form menu components.
	int cooking_timer_seconds = menu_search_by_sequence(0).cooking_timer_seconds;
	count_zero_second_queue_write(cooking_timer_seconds);

	countdown_temperature_write_for_ui_events(menu_search_by_sequence(0).target_temperature);
	// Initialize by reading time while power on by esp_log_timestamp().
	uint current_time = esp_log_timestamp();
	uint previous_time = current_time;

	// 初始化设定温度，当前温度
	double SetTemperature = 0.0;
	double now_temperature = 0.0;

	// Initialize the rest time of countdown by set it to countdown target time.
	int cooking_time_remaining = cooking_timer_seconds;

	// 到达(设定温度-2℃)，才可以倒计时
	enum timer_preheat_approve_state current_countdown_approve_state = Timer_Preheat_Disapprove;

	countdown_approve_state_write(Timer_Preheat_Disapprove);
	countdown_drop_approve_write(Timer_Drop_Disapprove);

	timer_real_time_PWM_write(0.0);

	while (1)
	{
		current_countdown_state = read_countdown_start();
		cooking_timer_seconds = count_zero_second_queue_read();
		PID_mode = PID_mode_read();

		// SetTemperature = PID_set_temperature_read() - 273.15; //kelvin to celsius
		SetTemperature = countdown_temperature_read_for_ui_events() - 273.15;

		#if CONFIG_SIMULATED_TEMPERATURE
			now_temperature = NTC_thermistor_queue_read() - 173.15; // 模拟温度，比真正温度低了 100 摄氏度
		#else
			now_temperature = NTC_thermistor_queue_read() - 273.15; // 真实测温
			// now_temperature = 200;
		#endif

		if(now_temperature > (SetTemperature - 2))
		{
			current_countdown_approve_state = Timer_Preheat_Approve;
		}

		// current_time = esp_log_timestamp();
		if (current_countdown_state == Timer_Countdown_Start)
		{
			current_time = esp_log_timestamp();
			// printf("current_time: \n%ld\n", current_time);
			// countdown start
			if ((current_time - previous_time >= 1000) && (cooking_time_remaining > 0))
			{
				if(current_countdown_approve_state == Timer_Preheat_Approve)
				{
					if(countdown_drop_approve_read() == Timer_Drop_Approve)
					{
						cooking_time_remaining--;
						if(cooking_time_remaining == 0) // 倒计时总时长为0:0的情况
						{
							// cooking_time_remaining = 0;
							buzzer_occasion_queue_write(buzzer_countdown_over);
						}
					}
				}
				xQueueOverwrite(cooking_time_remaining_Mailbox, &cooking_time_remaining);	

				printf("cooking_time_remaining:%d\n", cooking_time_remaining);

				previous_time = current_time;
			}

			PID_set_temperature_write(countdown_temperature_read_for_ui_events()); // 发送自动操作设定温度给PID

			// press button for countdown stop or countdown time over or other PID mode convert
			if (cooking_time_remaining <= 0)
			{
				vTaskDelay(100 / portTICK_PERIOD_MS);
				cooking_timer_seconds = count_zero_second_queue_read();

				PID_mode = mode_null;
				PID_mode_write(PID_mode);

				current_countdown_state = Timer_Countdown_Stop;
				xQueueOverwrite(countdown_state_Mailbox, &current_countdown_state);

				current_countdown_approve_state = Timer_Preheat_Disapprove;
				// printf("disapprove countdown, remaining zero\n");
			}
			if (PID_mode != mode_timer)
			{
				current_countdown_state = Timer_Countdown_Stop;
				xQueueOverwrite(countdown_state_Mailbox, &current_countdown_state);

				current_countdown_approve_state = Timer_Preheat_Disapprove;
				// printf("disapprove countdown, other mode\n");
			}
			vTaskDelay(800 / portTICK_PERIOD_MS);
		}
		else
		{
			cooking_time_remaining = cooking_timer_seconds;

			current_countdown_approve_state = Timer_Preheat_Disapprove;
			// printf("disapprove countdown, not countdown mode\n");
		}
		countdown_approve_state_write(current_countdown_approve_state); // 发送自动操作倒计时批准
		vTaskDelay(200 / portTICK_PERIOD_MS);
	}
}

void timerForceHeatTask(void *pvParameters)
{
	// 自动模式强制加热倒计时
	int time_force_heat_countdown_time = menu_search_by_sequence(0).menu_force_heat_time;
	force_heat_countdown_queue_write(time_force_heat_countdown_time);

	// 自动模式强制加热状态
	enum timer_force_heat_state current_force_heat_state = Timer_No_Force_Heat;
	force_heat_state_write(current_force_heat_state);

	double SetTemperature = 0.0;
	double now_temperature = 0.0;

	// 读取自动模式设定温度
	SetTemperature = countdown_temperature_read_for_ui_events() - 273.15;

	// 读取自动模式实时温度
	#if CONFIG_SIMULATED_TEMPERATURE
		now_temperature = NTC_thermistor_queue_read() - 173.15; // 模拟温度，比真正温度低了 100 摄氏度
	#else
		now_temperature = NTC_thermistor_queue_read() - 273.15; // 真实测温
		// now_temperature = 200;
	#endif

	while(1)
	{
		SetTemperature = countdown_temperature_read_for_ui_events() - 273.15;
		now_temperature = NTC_thermistor_queue_read() - 273.15; // 真实测温
		
		time_force_heat_countdown_time = force_heat_countdown_queue_read();
		// printf("time_force_heat_countdown_time : %d\n", time_force_heat_countdown_time);
		if((countdown_drop_approve_read() == Timer_Drop_Approve) && ((now_temperature < (SetTemperature + Force_Heat_Over_Delta))) && (timer_real_time_PWM_read() < 255) && (time_force_heat_countdown_time != 0))
		{
			force_heat_state_write(Timer_Force_Heat);
			force_heat_countdown_queue_write((time_force_heat_countdown_time <= 0) ? 0 : --time_force_heat_countdown_time);
			// vTaskDelay(800 / portTICK_PERIOD_MS);
		}
		else
		{
			force_heat_state_write(Timer_No_Force_Heat);
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void countdown_init()
{
	cooking_time_remaining_Mailbox = xQueueCreate(1, sizeof(int));
	countdown_state_Mailbox = xQueueCreate(1, sizeof(enum timer_countdown_state));
	handle_queue_Count_zero_cooking_timer_seconds = xQueueCreate(1, sizeof(int));
	handle_queue_Count_zero_temperature = xQueueCreate(1, sizeof(double));
	handle_countdown_approve_state = xQueueCreate(1,sizeof(enum timer_preheat_approve_state));
	handle_countdown_drop_approve = xQueueCreate(1,sizeof(enum timer_drop_approve_state));
	handle_queue_force_heat_state = xQueueCreate(1,sizeof(enum timer_force_heat_state));
	handle_queue_force_heat_countdown = xQueueCreate(1, sizeof(int));
	handle_queue_real_time_PWM = xQueueCreate(1, sizeof(double));
	xTaskCreate(countdownTask, "countdownTask", 1024 * 6, NULL, 2, NULL);
	xTaskCreate(timerForceHeatTask, "timerForceHeatTask", 1024 * 6, NULL, 2, NULL);
}

void count_zero_second_queue_write(int second)
{
	xQueueOverwrite(handle_queue_Count_zero_cooking_timer_seconds, &second);
}

int count_zero_second_queue_read(void)
{
	int current_second;
	xQueuePeek(handle_queue_Count_zero_cooking_timer_seconds, &current_second, portMAX_DELAY);
	return current_second;
}

int menu_read_remaining_countdown(void)
{
	int cooking_time_remaining = 0;
	xQueuePeek(cooking_time_remaining_Mailbox, &cooking_time_remaining, 0);
	return cooking_time_remaining;
}

enum timer_countdown_state read_countdown_start(void)
{
	enum timer_countdown_state current_countdown_state = Timer_Countdown_Stop;
	xQueuePeek(countdown_state_Mailbox, &current_countdown_state, 1);
	return current_countdown_state;
}

void write_countdown_start(enum timer_countdown_state current_countdown_state)
{
	xQueueOverwrite(countdown_state_Mailbox, &current_countdown_state);
}

enum mode_select_state timer_start_button_event(void)
{
	enum timer_countdown_state current_countdown_state = read_countdown_start();

	enum mode_select_state PID_mode = PID_mode_read();

	if ((current_countdown_state == Timer_Countdown_Stop) || (PID_mode != mode_timer))
	{
		current_countdown_state = Timer_Countdown_Start;
		PID_mode = mode_timer;
	}
	else
	{
		current_countdown_state = Timer_Countdown_Stop;
		PID_mode = mode_null;
	}
	xQueueOverwrite(countdown_state_Mailbox, &current_countdown_state);
	PID_mode_write(PID_mode);
	return PID_mode;
}

void countdown_temperature_write_for_ui_events(double current_temperature)
{
	xQueueOverwrite(handle_queue_Count_zero_temperature, &current_temperature);
}

double countdown_temperature_read_for_ui_events(void)
{
	double current_temperature = 0.0;
	xQueuePeek(handle_queue_Count_zero_temperature, &current_temperature, 1);
	return current_temperature;
}

void countdown_state_Mailbox_write_stop_for_manual(void)
{
	enum timer_countdown_state current_countdown_state = Timer_Countdown_Stop;
	xQueueOverwrite(countdown_state_Mailbox, &current_countdown_state);
}

int Display_countdown_minute()
{
	int minute;
	minute = menu_read_remaining_countdown() / 60;
	return minute;
}

int Display_countdown_second()
{
	int second;
	second = menu_read_remaining_countdown() % 60;
	return second;
}

enum timer_preheat_approve_state countdown_approve_state_read(void)
{
	enum timer_preheat_approve_state current_countdown_approve_state = Timer_Preheat_Disapprove;
	xQueuePeek(handle_countdown_approve_state, &current_countdown_approve_state, 1);
	return current_countdown_approve_state;
}

void countdown_approve_state_write(enum timer_preheat_approve_state current_countdown_approve_state)
{
	xQueueOverwrite(handle_countdown_approve_state, &current_countdown_approve_state);
}

enum timer_drop_approve_state countdown_drop_approve_read(void)
{
	enum timer_drop_approve_state current_countdown_drop_approve = 0;
	xQueuePeek(handle_countdown_drop_approve, &current_countdown_drop_approve, 1);
	return current_countdown_drop_approve;
}

void countdown_drop_approve_write(enum timer_drop_approve_state current_countdown_drop_approve)
{
	xQueueOverwrite(handle_countdown_drop_approve, &current_countdown_drop_approve);
}

int force_heat_countdown_queue_read(void)
{
	int current_force_heat_countdown;
	xQueuePeek(handle_queue_force_heat_countdown, &current_force_heat_countdown, portMAX_DELAY);
	return current_force_heat_countdown;
}

void force_heat_countdown_queue_write(int current_force_heat_countdown)
{
	xQueueOverwrite(handle_queue_force_heat_countdown, &current_force_heat_countdown);
}

enum timer_force_heat_state force_heat_state_read(void)
{
	enum timer_force_heat_state current_force_heat_state = Timer_No_Force_Heat;
	xQueuePeek(handle_queue_force_heat_state, &current_force_heat_state, 1);
	return current_force_heat_state;
}

void force_heat_state_write(enum timer_force_heat_state current_force_heat_state)
{
	xQueueOverwrite(handle_queue_force_heat_state, &current_force_heat_state);
}

double timer_real_time_PWM_read(void)
{
    double current_timer_real_time_PWM = 0;
    xQueuePeek(handle_queue_real_time_PWM, &current_timer_real_time_PWM, 1);
    return current_timer_real_time_PWM;
}

esp_err_t timer_real_time_PWM_write(double current_timer_real_time_PWM)
{
    xQueueOverwrite(handle_queue_real_time_PWM, &current_timer_real_time_PWM);
    return ESP_OK;
}
