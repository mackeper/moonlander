#ifdef ENABLE_RGB_MATRIX_FIRST_ANIMATION
RGB_MATRIX_EFFECT(first_animation)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool first_animation(effect_params_t *params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 16);
    uint16_t red = ((i * 17) + time) % 256;
    uint16_t green = ((i * 23) + time) % 256;
    uint16_t blue = ((i * 29) + time) % 256;
    rgb_matrix_set_color(i, red, green, blue);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // ENABLE_RGB_MATRIX_FIRST_ANIMATION
