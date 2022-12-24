# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 14:48:10 by mingkang          #+#    #+#              #
#    Updated: 2022/12/24 15:57:58 by mingkang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= fdf

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

MLXFLAGS	= -lmlx -framework OpenGL -framework AppKit

RM			= rm

RMFLAGS		= -rf

AR			= ar

ARFLAGS		= -crs

#libft
LIBFT_DIR	= ./libft/

LIBFT		= ${LIBFT_DIR}libft.a

# INCLUDE		= -I ${LIBFT_DIR}



SRCS_DIR	= ./sources/

SRCS_NAME	= color_utils.c color.c common.c control_key.c control_mouse.c \
draw.c init_map.c init.c main.c point.c

SRCS		= ${addprefix ${SRCS_DIR}, ${SRCS_NAME}}

OBJS_DIR 	= objects/

OBJS_NAME	= ${SRCS_NAME:.c=.o}

OBJS		= ${addprefix ${OBJS_DIR}, ${OBJS_NAME}}

all:		${NAME}

${NAME}:	${LIBFT} ${OBJS_DIR} ${OBJS}
	${CC} ${CFLAGS} ${LIBFT} ${MLXFLAGS} ${OBJS} -o $@

${OBJS_DIR}:
	mkdir ${OBJS_DIR}

${OBJS_DIR}%.o:	${SRCS_DIR}%.c
	${CC} ${CFLAGS} -I"./" -I"./libft/" -c $< -o $@

${LIBFT}:
	${MAKE} -sC ${LIBFT_DIR}

clean:
	${MAKE} -sC ${LIBFT_DIR} clean
	${RM} ${RMFLAGS} ${OBJ_DIR}

fclean:		clean
	${RM} ${RMFLAGS} ${LIBFT}
	${RM} ${NAME}

re:
	${MAKE} fclean
	${MAKE} all

.PHONY:		all clean fclean re bonus
