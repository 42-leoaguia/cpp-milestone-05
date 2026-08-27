# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leoaguia <leoaguia@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/27 19:57:49 by leoaguia          #+#    #+#              #
#    Updated: 2026/08/27 21:08:50 by leoaguia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile

NAME		=	serial

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRCS		=	main.cpp		\
				Serializer.cpp	\

OBJSDIR		=	obj/

OBJS		=	$(SRCS:%.cpp=$(OBJSDIR)%.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJSDIR)%.o: %.cpp
	mkdir -p $(OBJSDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re