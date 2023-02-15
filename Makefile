
#	███╗   ███╗ █████╗ ██╗  ██╗███████╗███████╗██╗██╗     ███████╗
#	████╗ ████║██╔══██╗██║ ██╔╝██╔════╝██╔════╝██║██║     ██╔════╝
#	██╔████╔██║███████║█████╔╝ █████╗  █████╗  ██║██║     █████╗
#	██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝  ██╔══╝  ██║██║     ██╔══╝
#	██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗██║     ██║███████╗███████╗
#	╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝╚══════╝╚══════╝

NAME = fdf

CC		 = cc
CFLAGS   = -Wall -Werror -Wextra
MLXFLAGS = -lglfw -L "$(HOME)/homebrew/Cellar/glfw/3.3.8/lib/"
AR		 = ar rcs
RM		 = rm -rf
#FSANITIZE = -fsanitize=address -g

.SILENT:
			libft
			clean
			all
			$(NAME)

SRC =		fdf.c			\
			get_input.c		\
			start_mlx.c		\
			xyz.c			\

OBJS =		$(SRC:.c=.o)

LIBFT =	./libft/libft.a
MLX42 =	./MLX42/build/libmlx42.a

$(NAME):	$(LIBFT) $(MLX42) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(FSANITIZE) $(MLX42) $(LIBFT) -o $(NAME) $(MLXFLAGS)

$(LIBFT):
			@if [ ! -d "libft" ]; then git clone https://github.com/Pgorner/libft.git; fi
			@cd libft && make && make clean
$(MLX42):
			@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
			@cd MLX42 && cmake -B build && cmake --build build -j4 

all :		$(NAME)

clean :
			$(RM) $(OBJS)

fclean :	clean
			@$(RM) $(NAME)
			@$(RM) ./libft
			@$(RM) ./MLX42

re :		fclean all

libft: $(LIBFT)
mlx: $(MLX42)

.PHONY: all clean fclean re
