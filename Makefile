# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rheck <rheck@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 14:39:41 by rheck             #+#    #+#              #
#    Updated: 2024/01/16 15:35:25 by rheck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
LFLAGS = -lreadline
INC_DIR = ./inc
SRC_DIR = ./src
BUILT_DIR = ./src/builtins
OBJ_DIR = ./obj

# Source files
MINISHELL_SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files
MINISHELL_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MINISHELL_SRC))

# Target
MINISHELL_TARGET = minishell

#includes

INCLUDE = -Iincludes -I INC_DIR

#pathing de la bibliotheque readline 
READL   = -L/usr/local/lib -I/usr/local/include -Ireadline -I$(shell brew --prefix readline)/include -lreadline -lhistory -L $(shell brew --prefix readline)/lib

CFLAGS  = -Wall -Wextra -Werror -I$(shell brew --prefix readline)/include -g -fsanitize=address

all: $(MINISHELL_TARGET)

$(MINISHELL_TARGET): $(MINISHELL_OBJ)
	$(CC) $(CFLAGS) $(READL) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(MINISHELL_TARGET)
	clear

re: fclean all

.PHONY: all clean fclean re