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

/*    UTILS FUNCTIONS    */

/*    PROJECT'S MAIN FUNCTIONS    */

#endif
