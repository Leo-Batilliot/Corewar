/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** simulation_main
*/

#include "corewar.h"

int events(sfRenderWindow *win, simulation_t *sim)
{
    sfEvent event;

    (void) sim;
    while (sfRenderWindow_pollEvent(win, &event)) {
        if ((event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape) ||
            event.type == sfEvtClosed)
            sfRenderWindow_close(win);
    }
    return 0;
}

int simulation_main(sfRenderWindow *win, simulation_t *sim)
{
    if (!sim || !win)
        return 84;
    events(win, sim);
    return 0;
}