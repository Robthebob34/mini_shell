# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rheck <rheck@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 14:39:41 by rheck             #+#    #+#              #
#    Updated: 2023/12/21 15:40:58 by rheck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
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

#pathing de la bibliotheque readline 
READLINE_DIR = $(shell brew --prefix readline)

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib

all: $(MINISHELL_TARGET)

$(MINISHELL_TARGET): $(MINISHELL_OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(READLINE_LIB) -o $@ $^

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