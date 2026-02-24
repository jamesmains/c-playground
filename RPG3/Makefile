# --- Setup ---
CC = gcc
EMCC = emcc
# -Iinclude and -Ilib tell the compiler to look in those folders for .h files
CFLAGS = -Wall -g -Iinclude -Ilib

DESKTOP_FLAGS = $(shell sdl2-config --cflags --libs)
WASM_FLAGS = -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -o index.html -lwebsocket.js

# --- New File Paths ---
# We split files into Desktop/Web specific lists
COMMON_SRC = lib/cJSON.c src/player/network_player.c src/network.c src/engine.c
CLIENT_SRC = src/main.c src/player/player_input.c $(COMMON_SRC)
SERVER_SRC = src/server.c lib/mongoose.c lib/cJSON.c

TARGET_BIN = rpg_desktop
SERVER_BIN = rpg_server

# --- Rules ---

all: desktop server

# Build the Linux Desktop Game
desktop: $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(CLIENT_SRC) $(DESKTOP_FLAGS) -o $(TARGET_BIN)
	@echo "\nRPG3 [Desktop]\n✓ Desktop Build Complete"

# Build the Web WASM Game
web: $(CLIENT_SRC)
	$(EMCC) $(CFLAGS) $(CLIENT_SRC) $(WASM_FLAGS)
	@echo "\nRPG3 [Web]\n✓ Web Build Complete"

# Build the Dedicated Server
server: $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) -o $(SERVER_BIN) -lm
	@echo "\nRPG3 [Server]\n✓ Server Build Complete"

clean:
	rm -f $(TARGET_BIN) $(SERVER_BIN) index.html index.js index.wasm
	@echo "\nRPG3 [Clean]\n🧹 Folder cleaned"

serve:
	@echo "\nRPG3 [Serve]\n🚀 Starting local server at http://localhost:8000"
	python3 -m http.server 8000