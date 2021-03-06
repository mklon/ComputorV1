#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/03 13:24:28 by oposhiva          #+#    #+#              #
#    Updated: 2018/06/03 13:24:39 by oposhiva         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = computor

SOURCE =    main.cpp \
            Solution.class.cpp \

OBJECTS = $(SOURCE:.cpp=.o)

CC = g++

FL = -Wall -Wextra -Werror -std=c++11

all: $(NAME) done

$(NAME): $(OBJECTS)
	@$(CC) $(FL) $(SOURCE) -o $(NAME)

%.o: %.cpp
	@$(CC) $(FL) -c $< -o $@

clean:
	@rm -f $(OBJECTS)
	@echo "\033[;33m[ It's clean ]\033[33;0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[;31m[ Deleted ]\033[33;0m"

re: fclean all

done:
	@echo "\033[;32m[ Well done ]\033[33;0m"
