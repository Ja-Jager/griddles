#include <PID.h>

QueueHandle_t handle_queue_PID;
QueueHandle_t handle_queue_PID_set_temperature;
QueueHandle_t handle_queue_PID_mode_state;

PID_structure pid_set;

double PWM_var = 0; // 占空比
double dError = 0;
double Error = 0;
double SumError = 0;
double now_temperature = 0;
double PrevError = 0;
/*
 PID 计算
 */

void PID_calculate_init() // 不改变比例、积分、微分常数、死区，第一次读取到的值赋予所有偏差
{
    pid_set.SetTemperature = 449.82;                      // 默认鸡块油温(K)
    // pid_set.SetTemperature = 180;                       // 默认鸡块油温
    pid_set.Proportion = (double)Proportion_Coefficient;        // 比例常数
    pid_set.Integral = (double)Integral_Coefficient;            // 积分常数
    pid_set.Derivative = (double)Derivative_Coefficient;        // 微分常数
    pid_set.umin = pid_set.SetTemperature - Umin_range; // 死区
    pid_set.FirstError = 1;                             // The number is not important. Init only. Do not use 0.
    pid_set.LastError = pid_set.FirstError;
    pid_set.PrevError = pid_set.FirstError;
    pid_set.SumError = pid_set.FirstError;

    PID_queue_init();
    PID_set_temperature_write(pid_set.SetTemperature); // 队列里写入默认设定温度

    xTaskCreate(task_pid_calculate, "PIDCalculateTask", 1024 * 4, NULL, 2, NULL);
}

void task_pid_calculate(void *ptr) // 融化参数
{
    
    // int cooking_time_remaining = 0; // 倒计时剩余时间

    while (1)
    {
        // double SumError;
        enum mode_select_state current_PID_mode = PID_mode_read();

        pid_set.SetTemperature = PID_set_temperature_read() - 273.15; //kelvin to celsius
        // printf("%.2f\n",pid_set.SetTemperature);
        pid_set.umin = pid_set.SetTemperature - Umin_range;
        // ESP_LOGI("Set Temperature", "target Temperature celsius = %.2f°C", pid_set.SetTemperature);

        #if CONFIG_SIMULATED_TEMPERATURE
			now_temperature = NTC_thermistor_queue_read() - 173.15; // 办公室测温
        #else
			now_temperature = NTC_thermistor_queue_read() - 273.15; // 真实测温
            // now_temperature = 200;
		#endif

        // ESP_LOGI("Now Temperature", "now Temperature = %.2f°C", now_temperature); //kelvin to celsius
        Error = pid_set.SetTemperature - now_temperature; // 先计算偏差
        
        // printf("SumError:%.2f\n",SumError);  
        
        if (isnan(Error))
        {
            SumError = 0;
        }
        else
        {
            SumError = SumError + Error;
        }
        
        if ((SumError >= SumError_threshold) || (now_temperature <= pid_set.SetTemperature - 2))
        {
            SumError = SumError_threshold;
        }
        if (SumError <= -SumError_threshold)
        {
            SumError = (-1)*SumError_threshold;
        }
        // printf("Error:%.2f\n",Error);
        // printf("SumError:%.2f\n",SumError);
        
        dError = Error - PrevError; // 对偏差微分
        PrevError = Error;
        // printf("dError:%.2f\n",dError);
        if ((current_PID_mode == mode_timer) || (current_PID_mode == mode_manual))
        {
            if(now_temperature > pid_set.SetTemperature)
            {
                PWM_var = Duty_MIN;
            }
            else if(now_temperature <= pid_set.SetTemperature - 5)
            {
                PWM_var = Duty_MAX;
            }  
        }
        if ((now_temperature > pid_set.SetTemperature) || (current_PID_mode == mode_null))
        {
            PWM_var = Duty_MIN;
            // ESP_LOGI("Set Temperature", "Countdown stop\n");
        }
        
        if (PWM_var >= Duty_MAX)
        {
            PWM_var = Duty_MAX;
        }
        else if (PWM_var <= Duty_MIN)
        {
            PWM_var = Duty_MIN;
        }
        PID_queue_write(PWM_var);
        // ESP_LOGI("PWM_var", "PWM_var = %.2f%%", (float) PWM_var/255*100);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// API接口
esp_err_t PID_queue_init()
{
    handle_queue_PID = xQueueCreate(1, sizeof(int));
    handle_queue_PID_set_temperature = xQueueCreate(1, sizeof(double));
    handle_queue_PID_mode_state = xQueueCreate(1, sizeof(enum mode_select_state));
    return ESP_OK;
}

// read
int PID_queue_read(void)
{
    int current_duty = 0;
    xQueuePeek(handle_queue_PID, &current_duty, 1);
    return current_duty;
}

// write
esp_err_t PID_queue_write(int duty)
{
    xQueueOverwrite(handle_queue_PID, &duty);
    return ESP_OK;
}

double PID_set_temperature_read(void)
{
    double set_temperature = 0;
    xQueuePeek(handle_queue_PID_set_temperature, &set_temperature, 1);
    return set_temperature;
}

esp_err_t PID_set_temperature_write(double set_temperature)
{
    xQueueOverwrite(handle_queue_PID_set_temperature, &set_temperature);
    return ESP_OK;
}

enum mode_select_state PID_mode_read(void)
{
    enum mode_select_state current_PID_mode = mode_null;
    xQueuePeek(handle_queue_PID_mode_state, &current_PID_mode, 1);
    return current_PID_mode;
}

esp_err_t PID_mode_write(enum mode_select_state mode_state)
{
    xQueueOverwrite(handle_queue_PID_mode_state, &mode_state);
    return ESP_OK;
}
