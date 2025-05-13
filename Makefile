##
## EPITECH PROJECT, 2024
## makefile
## File description:
## task 01
##

# DIRECTORIES
OBJ_DIR = obj

# FILES
SRC = 	lib/mini_printf.c 			\
		lib/my_strcmp.c 			\
		lib/my_strlen.c 			\
		lib/my_atoi.c 				\
		lib/swap_end_color.c 		\
		lib/array_len.c 			\
		lib/free.c 					\
		src/utils/get_type.c 		\
		src/utils/linked_list.c 	\
		src/utils/op.c 				\
		src/utils/champions.c 		\
		src/utils/update_pc.c 		\
		src/utils/init.c 			\
		src/utils/free.c 			\
		src/utils/convert_type.c 	\
		src/utils/get_args.c 		\
		src/utils/flags.c 			\
		src/game_loop.c 			\
		src/cmd/live.c 				\
		src/cmd/st.c 				\
		src/cmd/ld.c 				\
		src/cmd/add.c 				\
		src/cmd/sub.c 				\
		src/cmd/and.c 				\
		src/cmd/or.c 				\
		src/cmd/xor.c 				\
		src/cmd/zjump.c 			\
		src/cmd/ldi.c 				\
		src/cmd/sti.c 				\
		src/cmd/lld.c 				\
		src/cmd/lldi.c 				\
		src/cmd/aff.c				\
		src/utils/in_reg.c 			\
		src/utils/get_value.c 		\
		src/exec_cmd.c 				\
		src/parsing.c 				\
		src/main.c 					\

# COLORS
RED=\033[31m
GREEN=\033[32m
WHITE=\033[37m
BOLD=\033[1m
RESET=\033[0m

# VARIABLES
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
CFLAGS = -Wextra -Wall -W -Werror -I include
CC = gcc
NAME = corewar

# PRINT COMPILATION
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo -e "$(GREEN)$(BOLD)[COMPILING]:\t$(RESET)$(GREEN)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# PRINT AND THEN COMPILE
all: pre-compile $(NAME)

# PRINT INFO
pre-compile:
	@echo -e "$(WHITE)$(BOLD)\t$(WHITE)[COMPILATION...]$(RESET)"
	@mkdir -p $(OBJ_DIR)

# COMPILATION
$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)
	@echo -e "$(WHITE)$(BOLD)\t[COMPILED SUCCESSFULLY]"
	@echo -e "[READY]:$(RESET)$(WHITE)\t$(NAME)$(RESET)"

# CLEAN OBJECT FILES
clean:
	@echo -e "$(WHITE)$(BOLD)\t[CLEANING OBJ...]$(RESET)"
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo "$(RED)$(BOLD)[CLEAN]:\t$(RESET)$(RED)$(OBJ_DIR)$(RESET)"; \
		rm -rf $(OBJ_DIR); \
	fi

# CLEAN EXEC / LIB and call clean
fclean:
	@echo -e "$(WHITE)$(BOLD)\t[CLEANING EXEC/LIB...]"
	@echo -e "$(RED)[CLEAN]:\t$(RESET)$(RED)$(NAME)$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) clean -s

# CLEAN EVERYTHING AND RE-COMPILE
re: fclean all

tests_run:
	@echo -e "$(WHITE)$(BOLD)\t[TESTS...]$(RESET)"

debug: CFLAGS += -g
debug: re
