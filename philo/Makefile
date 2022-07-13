#Name
NAME 		= 	philo

#Commands
CC			= 	gcc
RM			=	rm -rf

#Compilation flags
FLAGS		=	$(LFLAGS) $(WFLAGS)  # $(MEM_FLAGS)
LFLAGS		=	-lpthread
WFLAGS		=	-Wall -Werror -Wextra
MEM_FLAGS	=	-g3 -fsanitize=address

#Source files
SRCS		=	philo.c\
				launch.c\
				error.c\
				utils.c\

OBJS		=	$(SRCS:.c=.o)


#---------------------#

all:	${NAME}

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $@ $(FLAGS)

%.o: %.c
			$(CC) -c $< -o $@ $(FLAGS)
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re