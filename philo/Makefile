NAME	=	philo

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror 
BASE_DEBUG_CFLAGS	=	$(CFLAGS) -g3
DEBUG_CFLAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=thread

FLAGS	=	$(CFLAGS)

HEADERS	=	philo.h

SRC_DIR	=	src/
OBJ_DIR	=	obj/

SRC_FILES	=	main	\
				lib_utils	\
				init	\
				dinner	\
				thread_utils	\
				time	\
				monitoring	\
				simulation	\
				safe_pthread

SRCS =	$(foreach file,$(SRC_FILES),$(foreach dir,$(SRC_DIR),$(dir)$(file).c))
OBJS = $(foreach file,$(SRC_FILES),$(foreach dir,$(OBJ_DIR),$(dir)$(file).o))

DIR_INCS	=	includes/

INCLUDES	=	$(addprefix -I , $(DIR_INCS))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DIR_INCS)$(HEADERS)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug: clean
	@$(MAKE) -j FLAGS="$(DEBUG_CFLAGS)"

.PHONY:  all clean fclean re debug