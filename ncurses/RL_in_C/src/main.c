#include <rogue.h>

Entity* player;

int main(void)
{
    cursesSetup();

    Position start_pos = {10, 20};
    player = createPlayer(start_pos);

    player = createPlayer(start_pos);
    mvaddch(player->pos.y, player->pos.x, player->ch);

    gameLoop();

    closeGame();

    return 0;
}