# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/15 12:34:28 by cesar             #+#    #+#              #
#    Updated: 2024/03/19 17:49:30 by cefuente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

SRCS_LIST		=	mem.c \
					main.c \
					quit.c \
					utils.c \
					famine.c \
					routine.c \
					print_states.c \
					actions_and_checks.c \
					
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/
INCLUDES_DIR	=	includes/

SRCS			=	$(addprefix $(SRCS_DIR),$(SRCS_LIST))
OBJS			=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
HEADER			=	$(INCLUDES_DIR)philosophers.h

CC				=	cc
FLAGS			=	-Wall -Wextra -Werror -g -lpthread -pthread
RM				=	rm -rf

all			:	$(NAME)

$(NAME)		:	$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o	:	$(SRCS_DIR)%.c $(HEADER)
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I$(INCLUDES_DIR) -c $< -o $@

clean		:
	$(RM) $(OBJS_DIR)

fclean		:    clean
	$(RM) $(NAME)

re			:    fclean all

.PHONY		:	all clean fclean re