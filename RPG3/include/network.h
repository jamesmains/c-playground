#ifndef NETWORK_H
#define NETWORK_H

#include <emscripten/websocket.h>

struct GameContext; 
typedef struct GameContext GameContext;

struct EmscriptenWebSocketMessageEvent; 
typedef struct EmscriptenWebSocketMessageEvent EmscriptenWebSocketMessageEvent;

void send_position(float x, float y);
EM_BOOL on_message(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData);
void initialize_websocket();
#endif