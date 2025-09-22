#### Variables ####

# Binary
NAME			= philo

# Tooling
CC				= cc
RM				= rm -rf

# Directories
INC_DIR			= includes/
SRC_DIR			= src/
OBJ_DIR			= obj/

# Flags
INCLUDES		= -I$(INC_DIR)
CFLAGS			= -Wall -Werror -Wextra -pthread $(INCLUDES)
CFLAGS			+= -MMD -MP
LDFLAGS			= -pthread
DEBUG_FLAGS		= -g -fsanitize=address
GRIND_FLAGS		= -g3 -O0

# Sources
SRC_FILES		= \
				controls.c \
				error_and_close_management_0.c \
				error_and_close_management_1.c \
				forking.c \
				ft_atoi.c \
				ft_split.c \
				init.c \
				main_process.c \
				parsing.c \
				printing.c \
				routines.c \
				threads.c \
				time_management.c \
				utils_0.c \
				utils_1.c
SRCS		= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS		= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPS		= $(OBJS:.o=.d)


#### Rules ####

all:			$(NAME)

$(NAME):		$(OBJS)
				@echo "Linking $(NAME)..."
				$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
				@echo "$(NAME) linked."

$(OBJ_DIR):
				@mkdir -p $@

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c | $(OBJ_DIR)
				@echo "Compiling $< -> $@..."
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo "$@ Compiled."


clean:
				@echo "Cleaning $(NAME) object files..."
				@$(RM) $(OBJ_DIR)
				@echo "Object files of $(NAME) removed"

fclean:	clean
				@echo "Cleaning everything in $(NAME)..."
				@$(RM) $(NAME)
				@echo "Everything related to $(NAME) cleaned."

re: 			fclean all

debug:
				@$(MAKE) re CFLAGS="$(CFLAGS) $(DEBUG_FLAGS)"

grind:
				@$(MAKE) re CFLAGS="$(CFLAGS) $(GRIND_FLAGS)"

-include $(DEPS)

.PHONY: 		all clean fclean re debug grind