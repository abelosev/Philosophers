NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -pthread -g3 -I./header

SRCDIR = ./src/
OBJDIR = ./obj/

SRC	=	${addprefix src/, \
		check_input.c \
		free_outils.c \
		init_data.c \
		init_philo.c \
		libft_outils.c \
		main.c \
		routine.c \
		time_and_print.c}

OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

$(NAME) : $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

all: $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re