idf_component_register(SRCS "pcf8575_button_heat_mode.c"
                    INCLUDE_DIRS "."
                    REQUIRES PID manual_mode timer_mode pcf8575)
