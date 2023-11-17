idf_component_register(SRCS "Max6675.c" "spi_mod.c"
                    INCLUDE_DIRS "."
                    REQUIRES nvs_store driver)
