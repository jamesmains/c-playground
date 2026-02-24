#include "mongoose.h"
#include "cJSON.h"

static const char *s_listen_on = "ws://0.0.0.0:8001";
#define MAX_PLAYERS 4

int connected_players = 0;

// Handle events (connections, messages, etc.)
static void fn(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        // Upgrade all HTTP requests to WebSocket if server is not full, otherwise boot back with server full message
        if(connected_players < MAX_PLAYERS) {
            mg_ws_upgrade(c, (struct mg_http_message *) ev_data, NULL);
        }
        else {
            mg_http_reply(c, 503, "Content-Type: text/plain\r\n", "Server full. Try again later.");
        }

    } else if (ev == MG_EV_WS_OPEN) {
        int id = connected_players; // Unique connection ID
        connected_players++;
        printf("New player connected! ID: %d\n", id);

        // Notify the client of their ID
        char response[64];
        snprintf(response, sizeof(response), "{\"type\":\"init\", \"id\":%d}", id);
        mg_ws_send(c, response, strlen(response), WEBSOCKET_OP_TEXT);
    } else if (ev == MG_EV_WS_MSG) {
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        
        // Use .buf and .len to relay the message
        printf("Relaying: %.*s\n", (int) wm->data.len, wm->data.buf);

        for (struct mg_connection *t = c->mgr->conns; t != NULL; t = t->next) {
            if (t->is_websocket && t != c) {
                mg_ws_send(t, wm->data.buf, wm->data.len, WEBSOCKET_OP_TEXT);
            }
        }
    } else if (ev == MG_EV_CLOSE){
        if(c->is_websocket) {
            connected_players--;
            printf("Player disconnected. Remaining: %d\n", connected_players);
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