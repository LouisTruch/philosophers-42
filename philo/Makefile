NAME_MANDATORY	=	philo

SRCS_MANDATORY	=	main.c \
					utils.c \
					parsing.c \
					init_structs.c \
					time_functions.c \
					algo_philo.c

OBJS_MANDATORY	=	${SRCS_MANDATORY:.c=.o}

CC		= clang

CFLAGS	= -Wall -Wextra -Werror -pthread -g

RM		= rm -f

all		: ${NAME_MANDATORY}

.c.o 	: ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME_MANDATORY}	:	${OBJS_MANDATORY}
					${CC} ${CFLAGS} -o ${NAME_MANDATORY} ${OBJS_MANDATORY}

clean	:
		${RM} ${OBJS_MANDATORY}

fclean	:
		${RM} ${OBJS_MANDATORY} ${NAME_MANDATORY}

re		: fclean all

.PHONY	: all clean fclean re
