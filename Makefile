##
## EPITECH PROJECT, 2023
## make create
## File description:
## make
##

SRC	=	src/main.c
SRC	+=	src/amazed.c
SRC	+=	src/parser/parser.c
SRC	+=	src/parser/retrieve_infos.c
SRC	+=	src/parser/handle_errors.c
SRC +=	src/linked_list/function_list.c
SRC	+=	src/linked_list/create_list.c
SRC	+=	src/linked_list/comment_handling.c
SRC	+=	src/linked_list/coordinate_handling.c
SRC	+=	src/linked_list/link_handling.c
SRC	+=	src/algorithme/bfs_algo.c

OBJ = $(SRC:.c=.o)

NAME = amazed

CC = gcc -g

CFLAGS	=	-I include
CFLAGS	+=	-W -Wall -Wextra -Wpedantic

LIB	=	-L lib -lmy

all: $(NAME)

$(NAME): $(OBJ)
	@make -C lib/my
	@make clean -C lib/my
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIB)

clean:
	@rm -f $(OBJ)
	@find . -name "*~" -delete

tests_run:
	@make re -C tests/
	@make clean -C tests/
	@./unit_tests

fclean: clean
	@rm -f $(NAME)
	@make fclean -C tests/
	@make fclean -C lib/my
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete

re: fclean all

.PHONY:	all clean fclean re tests_run
