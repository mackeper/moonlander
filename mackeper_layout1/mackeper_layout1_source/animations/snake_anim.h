#ifdef ENABLE_RGB_MATRIX_FIRST_ANIMATION
RGB_MATRIX_EFFECT(snake_animation)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool snake_animation(effect_params_t *params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  rgb_matrix_map_row_column_to_led()
  uint16_t max_tick = 65535 / rgb_matrix_config.speed;
  for (uint8_t i = led_min; i < led_max; i++) {
    uint16_t tick = max_tick;
    // Reverse search to find most recent key hit
    for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
        if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
            tick = g_last_hit_tracker.tick[j];
            break;
        }
    }
    uint16_t red = ((i * 17) + time) % 256;
    uint16_t green = ((i * 23) + time) % 256;
    uint16_t blue = ((i * 29) + time) % 256;
    rgb_matrix_set_color(i, red, green, blue);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // ENABLE_RGB_MATRIX_FIRST_ANIMATION
