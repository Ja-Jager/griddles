#include "manual_mode.h"
// #include "encoder.h"
// #include "ui_events.c"
// #include "main.c" 
#include "PID.h"
// #include "NTC_thermistor.h"
#include "Max6675.h"
#include "buzzer.h"

QueueHandle_t manual_start_state_Mailbox; // 倒计时开始
QueueHandle_t handle_queue_manual_countdown_time;
QueueHandle_t handle_queue_manual_countdown_rest_time;
QueueHandle_t handle_manual_approve_state;
QueueHandle_t handle_manual_drop_approve;

void manual_mode_countdown_Task(void *pvParam)
{
	uint current_time = esp_log_timestamp();
	uint previous_time = current_time;

	int manual_countdown_time = 180;
	manual_countdown_time_write(manual_countdown_time);

	int manual_countdown_rest_time = 180;
	manual_countdown_rest_time_write(manual_countdown_rest_time);

	enum manual_countdown_state current_manual_state = manual_countdown_stop;
	xQueueOverwrite(manual_start_state_Mailbox, &current_manual_state);

	enum mode_select_state current_PID_mode = mode_null;

	// 不批准手动操作倒计时（初始化）
	enum manual_preheat_approve_state current_manual_approve_state = manual_preheat_disapprove;

	write_manual_drop_approve(manual_drop_approve);

	double SetTemperature = 0.0;
	double now_temperature = 0.0;

	while (1)
	{
		current_PID_mode = PID_mode_read();

		current_manual_state = manual_mode_start_mailbox_read();

		// 手动操作设定温度
		// vTaskDelay(5 / portTICK_PERIOD_MS); 
		SetTemperature = PID_set_temperature_read() - 273.15;
		
		#if CONFIG_SIMULATED_TEMPERATURE
			now_temperature = NTC_thermistor_queue_read() - 173.15;
		#else
			now_temperature = NTC_thermistor_queue_read() - 273.15; // 真实测温
			// now_temperature = 200;
		#endif

		if(now_temperature > (SetTemperature - 2)) //批准手动操作倒计时
		{
			current_manual_approve_state = manual_preheat_approve;
		}

		if(current_manual_state == manual_countdown_start) // 手动操作开始倒计时
		{
			current_time = esp_log_timestamp();
			if ((current_time - previous_time >= 1000)) // 经过一秒
			{
				if(current_manual_approve_state == manual_preheat_approve) // 允许倒计时
				{
					if(read_manual_drop_approve() == manual_drop_approve)
					{
						manual_countdown_rest_time -= 1;
						if(manual_countdown_time == 0)
						{
							manual_countdown_rest_time = 0;
						}
						if(manual_countdown_rest_time == 0) // 倒计时总时长为0:0的情况
						{
							if(manual_countdown_time != 0) // 倒计时总时长为0:0的情况
							{
								buzzer_occasion_queue_write(buzzer_countdown_over);
							}
						}
					}
				}
				previous_time = current_time;
				printf("rest time = %d\n", manual_countdown_rest_time);
				manual_countdown_rest_time_write(manual_countdown_rest_time);
			}
			if ((manual_countdown_rest_time <= 0) && (manual_countdown_time != 0)) // 除倒计时总时长为0:0外，时间走完的情况
			{
				current_PID_mode = mode_null;
				PID_mode_write(current_PID_mode);
				vTaskDelay(100 / portTICK_PERIOD_MS);

				current_manual_state = manual_countdown_stop;
				xQueueOverwrite(manual_start_state_Mailbox, &current_manual_state);

				current_manual_approve_state = manual_preheat_disapprove;
			}
			if (current_PID_mode != mode_manual)
			{
				current_manual_state = manual_countdown_stop;
				xQueueOverwrite(manual_start_state_Mailbox, &current_manual_state);

				current_manual_approve_state = manual_preheat_disapprove;
			}
			vTaskDelay(800 / portTICK_PERIOD_MS);
		}
		else
		{
			// 设定时间赋于倒计时时间
			manual_countdown_time = manual_countdown_time_read();
			manual_countdown_rest_time = manual_countdown_time;

			// 默认倒计时状态为停止
			current_manual_state = manual_countdown_stop;
			xQueueOverwrite(manual_start_state_Mailbox, &current_manual_state);

			// 默认为不允许倒计时
			current_manual_approve_state = manual_preheat_disapprove;
		}
		write_manual_approve_state(current_manual_approve_state);
		vTaskDelay(200 / portTICK_PERIOD_MS);
		
	}
}

