idf_component_register(SRCS "menu.c" "menu_countdown.c"
                       INCLUDE_DIRS "."
                       REQUIRES nvs_store "json"
                      )       