#include <pebble.h>
#include "communication.h"
#include "vibrations.h"
  
// Key values for AppMessage Dictionary
enum {
	PATTERN_KEY = 0
};
 
//received a request to play a vibration pattern
static void in_received_handler(DictionaryIterator *received, void *context) {
  Tuple *tuple;
	
	tuple = dict_find(received, PATTERN_KEY);
	if(tuple) {
    int pattern = (int)tuple->value->uint32;
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Status: %d", pattern); 
    play_pattern(pattern);
	}
	
}

static void in_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Dropped!");
}
 
static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Failed to Send!");
}

void init_communication()
{
  // Register message handlers
  app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_register_outbox_failed(out_failed_handler);
  
  // Init buffers
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

//input from user => send to mobile
/*
void send_message(uint8_t length, uint8_t *message) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  if (iter == NULL) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "null iter");
    return;
  }
  Tuplet tuple = (message == NULL)
                      ? TupletInteger(0, 0)
                      : TupletBytes(0, message, length);
  dict_write_tuplet(iter, &tuple);
  dict_write_end(iter);
 
  app_message_outbox_send();
  return;
}
*/