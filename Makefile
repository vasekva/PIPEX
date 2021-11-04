NAME		=	pipex

INCLUDES		=	-I ./includes/
LIBFT_DIR		=	./libft/
LIBRARY			=	./libft/libft.a
SRCS_DIR		=	./srcs/
OBJS_DIR		=	./objs/

BACK_GRAY		=	\033[47m
NORM			=	\033[0m
BOLD			=	\033[1m
GREEN			=	\033[32m
YELLOW			=	\033[33m
BLUE			=	\033[34m
PURPLE			=	\033[35m
BRIGHT_BLUE		=	\033[36m
NONE			=	\033[37m

WALL			=	$(BOLD)$(PURPLE)|
F_WALL			=	$(WALL)$(BOLD)
B_WALL			=	$(WALL)$(NORM)
ROOF			=	$(BOLD)$(WALL)===============================================$(WALL)

M_SRCS_NAME		=	main.c				\
					utils.c				\

B_SRCS_NAME		=	bonus_main.c		\
					utils.c				\
					get_next_line.c		\
					add_to_file.c		\

M_OBJS_NAME		=	$(M_SRCS_NAME:.c=.o)
B_OBJS_NAME		=	$(B_SRCS_NAME:.c=.o)

MAIN_SRCS		=	$(addprefix $(SRCS_DIR), $(M_SRCS_NAME))
BONUS_SRCS		=	$(addprefix $(SRCS_DIR), $(B_SRCS_NAME))

M_OBJS		=	$(addprefix $(OBJS_DIR), $(M_OBJS_NAME))
B_OBJS		=	$(addprefix $(OBJS_DIR), $(B_OBJS_NAME))

CC			=	gcc -g
CFLAGS		=	-Wall -Wextra -Werror

.PHONY:			all, clean, fclean, re

all: 			$(NAME)

bonus:			$(BONUS_SRCS)
				@$(CC)	$(INCLUDES)	-c	$(BONUS_SRCS)
				@mkdir	-p				$(OBJS_DIR)
				@mv		$(B_OBJS_NAME)	$(OBJS_DIR)
				@$(MAKE)	-C			$(LIBFT_DIR)
				@$(CC)	$(B_OBJS)	$(LIBRARY) -o $(NAME)

$(NAME):		$(M_OBJS)
				@echo	"$(ROOF)"
				@echo	"$(F_WALL) $(YELLOW)COMPILATION PIPEX...\t\t\t$(B_WALL)"
				@$(MAKE)	-C			$(LIBFT_DIR)
				@$(CC)	$(M_OBJS)	$(LIBRARY) -o $(NAME)
				@echo	"$(ROOF)"
				@echo	"$(F_WALL)$(PURPLE)======\t $(GREEN)PIPEX IS READY TO LAUNCH$(PURPLE)\t =======$(B_WALL)"

$(M_OBJS):		$(MAIN_SRCS)
				@$(CC)	$(INCLUDES)	-c	$(MAIN_SRCS)
				@mkdir	-p				$(OBJS_DIR)
				@mv		$(M_OBJS_NAME)	$(OBJS_DIR)

clean:
				@echo	"$(F_WALL)======= $(BLUE)REMOVING ALL OBJS FILES $(PURPLE)=======$(B_WALL)"
				@echo	"$(F_WALL) $(BRIGHT_BLUE)REMOVING LIBFT OBJS...\t\t$(B_WALL)"
				@$(MAKE)	clean	-C		$(LIBFT_DIR)
				@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t$(B_WALL)"
				@echo	"$(F_WALL) $(BRIGHT_BLUE)REMOVING PIPEX OBJS...\t\t$(B_WALL)"
				@rm -rf	./objs/*.o
				@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t$(B_WALL)"
				@echo	"$(F_WALL)=============$(GREEN) SUCCESSFULLY $(BOLD)$(PURPLE)============$(B_WALL)"
				@echo	"$(NONE)"

fclean:			clean
				@echo	"$(ROOF)"
				@echo	"$(F_WALL)==== $(BLUE)DELETING DIRECTORIES AND BINARY FILES $(PURPLE)====$(B_WALL)"
				@($(MAKE)	fclean	-C		$(LIBFT_DIR))
				@rm -rf	$(NAME)
				@echo	"$(F_WALL) $(BRIGHT_BLUE)REMOVING pipex\t\t\t\t$(B_WALL)"
				@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t\t$(B_WALL)"
				@(rm -rf	$(OBJS_DIR))
				@echo	"$(F_WALL) $(BRIGHT_BLUE)REMOVING ./objs\t\t\t\t$(B_WALL)"
				@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t\t$(B_WALL)"
				@echo	"$(F_WALL)===$(BRIGHT_BLUE) ALL FILES HAVE BEEN $(GREEN)DELETED SUCCESSFULLY$(PURPLE)===$(B_WALL)"
				@echo	"$(ROOF)"
				@echo	"$(NONE)"

re:				fclean all