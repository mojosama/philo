NAME	=	philo

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror 
BASE_DEBUG_CFLAGS	=	$(CFLAGS) -g3
DEBUG_CFLAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=address

FLAGS	=	$(CFLAGS)

HEADERS	=	philo.h

SRC_DIR	=	src/
OBJ_DIR	=	obj/

SRC_FILES	=	main	lib_utils	init

SRCS = $(foreach file,$(SRC_FILES),$(foreach dir,$(SRC_DIR),$(dir)$(file).c))
OBJS = $(foreach file,$(SRC_FILES),$(foreach dir,$(OBJ_DIR),$(dir)$(file).o))

DIR_INCS	=	includes/			\
				$(MLX_INCLUDES)

INCLUDES	=	$(addprefix -I , $(DIR_INCS))

LIBS = -lm $(MLX_L) -lXext -lX11

all: $(NAME)

$(NAME): $(OBJS)
	$(MLX_MAKE)
	$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)| $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	@$(MAKE) -j FLAGS="$(DEBUG_CFLAGS)"

.PHONY:  all clean fclean re fast debug