void manual_mode_init()
{
	manual_start_state_Mailbox = xQueueCreate(1, sizeof(enum manual_countdown_state));
	handle_queue_manual_countdown_time = xQueueCreate(1, sizeof(int));
	handle_queue_manual_countdown_rest_time = xQueueCreate(1, sizeof(int));
	handle_manual_approve_state = xQueueCreate(1, sizeof(enum manual_preheat_approve_state));
	handle_manual_drop_approve = xQueueCreate(1, sizeof(enum manual_drop_approve_state));
	xTaskCreate(manual_mode_countdown_Task, "manual mode Task", 1024 * 6, NULL, 2, NULL);
}

enum mode_select_state manual_mode_start_mailbox_write(void)
{
	enum mode_select_state PID_mode = PID_mode_read();

	enum manual_countdown_state manual_start_state = manual_mode_start_mailbox_read();

	if ((manual_start_state == manual_countdown_stop) || (PID_mode != mode_manual))
	{
		manual_start_state = manual_countdown_start;
		PID_mode = mode_manual;	
	}
	else
	{
		manual_start_state = manual_countdown_stop;
		PID_mode = mode_null;
	}

	xQueueOverwrite(manual_start_state_Mailbox, &manual_start_state);
	PID_mode_write(PID_mode);

	return PID_mode;
}

enum manual_countdown_state manual_mode_start_mailbox_read(void)
{
	enum manual_countdown_state manual_start_state = manual_countdown_stop;
	xQueuePeek(manual_start_state_Mailbox, &manual_start_state, 1);
	return manual_start_state;
}

int manual_countdown_time_read(void)
{
	int current_time = 0;
	xQueuePeek(handle_queue_manual_countdown_time, &current_time, 1);
	return current_time;
}

void manual_countdown_time_write(int current_time)
{
	xQueueOverwrite(handle_queue_manual_countdown_time, &current_time);
}

int manual_countdown_rest_time_read(void)
{
	int current_rest_time = 0;
	xQueuePeek(handle_queue_manual_countdown_rest_time, &current_rest_time, 1);
	return current_rest_time;
}

void manual_countdown_rest_time_write(int current_rest_time)
{
	xQueueOverwrite(handle_queue_manual_countdown_rest_time, &current_rest_time);
}

int manual_countdown_rest_time_minute(int current_rest_time)
{
	int current_rest_time_minute = 0;
	current_rest_time_minute = current_rest_time / 60;
	return current_rest_time_minute;
}

int manual_countdown_rest_time_second(int current_rest_time)
{
	int current_rest_time_second = 0;
	current_rest_time_second = current_rest_time % 60;
	return current_rest_time_second;
}

enum manual_preheat_approve_state read_manual_approve_state(void)
{
	enum manual_preheat_approve_state current_manual_approve_state = manual_preheat_disapprove;
	xQueuePeek(handle_manual_approve_state, &current_manual_approve_state, 1);
	return current_manual_approve_state;
}

void write_manual_approve_state(enum manual_preheat_approve_state current_manual_approve_state)
{
	xQueueOverwrite(handle_manual_approve_state, &current_manual_approve_state);
}

enum manual_drop_approve_state read_manual_drop_approve(void)
{
	enum manual_drop_approve_state current_manual_drop_approve = 0;
	xQueuePeek(handle_manual_drop_approve, &current_manual_drop_approve, 1);
	return current_manual_drop_approve;
}

void write_manual_drop_approve(enum manual_drop_approve_state current_manual_drop_approve)
{
	xQueueOverwrite(handle_manual_drop_approve, &current_manual_drop_approve);
}
