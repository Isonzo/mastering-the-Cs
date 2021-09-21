#include <rogue.h>

bool cursesSetup(void)
{
    initscr();
    noecho();
    curs_set(0);

    if (has_colors())
    {
        start_color();

        init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);

        return true;
    }
    else
    {
        mvprintw(20, 50, "Your system doesn't support colors, come back when you have top of the line tech (or a different terminal).");
        getch();
        return false;
    }
}

void gameLoop(void)
{
    int ch;

    makeFOV(player);
    drawEverything();

    while ((ch = getch()))
    {
        if (ch == 'q')
        {
            break;
        }

        handleInput(ch);
        drawEverything();
    }
}

void closeGame(void)
{
    endwin();
    free(player);
}