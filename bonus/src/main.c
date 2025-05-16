/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** main
*/

#include "op.h"
#include "corewar.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// name :   not_enough_arguments
// args :   args, ac
// use :    check if we have not enought args
static int not_enough_arguments(char **args, int ac)
{
    int count = 0;
    int len = array_len((const void **) args);

    for (int i = 1; ac > 2 && i < len; i++) {
        if (!my_strcmp(args[i], "-a") || !my_strcmp(args[i], "-n")
            || !my_strcmp(args[i], "-dump")) {
            i++;
            continue;
        }
        count++;
    }
    if (count < 2) {
        mini_printf(2, "At least 2 robots are needed to run the simulation\n");
        return 84;
    }
    return 0;
}

static int get_names(corewar_t *corewar)
{
    int count = 0;

    corewar->sim->names = malloc(sizeof(char *) * (corewar->nb_robot + 1));
    if (!corewar->sim->names)
        return 1;
    for (champ_t *head = corewar->champions; head; head = head->next) {
        corewar->sim->names[count] = my_strdup(head->prog_name);
        count++;
    }
    corewar->sim->names[count] = NULL;
    return 0;
}

// name :   corewar_main
// args :   argument count, arguments value
// use :    S.E
simulation_t *corewar_main(char **av, sfRenderWindow *window)
{
    corewar_t *corewar = NULL;
    unsigned char buffer[MEM_SIZE + 1] = {0};
    simulation_t *res;
    int ac = array_len((const void **)av);

    if (not_enough_arguments(av, ac) == 84)
        return NULL;
    corewar = parsing_main(av, window);
    if (!corewar)
        return NULL;
    buffer[MEM_SIZE] = '\0';
    set_champions_positions(corewar, buffer);
    if (get_names(corewar))
        return NULL;
    game_loop(corewar, buffer);
    res = corewar->sim;
    free_corewar(corewar);
    return res;
}


// name :   change_scene
// args :   window, simulation, option, args
// use :    S.E
int change_scene(sfRenderWindow *win, simulation_t *sim, char *opt, char **av)
{
    if (!my_strcmp(opt, "LOAD"))
        return simulation_main(win, corewar_main(av, win));
    if (!my_strcmp(opt, "SIMULATION"))
        return simulation_main(win, sim);
    return 0;
}

// name :   create_window
// args :   N.A
// use :    S.E
static sfRenderWindow *create_window(void)
{
    sfVideoMode desktop;
    sfVector2i position;
    sfContextSettings settings = {24, 8, 4, 2, 0, 0, 0};
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window = sfRenderWindow_create(
        mode, "COREWAR BONUS", sfClose | sfResize, &settings);

    if (!window) {
        mini_printf(2, "Window creation failed.\n");
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(window, 60);
    desktop = sfVideoMode_getDesktopMode();
    position.x = (desktop.width - 1920) / 2;
    position.y = (desktop.height - 1080) / 2;
    sfRenderWindow_setPosition(window, position);
    sfRenderWindow_clear(window, sfBlack);
    return window;
}

// name :   main
// args :   ac, av
// use :    main of the project
int main(int ac, char **av)
{
    sfRenderWindow *window = create_window();
    int res = 0;

    (void) ac;
    if (!window)
        return 84;
    res = change_scene(window, NULL, "LOAD", av);
    sfRenderWindow_close(window);
    sfRenderWindow_destroy(window);
    return res; 
}