#ifdef ENABLE_RGB_MATRIX_BREATHING_RANDOM
RGB_MATRIX_EFFECT(breathing_random_anim)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t g_s_can_change_color = 0;
static uint8_t g_s_current = 0;
static uint8_t g_s_int[3] = {1, 0, 0};

static bool breathing_random(effect_params_t *params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  uint8_t change_color_breakpoint = 10;
  uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 16);
  uint8_t sin_time = sin8(time);

  if (sin_time < change_color_breakpoint && g_s_can_change_color) {
    g_s_int[g_s_current] = 0;
    g_s_current = (g_s_current + 1) % 3;
    g_s_int[g_s_current] = 1;
    g_s_can_change_color = 0;
  }

  if (sin_time > change_color_breakpoint) {
    g_s_can_change_color = 1;
  }

  for (uint8_t i = led_min; i < led_max; i++) {
    uint8_t red = sin_time * g_s_int[0];
    uint8_t green = sin_time * g_s_int[1];
    uint8_t blue = sin_time * g_s_int[2];
    rgb_matrix_set_color(i, red, green, blue);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // ENABLE_RGB_MATRIX_BREATING_RANDOM
