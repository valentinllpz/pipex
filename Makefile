# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 17:58:20 by vlugand-          #+#    #+#              #
#    Updated: 2021/10/07 15:13:59 by vlugand-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	pipex

SRCS		= 	srcs/main.c

CC			= 	gcc
OBJS		= 	${SRCS:.c=.o}
CFLAGS		= 	-Wall -Wextra -Werror
LIBS		=	-L libft -lft
RM			= 	rm -f
LIBFT		=	libft/libft.a

all:		${LIBFT} ${NAME}

.c.o:
			${CC} ${CFLAGS} -I includes -c $< -o ${<:.c=.o}

${LIBFT}:
			@make -C libft
			@echo "\033[0;36m\033[1mLibft is ready to use.\033[0m"
			#For any change in libft please use "make re" with this Makefile or "make" on the Makefile located in ./libft/

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBS} -lncurses
			@echo "\033[0;32m\033[1mPipex is now ready!\033[0m"
			@echo "\033[92m██████  ██ ██████  ███████ ██   ██ "
			@echo "\033[93m██   ██ ██ ██   ██ ██       ██ ██  "
			@echo "\033[91m██████  ██ ██████  █████     ███   "
			@echo "\033[95m██      ██ ██      ██       ██ ██  "
			@echo "\033[96m██      ██ ██      ███████ ██   ██ \033[0mby vlugand-"
			@echo ""

clean:		
			@make clean -C libft
			${RM} ${OBJS}
			@echo "\033[0;35m\033[1mCleaned all .o files.\033[0m"

fclean:		
			@make fclean -C libft
			${RM} ${OBJS}
			${RM} ${NAME}
			@echo "\033[0;35m\033[1mCleaned all .o files and executable.\033[0m"

re:			fclean all

.PHONY:		all clean fclean re bonus
