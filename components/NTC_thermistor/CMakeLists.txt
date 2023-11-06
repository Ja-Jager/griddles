idf_component_register(SRCS "NTC_thermistor.c"
                    INCLUDE_DIRS "."
                    REQUIRES "driver" "esp_adc" 
                    )