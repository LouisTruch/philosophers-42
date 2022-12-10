NAME_MANDATORY	=	philo
NAME_BONUS		= 	philo_bonus

SRCS_MANDATORY	=
OBJS_MANDATORY	=	${SRCS_MANDATORY:.c=.o}

SRCS_BONUS		=
OBJS_BONUS		=	${SRCS_BONUS:.c=.o}

OBJS 			=	${OBJS_MANDATORY} ${OBJS_BONUS}
BINARY			=	${NAME_MANDATORY} ${NAME_BONUS}

CC		= clang

CFLAGS	= -Wall -Wextra -Werror -g

RM		= rm -f


all		: ${NAME_MANDATORY}

bonus	: ${NAME_BONUS}

.c.o 	: ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME_MANDATORY}	:	${OBJS_MANDATORY}
					${CC} ${CFLAGS} -o ${NAME_MANDATORY} ${OBJS_MANDATORY}

${NAME_BONUS}		:	${OBJS_BONUS}
					${CC} ${CFLAGS} -o ${NAME_MANDATORY} ${OBJS_MANDATORY}

clean	:
		${RM} ${OBJS}

fclean	:
		${RM} ${OBJS} ${BINARY}

re		: fclean all

rebonus	: fclean bonus

.:PHONY	: all clean fclean re bonus rebonus
