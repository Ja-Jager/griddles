idf_component_register(SRCS "PID.c"
                    INCLUDE_DIRS "."
                    REQUIRES "NTC_thermistor"
                                "timer_mode")
