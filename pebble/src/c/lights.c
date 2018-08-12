#include <pebble.h>

static Window *s_window;
static TextLayer *s_text_layer;

typedef struct light {
    char* name;
    int code;
} light;

static light light_codes[5] = {
   {"Living Room Lamp", 2},
   {"Office Lights", 1},
   {"Bedroom Lamp", 4},
   {"Bedroom Lights", 3},
   {"Office Lamp", 0}
};

static int counter = 0;

static void send_request(int light, int state) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  if (!iter) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed to send messgae");
    // Error creating outbound message
    return;
  }

  dict_write_int(iter, 10, &light, sizeof(int), true);
  dict_write_int(iter, 11, &state, sizeof(int), true);
  dict_write_end(iter);

  app_message_outbox_send();
}


static void prv_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (counter < 4) counter++;
  else counter = 0;

  text_layer_set_text(s_text_layer, light_codes[counter].name);
}

static void prv_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_request(light_codes[counter].code, 1);
}

static void prv_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_request(light_codes[counter].code, 0);
}

static void prv_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, prv_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, prv_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, prv_down_click_handler);
}

static void prv_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_text_layer = text_layer_create(GRect(0, 72, bounds.size.w, 25));
  text_layer_set_text(s_text_layer, light_codes[counter].name);
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

static void prv_window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
}

static void prv_init(void) {
  s_window = window_create();
  window_set_click_config_provider(s_window, prv_click_config_provider);
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = prv_window_load,
    .unload = prv_window_unload,
  });
  const bool animated = true;
  window_stack_push(s_window, animated);
  
  app_message_open(64, 64);
}

static void prv_deinit(void) {
  window_destroy(s_window);
}

int main(void) {
  prv_init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", s_window);

  app_event_loop();
  prv_deinit();
}
