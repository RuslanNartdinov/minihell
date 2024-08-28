	#•	Оболочка будет работать только в интерактивном режиме (без скриптов, то есть исполняемый файл не принимает аргументов).
	#•	Запускать простые команды с абсолютным или относительным путем (например, /bin/ls, ../bin/ls).
	#•	Запускать простые команды без указания пути (например, ls, cat, grep и т.д.).
	#•	Иметь рабочую историю (можно перемещаться по командам с помощью стрелок вверх/вниз).
	#•	Реализовать каналы (|).
	#•	Реализовать перенаправления (<, >, >>).
	#•	Реализовать here-doc (<<).
	#•	Обрабатывать двойные кавычки (””) и одинарные кавычки (’’), которые должны экранировать специальные символы, а также $ для двойных кавычек.
	#•	Обрабатывать переменные окружения ($, за которым следует последовательность символов).
	#•	Обрабатывать сигналы, как в bash (ctrl + C, ctrl + , ctrl + D).
	#•	Реализовать следующие встроенные команды:
	#•	echo (только с опцией -n).
	#•	exit.
	#•	env (без опций или аргументов).
	#•	export (без опций).
	#•	unset (без опций).
	#•	cd.
	#•	pwd.


SRC := $(shell find . -name '*.c')


OBJ = $(SRC:.c=.o)

NAME = minishell
#CFLAGS =  -Wall -Wextra -Werror
CC = cc

all : $(NAME)

$(NAME) : $(OBJ)
	${CC} ${CFLAGS} ${OBJ} -o $(NAME)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re