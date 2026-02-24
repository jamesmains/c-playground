#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/websocket.h>
#include "cJSON.h"
#include "player/network_player.h"
#include "player/player_input.h"
#include "engine.h"
#include "network.h"
#include "main.h"

// Global WebSocket handle
EMSCRIPTEN_WEBSOCKET_T ws;

// This only exists for the Web build
void send_position(float x, float y)
{
    unsigned short state;
    emscripten_websocket_get_ready_state(ws, &state);

    if (state == 1 && ctx.my_client_id != -1)
    {   
        cJSON *root = cJSON_CreateObject();
        cJSON_AddStringToObject(root, "type", "move");
        cJSON_AddNumberToObject(root, "id", ctx.my_client_id);
        cJSON_AddNumberToObject(root, "x", x);
        cJSON_AddNumberToObject(root, "y", y);

        char *out = cJSON_PrintUnformatted(root);
        emscripten_websocket_send_utf8_text(ws, out);
        free(out);
        cJSON_Delete(root);
    }
}

// Callback for receiving data from server
EM_BOOL on_message(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData) {
    cJSON *json = cJSON_Parse((char*)websocketEvent->data);
    if (json == NULL) return EM_FALSE;

    cJSON *type = cJSON_GetObjectItem(json, "type");

    if(strcmp(type->valuestring, "init") == 0){
        ctx.my_client_id = cJSON_GetObjectItemCaseSensitive(json,"id")->valueint;
    }
    else if(strcmp(type->valuestring, "move") == 0){
        int id = cJSON_GetObjectItemCaseSensitive(json,"id")->valueint;
        float x = cJSON_GetObjectItemCaseSensitive(json,"x")->valuedouble;
        float y = cJSON_GetObjectItemCaseSensitive(json,"y")->valuedouble;
        printf("Received move for ID %d: (%f, %f)\n", id, x, y);
        if(id != ctx.my_client_id && id >= 0 && id < 4) {
            // Todo: Need to check for map_id and see other notes about local player movement
            ctx.players[id].x = x;
            ctx.players[id].y = y;
        }
    }

    // Print to Browser Console (F12)
    printf("Raw Data: %s\n", websocketEvent->data);
    cJSON_Delete(json);
    return EM_TRUE;
}

void initialize_websocket() {
    // 1. Initialize WebSocket FIRST
    EmscriptenWebSocketCreateAttributes attr = { "ws://192.168.1.10:8001", NULL, EM_TRUE };
    ws = emscripten_websocket_new(&attr);
    emscripten_websocket_set_onmessage_callback(ws, NULL, on_message);
    
    // 2. Set the loop NEXT (This registers the timing with the browser)
    // We set the 3rd argument to 0 so it doesn't block execution here
    emscripten_set_main_loop(main_loop, 0, 0); 
}

#endif