#include "mongoose.h"
#include "cJSON.h"
#include "../include/common.h"

static const char *s_listen_on = "ws://0.0.0.0:8001";

SharedContext server_ctx;

// Handle events (connections, messages, etc.)
static void fn(struct mg_connection *c, int ev, void *ev_data) {

    // CLIENT INIT ATTEMPT
    if (ev == MG_EV_HTTP_MSG) {
        int availableIndex = -1;
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            availableIndex = server_ctx.players[i].active == 0 ? i : -1;
            if (availableIndex != -1)
                break;
        }
        // Upgrade all HTTP requests to WebSocket if server is not full, otherwise boot back with server full message
        if(availableIndex != -1) {
            mg_ws_upgrade(c, (struct mg_http_message *) ev_data, NULL);
        }
        else {
            mg_http_reply(c, 503, "Content-Type: text/plain\r\n", "Server full. Try again later.");
        }

    } 
    // PLAYER CONNECT
    else if (ev == MG_EV_WS_OPEN) {
        int availableIndex = -1;
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            availableIndex = server_ctx.players[i].active == 0 ? i : -1;
            if (availableIndex != -1)
                break;
        }
        int id = availableIndex; // Unique connection ID
        c->fn_data = (void *)(uintptr_t)availableIndex;

        server_ctx.players[availableIndex].active = 1;
        server_ctx.players[availableIndex].id = availableIndex;

        // Notify the client of their ID
        char response[64];
        snprintf(response, sizeof(response), "{\"type\":\"init\", \"id\":%d}", id);
        mg_ws_send(c, response, strlen(response), WEBSOCKET_OP_TEXT);
        printf("New player connected! ID: %d\n", id);
    } 
    // PLAYER ACTION
    else if (ev == MG_EV_WS_MSG) {
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        
        // Use .buf and .len to relay the message
        printf("Relaying: %.*s\n", (int) wm->data.len, wm->data.buf);

        for (struct mg_connection *t = c->mgr->conns; t != NULL; t = t->next) {
            if (t->is_websocket && t != c) {
                mg_ws_send(t, wm->data.buf, wm->data.len, WEBSOCKET_OP_TEXT);
            }
        }
    } 
    // PLAYER DISCONNECT
    else if (ev == MG_EV_CLOSE){
        if(c->is_websocket && c->fn_data != NULL) {
            int id = (int)(uintptr_t)c->fn_data;

            server_ctx.players[id].active = 0;

            char leave_msg[64];
            snprintf(leave_msg, sizeof(leave_msg), "{\"type\":\"leave\", \"id\":%d}", id);
            
            for (struct mg_connection *t = c->mgr->conns; t != NULL; t = t->next) {
                if (t->is_websocket && t != c) {
                    mg_ws_send(t, leave_msg, strlen(leave_msg), WEBSOCKET_OP_TEXT);
                }
            }
        }
    }
}

int main(void){
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    printf("Starting RPG3 Server on %s\n", s_listen_on);
    mg_http_listen(&mgr, s_listen_on, fn, NULL);

    for (;;) mg_mgr_poll(&mgr, 1000); // main server loop

    mg_mgr_free(&mgr);
    return 0;
}