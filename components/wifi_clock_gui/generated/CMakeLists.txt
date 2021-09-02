if(ESP_PLATFORM)

idf_component_register(SRCS *.c
                       INCLUDE_DIRS . ./generated 
                       REQUIRES lvgl)

else()
    message(FATAL_ERROR "LVGL LV: ESP_PLATFORM is not defined. Try reinstalling ESP-IDF.")
endif()
