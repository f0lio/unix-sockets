
.PHONEY: all clean fclean re bonus

NAME				=	server
CC					=	gcc
FLAGS				=	-Werror -Wextra -Wall

INCLUDES			=	-I includes

SRC					=	main.c server.c

SRC					:=	$(SRC:%.c=./src/%.c)

COMPILE	= $(CC) $(SRC) $(INCLUDES) -o $(NAME) # -g

all: $(NAME)

$(NAME): $(SRC)
	@$(COMPILE)

run: all
	@./$(NAME) 8080

clean:
	@rm -rf *.o

fclean: clean
	@-rm -f $(NAME)
	@-rm -f *.out
	@-rm -f *.gch
	@-rm -rf ./*.d*

re: fclean all
