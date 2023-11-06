# ESP-RELAY-SOFTWARE-PWM

1. 声明一个结构体配置初始化参数并初始化

``` c
softPwm_t softpwm=
{
    .PWMPin = 19,
    .freq = 0.2,
};

```

2. 调用 softpwm_init(&softpwm)
