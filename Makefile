NAME = cub3D
UNAME = $(shell uname)

#text_color
COLOR_OFF =\033[0m
RED =\033[0;31m
GREEN =\033[0;32m
YELLOW =\033[0;33m
CYAN =\033[1;36m
MAGNETA =\033[95m

ifeq ($(UNAME), Linux)
	EXTRA_LIBS = -Imlx_linux -I/usr/include -L/usr/lib -lmlx_Linux -lXext -lX11 -lm -lz
endif

ifeq ($(UNAME), Darwin)
	EXTRA_LIBS = -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit -Imlx
endif

CC = gcc
CFLAGS = -Wall -Wextra -Werror

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

LIBFT_DIR = libft/
LIBFT_LIB = $(addprefix $(LIBFT_DIR), libft.a)

HEADER_DIR = $(call rwildcard,./,includes)
HEADER = $(addprefix -I, $(HEADER_DIR))

SRCS = $(call rwildcard,srcs/,*.c)
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:c=o))

NAMESERVER = $(shell cat /etc/resolv.conf | grep nameserver)
NAMESERVER_IP = $(filter-out nameserver, $(NAMESERVER))
NAMESERVER_IP_SUFFIXED = $(addsuffix :0.0, $(NAMESERVER_IP))

all : $(NAME)

$(LIBFT_LIB) :
	@make bonus -C $(LIBFT_DIR)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "$(MAGNETA)Compiling: $<$(COLOR_OFF)\n"
	@$(CC) -o $@  -c $< $(HEADER)

$(NAME) : $(LIBFT_LIB) $(OBJS)
	@$(CC) $(OBJS) $(HEADER) $(LIBFT_LIB) $(EXTRA_LIBS) -o $(NAME)
	@printf "$(CYAN)$(NAME) done !$(COLOR_OFF)\n"

fclean :
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR) $(NAME)
	@printf "$(RED)Removed : obj files ($(NAME))$(COLOR_OFF)\n"
	@printf "$(RED)Removed : $(NAME)$(COLOR_OFF)\n"

re : fclean all

# Copy and paste the output of this rule below to terminal and hit enter.
display :
	export DISPLAY=$(NAMESERVER_IP_SUFFIXED)

kill :
	@killall -9 $(NAME)

valgrind :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY : clean fclean all re
