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
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdarg.h>
    /*    PROJECT LIBS    */

typedef struct node {
    char *name;
    int value;
    struct node *next;
} node_t;

typedef struct list {
    struct node *head;
} list_t;

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
    args_type_t type[MAX_ARGS_NUMBER];
    struct champ_s *next;
} champ_t;

typedef struct {
    unsigned int cycle_alive;
    int last_alive;
    int nb_robot;
    champ_t *champions;
} prog_t;

typedef int (*cmd_func_t)(prog_t *, champ_t *, unsigned char *);

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
char *str_lowcase(char *);
int is_bool(const char *);

/*    LIB ARRAY    */
char **split_str(const char *, const char *);
int free_array(void **);
int my_array_len(const void **);
int total_array_len(const char **);

/*    LIB NUMBER    */
int my_atoi(const char *);
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

/*    UTILS FUNCTIONS    */
int get_type(int *i, champ_t *cur, unsigned char *buffer);
int init_champ(prog_t *prog, unsigned char *buffer);
int update_pc(champ_t *cur);
int convert_int(unsigned char *buffer, champ_t *cur);
void **get_args(champ_t *cur, unsigned char *buffer);

/*    PROJECT'S MAIN FUNCTIONS    */
int game_loop(prog_t *prog, unsigned char *buffer);
int exec_cmd(champ_t *cur, prog_t *prog, unsigned char *buffer);
int add_champ(FILE *fd, prog_t *prog, int id);

/*      CMD       */
int live(prog_t *prog, champ_t *cur, unsigned char *buffer);

#endif
