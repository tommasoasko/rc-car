idf_component_register(
    SRCS "led.c"
    INCLUDE_DIRS "include"
    # questo serve per linkare moduli da compilare prima di questo
    PRIV_REQUIRES 
        freertos
        driver
)