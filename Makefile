NAME = minishell

GNL = get_next_line/get_next_line_utils.c \
	  get_next_line/get_next_line.c \

SRC_BUILTINS =  source/builtins/builtins_comm_exec.c \
				source/builtins/builtins_comm.c \
				source/builtins/builtins_echo.c \
				source/builtins/builtins_exit.c \
				source/builtins/builtins_export.c \

SRC_EXECUTION = source/execution/execution_cmd_arg_utils.c \
				source/execution/execution_cmd_utils.c source/execution/execution_cmd.c \
				source/execution/execution_fds.c \
				source/execution/execution_handle_cmd.c \
				source/execution/execution_utils.c \
				source/execution/executor.c \

SRC_INITIALIZING =  source/initializing/enviroment_init.c \
					source/initializing/enviroment_set.c \
					source/initializing/initializing.c \

SRC_PARSING =   source/parsing/parsing_env.c \
				source/parsing/parsing_part_1.c \
				source/parsing/parsing_part_2.c \
				source/parsing/parsing.c \

UTILITIES = utilities/cmd_utils.c \
			utilities/ft_split.c \
			utilities/ft_strtrim.c \
			utilities/lst_utils.c \
			utilities/utils1.c \
			utilities/utils2.c \
			utilities/utils3.c \

SRC = source/minishell.c \
	  source/type.c \
	  $(GNL) \
	  $(SRC_BUILTINS) \
	  $(SRC_EXECUTION) \
	  $(SRC_INITIALIZING) \
	  $(SRC_PARSING) \
	  $(UTILITIES) \



OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -I/opt/vagrant/embedded/include

SEG_FLAGS = -fsanitize=address -g3

CFLAGS += $(SEG_FLAGS)

COMPILE = $(CC) $(CFLAGS) $(RLFLAG)

all : $(NAME)

leak: $(NAME)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes  --suppressions=leaks.supp ./minishell

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L/opt/vagrant/embedded/lib -lreadline -lncurses -lhistory -o $(NAME)


clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
