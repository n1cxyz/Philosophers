NAME		= philosophers
CC			= cc
BIN			= bin
SRC			= src/main.c
OBJS		= $(SRC:src/%c=$(BIN)/%o)
INCS		= include
CFLAGS		= -Wall -Werror -Wextra -g
IFLAGS		= -I$(INCS)
RM			= rm -rf
VALGRIND	= @valgrind --leak-check=full --show-leak-kinds=all
#--track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes

all: $(NAME)

$(NAME): ${BIN} ${OBJS} 
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

$(BIN)/%o: src/%c
	${CC} ${CFLAGS} -c $< ${IFLAGS} -o $@

$(BIN):
	mkdir -p $(BIN)

clean:
	$(RM) $(BIN)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: ${NAME}
	${VALGRIND} ./${NAME}

show:
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "IFLAGS		: $(IFLAGS)\n"
	@printf "SRC		: $(SRC)\n"
	@printf "OBJS		: $(OBJS)\n"

.PHONY: $(LIBFT) re all clean fclean