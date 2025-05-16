/*
** EPITECH PROJECT, 2025
** lib
** File description:
** lib
*/

#ifndef LIB_H
    #define LIB_H
    #include "op.h"
    /*    LIB    */
    /*    PROJECT LIBS    */
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>

#define GRID_X 80
#define GRID_Y 48

typedef struct node {
    char *name;
    int value;
    struct node *next;
} node_t;

typedef struct list {
    struct node *head;
} list_t;

typedef struct {
    sfText *name;
    sfText *alive;
} player_t;

typedef struct champ_s {
    unsigned int magic_number;
    char prog_name[PROG_NAME_LENGTH + 1];
    unsigned int prog_size;
    char *code;
    unsigned int wait_cycle;
    unsigned int pc;
    int status;
    int rem;
    unsigned int nbr_live;
    int pos;
    int id;
    int carry;
    int child;
    int advance_pc;
    int registre[REG_NUMBER];
    int color_index;
    int state;
    args_type_t type[MAX_ARGS_NUMBER];
    struct champ_s *next;
} champ_t;

typedef struct champ_info {
    int id;
    char *name;
    int color_id;
    unsigned int wait;
} champ_info_t;

typedef struct cycle_data {
    char buffer[MEM_SIZE][3];
    struct champ_info *champs[5];
    int *buffer_id;
    int cycle;
    int ctd;
    struct cycle_data *next;
    struct cycle_data *prev;
} cycle_data_t;

typedef struct button_data_s {
    int sizey;
    int sizex;
    int posx;
    int posy;
    char *path;
    int effect;
    int permanant;
    char *text;
    sfFont *font;
    char *hover;
} button_data_t;

typedef struct button_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfText *text;
    sfText *htext;
    sfRectangleShape *rect;
    int permanant;
    int active;
    int hover;
    int effect;
    sfVector2f pos;
    sfVector2f size;
    struct button_s *next;
} button_t;

typedef struct button_list_s {
    button_t *head;
} button_list_t;

typedef struct {
    cycle_data_t *list;
    button_list_t *b_list;
    sfRenderWindow *win;
    sfTexture *texture;
    sfSprite *background;
    sfFont *font;
    sfText *cycletext;
    sfText *cycledie;
    sfText *texts[MEM_SIZE];
    sfClock *clock;
    player_t *players[5];
    int state;
    int cycle_to_die;
    int sub_cycle;
    char **names;
} simulation_t;

typedef struct {
    unsigned int cycle_alive;
    int last_alive;
    int nb_robot;
    int dump;
    int cur_id;
    int *index;
    sfTexture **textures;
    sfSprite *sprite;
    int texture_index;
    sfClock *clock;
    simulation_t *sim;
    sfRenderWindow *window;
    cycle_data_t *current;
    champ_t *champions;
} corewar_t;

typedef struct {
    int address;
    int dump;
    int id;
    char **array;
    int index;
} flags_t;

typedef int (*cmd_func_t)(corewar_t *, champ_t *, unsigned char *);

typedef struct {
    char *name;
    cmd_func_t func;
} cmd_t;

/*    LIB STR    */
int my_strlen(const char *);
int my_strcmp(const char *, const char *);
int my_strncmp(const char *, const char *, int);
char *my_strdup(const char *);
char *array_to_str(const char **, char);
char *my_strcat(const char *, const char *, const char *);
int my_strncpy(const char *, const char *, int);
char *my_strcpy(char *dest, char const *src);
char *str_lowcase(char *);
int array_len(const void **);
int is_bool(const char *);

/*    LIB ARRAY    */
char **split_str(const char *, const char *);
int free_array(void **);
int my_array_len(const void **);
int total_array_len(const char **);

/*    LIB NUMBER    */
int my_atoi(const char *, int *);
int is_unsigned_int(const char *);
int is_negative_int(const char *);
int is_float(const char *str);

/*    LIB LINKED LIST    */
void free_list(list_t *);
list_t *create_list(void);
void add_node(char *, int, list_t *);
int delete_node(list_t *, const char *);
void print_list(list_t *);
char **list_to_array(list_t *);
int free_node(node_t *);

/*    OTHER LIB FUNCTIONS    */
int mini_printf(int, const char *, ...);
int my_free(void *);
unsigned int swap_end_color_4(unsigned int num);


/*    INIT    */
corewar_t *init_main_struct(sfRenderWindow *window);
flags_t *init_flags(char **);
champ_t *init_champion(flags_t *, corewar_t *);

/*    FREE    */
int free_champion(champ_t *);
int free_corewar(corewar_t *);

/*    UTILS FUNCTIONS    */
int check_reg(int);
int update_pc(champ_t *);
int convert_int(unsigned char *, int);
int get_type(int *, champ_t *cur, unsigned char *);
int set_champions_positions(corewar_t *, unsigned char *);
short convert_short(unsigned char *, int);
void **get_args(champ_t *, unsigned char *);
void add_to_end(corewar_t *prog, champ_t *champion);

/*    PROJECT'S MAIN FUNCTIONS    */
corewar_t *parsing_main(char **array, sfRenderWindow *window);
int game_loop(corewar_t *, unsigned char *);
int exec_cmd(champ_t *, corewar_t *, unsigned char *);
int handle_flags(flags_t *);
int parse_champion_file(corewar_t *, flags_t *);
int update_dir(champ_t *cur);
int check_array(champ_t *cur);
champ_t *find_node(corewar_t *, int, int);
void remove_champion(champ_t **, int, corewar_t *);
int read_mem(unsigned char *, int, int);
int get_value(int, void *, champ_t *, unsigned char *);
int reset_cycle(corewar_t *);
champ_t *new_champ(corewar_t *, champ_t *, int);

/*      CMD       */
int live(corewar_t *, champ_t *, unsigned char *);
int store(corewar_t *, champ_t *, unsigned char *);
int load(corewar_t *, champ_t *, unsigned char *);
int add(corewar_t *, champ_t *, unsigned char *);
int sub(corewar_t *, champ_t *, unsigned char *);
int and_cmd(corewar_t *, champ_t *, unsigned char *);
int or_cmd(corewar_t *, champ_t *, unsigned char *);
int xor_cmd(corewar_t *, champ_t *, unsigned char *);
int zjump(corewar_t *, champ_t *, unsigned char *);
int ldi(corewar_t *, champ_t *, unsigned char *);
int sti(corewar_t *, champ_t *, unsigned char *);
int lld(corewar_t *, champ_t *, unsigned char *);
int lldi(corewar_t *, champ_t *, unsigned char *);
int aff(corewar_t *, champ_t *, unsigned char *);
int fork_cmd(corewar_t *, champ_t *, unsigned char *);
int lfork_cmd(corewar_t *, champ_t *, unsigned char *);

int new_cycle(unsigned char *buffer, corewar_t *corewar);
int change_scene(sfRenderWindow *win, simulation_t *sim, char *opt, char **av);
int simulation_main(sfRenderWindow *win, simulation_t *sim);

#endif
