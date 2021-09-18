#include <rogue.h>

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Entity* player;
Tile** map;

int main(void)
{
    Position start_pos;

    cursesSetup();
    srand(time(NULL));

    map = createMapTiles();
    start_pos = setupMap();
    player = createPlayer(start_pos);

    player = createPlayer(start_pos);
    mvaddch(player->pos.y, player->pos.x, player->ch);

    gameLoop();

    closeGame();

    return 0;
}