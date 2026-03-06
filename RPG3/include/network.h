#ifndef NETWORK_H
#define NETWORK_H

#ifdef __EMSCRIPTEN__
    #include <emscripten/websocket.h>
#endif

struct GameContext; 
typedef struct GameContext GameContext;

struct EmscriptenWebSocketMessageEvent; 
typedef struct EmscriptenWebSocketMessageEvent EmscriptenWebSocketMessageEvent;

void send_position();
EM_BOOL on_message(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData);
void initialize_websocket();
#endif