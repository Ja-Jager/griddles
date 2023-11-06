idf_component_register(SRCS "manual_mode.c"
                       INCLUDE_DIRS "."
                       REQUIRES "nvs_store" "PID" "buzzer"
                      )       