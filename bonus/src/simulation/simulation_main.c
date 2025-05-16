/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** simulation_main
*/

#include "corewar.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int events(sfRenderWindow *win, simulation_t *sim)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(win, &event)) {
        if (event.type == sfEvtClosed) {
            sim->state = 1;
            return 1;
        }
        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyEscape) {
                sim->state = 1;
                return 1;
            }
        }
    }
    return 0;
}

sfText *init_text(int line, int col, int *err, simulation_t *sim)
{
    sfText *text = sfText_create();

    if (!text) {
        *err = 1;
        return NULL;
    }
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, (sfVector2f) {20 + 19 * line, 20 + 19 * col});
    sfText_setCharacterSize(text, 19);
    sfText_setFont(text, sim->font);
    return text;
}

int other_text(simulation_t *sim)
{
    sim->cycletext = sfText_create();
    if (!sim->cycletext)
        return 1;
    sfText_setFont(sim->cycletext, sim->font);
    sfText_setCharacterSize(sim->cycletext, 40);
    sfText_setPosition(sim->cycletext, (sfVector2f){1600, 20});
    sim->cycledie = sfText_create();
    if (!sim->cycledie)
        return 1;
    sfText_setFont(sim->cycledie, sim->font);
    sfText_setCharacterSize(sim->cycledie, 40);
    sfText_setPosition(sim->cycledie, (sfVector2f){1600, 70});
    return 0;
}

int init_sim_text(simulation_t *sim)
{
    int text_index = 0;
    int error = 0;

    for (int col = 0; col < GRID_Y; col++) {
        for (int line = 0; line < GRID_X; line++) {
            text_index = col * GRID_X + line;
            sim->texts[text_index] = init_text(line, col, &error, sim);
        }
        if (error)
            return 1;
    }
    if (other_text(sim))
        return 1;
    return 0;
}

static player_t *init_player(char *name, simulation_t *sim, int index)
{
    sfColor colors[5] = {sfWhite, sfRed, sfBlue, sfYellow, sfGreen};
    player_t *player = malloc(sizeof(player_t));

    if (!player)
        return NULL;
    player->alive = sfText_create();
    player->name = sfText_create();
    if (!player->name || !player->alive)
        return NULL;
    sfText_setFont(player->name, sim->font);
    sfText_setCharacterSize(player->name, 40);
    sfText_setColor(player->name, colors[index  + 1]);
    sfText_setPosition(player->name, (sfVector2f){1600, 200 + 150 * index});
    sfText_setString(player->name, name);
    sfText_setFont(player->alive, sim->font);
    sfText_setCharacterSize(player->alive, 40);
    sfText_setPosition(player->alive, (sfVector2f){1600, 250 + 150 * index});
    sfText_setString(player->alive, "ALIVE");
    return player;
}

int init_sim2(simulation_t *sim, sfRenderWindow *win)
{
    int count = 0;

    sim->win = win;
    sim->clock = sfClock_create();
    sim->font = sfFont_createFromFile("assets/Teko-Light.ttf");
    sim->b_list = NULL;
    if (!sim->clock || !sim->font || init_sim_text(sim))
        return 1;
    sim->texture = sfTexture_createFromFile("assets/background.jpg", NULL);
    sim->background = sfSprite_create();
    if (!sim->texture || !sim->background)
        return 1;
    sfSprite_setTexture(sim->background, sim->texture, sfTrue);     
    for (; sim->names[count]; count++) {
        sim->players[count] = init_player(sim->names[count], sim, count);
        if (!sim->players[count])
            return 1;
    }
    sim->players[count] = NULL;
    sim->state = 0;
    return 0;
}

void refresh_text(simulation_t *sim, cycle_data_t *cycle)
{
    char buffer[32];
    char buff[64];
    sfColor colors[5] = {sfWhite, sfRed, sfBlue, sfYellow, sfGreen};

    snprintf(buffer, sizeof(buffer), "cycle : %d", cycle->cycle);
    sfText_setString(sim->cycletext, buffer);
    snprintf(buff, sizeof(buff), "cycles to die : %d/%d\n", sim->sub_cycle, cycle->ctd);
    sfText_setString(sim->cycledie, buff);
    for (int i = 0; sim->players[i]; i++)
        sfText_setString(sim->players[i]->alive, "DEAD");
    for (int i = 0; sim->players[i]; i++)
        for (int y = 0; cycle->champs[y]; y++)
            if (!my_strcmp(cycle->champs[y]->name, sim->names[i]))
                sfText_setString(sim->players[i]->alive, "ALIVE");
    for (int i = 0; i < MEM_SIZE; i++) {
        sfText_setString(sim->texts[i], cycle->buffer[i]);
        sfText_setColor(sim->texts[i], colors[cycle->buffer_id[i]]);
    }
}

void render(simulation_t *sim)
{
    sfRenderWindow_clear(sim->win, sfBlack);
    sfRenderWindow_drawSprite(sim->win, sim->background, NULL);
    sfRenderWindow_drawText(sim->win, sim->cycletext, NULL);
    sfRenderWindow_drawText(sim->win, sim->cycledie, NULL);
    for (int i = 0; i < MEM_SIZE; i++)
        sfRenderWindow_drawText(sim->win, sim->texts[i], NULL);
    for (int i = 0; sim->players[i]; i++) {
        sfRenderWindow_drawText(sim->win, sim->players[i]->alive, NULL);
        sfRenderWindow_drawText(sim->win, sim->players[i]->name, NULL);
    }
    sfRenderWindow_display(sim->win);
}

cycle_data_t *get_next_cycle(cycle_data_t *cycle, int move, int *nb)
{
    cycle_data_t *res = cycle;
    int i = 0;

    if (!res)
        return NULL;
    if (move > 0) {
        for (; res && res->next && i < move; i++)
            res = res->next;
        *nb = i;
        return res;
    }
    for (; res->prev && i > move; i--)
        res = res->prev;
    *nb = i;
    return res;
}

int main_sim_loop(simulation_t *sim, cycle_data_t **current)
{
    int jump = 3;
    int move;
    static int end = 0;

    if (events(sim->win, sim))
        return 1;
    if (sfTime_asMilliseconds(sfClock_getElapsedTime(sim->clock)) > 13) {
        refresh_text(sim, *current);
        render(sim);
        sfClock_restart(sim->clock);
        *current = get_next_cycle(*current, jump, &move);
        sim->sub_cycle += move;
        if (sim->sub_cycle >= (*current)->ctd)
            sim->sub_cycle = sim->sub_cycle - (*current)->ctd;
        if (end) {
            sleep(1);
            return 1;
        }
        if (!(*current)->next)
            end = 1;
    }
    return 0;
}

int simulation_main(sfRenderWindow *win, simulation_t *sim)
{
    if (!sim || !win)
        return 84;
    if (init_sim2(sim, win))
        return 84;
    for (cycle_data_t *current = sim->list; current && sim->state == 0;) {
        if (main_sim_loop(sim, &current))
            break;
    }
    for (int i = 0; i < MEM_SIZE; i++)
        sfText_destroy(sim->texts[i]);
    sfFont_destroy(sim->font);
    sfClock_destroy(sim->clock);
    return 0;
}
