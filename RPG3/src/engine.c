#include "engine.h"
#include "network.h"
#include "player/network_player.h"
#include "player/player_input.h"
#include "main.h"

#include <SDL2/SDL.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void initialize_engine()
{
    // 3. Create the window LAST
    // Now that the main loop is registered, SDL can safely set VSync/Timing
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
}
void main_loop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            ctx.running = 0;

        // Make sure it's an actual key press event before doing anything... why are we not doing this outside?
    if (event.type == SDL_KEYDOWN)
    {
        handle_input(&ctx.players[ctx.my_client_id], &event);
    }

    // Todo: Add physics and collision here before submitting the change
    // |-> Needs to lerp smoothly
#ifdef __EMSCRIPTEN__
            send_position(ctx.players[ctx.my_client_id].x, ctx.players[ctx.my_client_id].y);
#endif
        }
    // --- Rendering ---
    SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255); // Background
    SDL_RenderClear(renderer);

    // Draw all players in the array
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect rect = {(int)ctx.players[i].x, (int)ctx.players[i].y, ctx.players[i].w, ctx.players[i].h};
        SDL_SetRenderDrawColor(renderer, ctx.players[i].color.r, ctx.players[i].color.g, ctx.players[i].color.b, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}
