NAME	=	philo

SRCS	=	main.c \
			init_structs.c \
			utils.c \
			parsing.c \
			time_functions.c \
			start_philo.c \
			manage_philo.c

OBJS	=	${SRCS:.c=.o}

CC		= clang

CFLAGS	= -Wall -Wextra -Werror -pthread -g

RM		= rm -f

all		: ${NAME}

.c.o 	: ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}	: ${OBJS}
		${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean	:
		${RM} ${OBJS}

fclean	: clean
		${RM} ${NAME}

re		: fclean all

.PHONY	: all clean fclean re
