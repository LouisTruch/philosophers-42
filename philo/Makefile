NAME_MANDATORY	=	philo

SRCS_MANDATORY	=	philo.c \
					utils.c \
					ft_parsing.c \
					initialise_game_struct.c

OBJS_MANDATORY	=	${SRCS_MANDATORY:.c=.o}

CC		= clang

CFLAGS	= -Wall -Wextra -Werror -g

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
