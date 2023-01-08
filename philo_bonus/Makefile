NAME	=	philo_bonus

SRCS	=	main_bonus.c \
			init_struct_bonus.c \
			start_philo_bonus.c \
			utils_bonus.c \
			parsing_bonus.c \
			time_functions_bonus.c 

OBJS	=	${SRCS:.c=.o}

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -pthread -g

RM		=	rm -f

all		:	${NAME}

.c.o 	:	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}	:	${OBJS}
		${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean	:
		${RM} ${OBJS}

fclean	:	clean
		${RM} ${NAME}

re		:	fclean all

.PHONY	: all clean fclean re
