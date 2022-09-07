#include "moonlander.h"

extern bool is_launching;
extern keyboard_config_t keyboard_config;

layer_state_t layer_state_set_kb(layer_state_t state) {
    if (is_launching || !keyboard_config.led_level) return state;
    state = layer_state_set_user(state);
    bool LED_1 = false;
    bool LED_2 = false;
    bool LED_3 = false;
    bool LED_4 = false;
    bool LED_5 = false;
    bool LED_6 = false;

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 1:
            LED_1 = true;
            break;
        case 2:
            LED_2 = true;
            break;
        case 3:
            LED_3 = true;
            break;
        case 4:
            LED_4 = true;
            break;
        case 5:
            LED_5 = true;
            break;
        case 6:
            LED_5 = true;
            break;
        default:
            break;
    }

    ML_LED_1(LED_1);
    ML_LED_2(LED_2);
    ML_LED_3(LED_3);
    ML_LED_4(LED_4);
    ML_LED_5(LED_5);
    ML_LED_6(LED_6);

    return state;
}
