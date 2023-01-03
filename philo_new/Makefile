NAME_MANDATORY	=	philo

SRCS_MANDATORY	=	main.c \
					init_structs.c \
					utils.c \
					parsing.c \
					time_functions.c \
					start_philo.c

OBJS_MANDATORY	=	${SRCS_MANDATORY:.c=.o}

CC		= clang

CFLAGS	= -pthread -g

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
