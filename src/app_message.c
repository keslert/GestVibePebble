#include <pebble.h>
#include "communication.h"
#include "vibrations.h"
  
Window *window;	

void init(void) {
	window = window_create();
	window_stack_push(window, true);
		
  init_communication();
	init_vibrations();
}

void deinit(void) {
	app_message_deregister_callbacks();
	window_destroy(window);
}

int main( void ) {
	init();
	app_event_loop();
	deinit();
}