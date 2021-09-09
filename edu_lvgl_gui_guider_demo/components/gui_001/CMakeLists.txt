file(GLOB_RECURSE SOURCES generated/*.c custom/*.c)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS ./generated ./generated/guider_customer_fonts ./generated/guider_fonts
                       ./custom ../ ../lvgl/src/lv_font
                       REQUIRES lvgl)