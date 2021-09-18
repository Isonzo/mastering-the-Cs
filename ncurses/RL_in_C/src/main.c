#include <rogue.h>

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Entity* player;
Tile** map;

int main(void)
{
    cursesSetup();

    Position start_pos = {10, 20};
    player = createPlayer(start_pos);
    map = createMapTiles();

    player = createPlayer(start_pos);
    mvaddch(player->pos.y, player->pos.x, player->ch);

    gameLoop();

    closeGame();

    return 0;
}