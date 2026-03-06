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
    // Handle player input
    input_loop();

    // Todo: Add physics and collision here before submitting the change
    // |-> Needs to lerp smoothly
#ifdef __EMSCRIPTEN__
            send_position();
#endif
    // --- Rendering ---
    SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255); // Background
    SDL_RenderClear(renderer);

    // Draw all players in the array
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect rect = {(int)ctx.shared.players[i].x, (int)ctx.shared.players[i].y, ctx.shared.players[i].w, ctx.shared.players[i].h};
        SDL_SetRenderDrawColor(renderer, ctx.shared.players[i].color.r, ctx.shared.players[i].color.g, ctx.shared.players[i].color.b, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}
