/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:55 by rheck             #+#    #+#             */
/*   Updated: 2024/01/04 13:40:43 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_main
{
	char	*my_prompt_line; // ligne d'entre utilisateur
	char	*env_path; // a recuperer dans la varible env
	char	*pwd; // a recuperer dans la variable env
	char	*old_pwd; // a recuperer dans la variable env
	pid_t	pid1; // variable de processus
	int		last_err_code; // code erreur du dernier processus achever 
	int		*output;
} t_main;
 
typedef struct s_cmd {
	char	*cmd_name; // nom de la commande 
	char	**cmd_args; // tableau commande + argument (doit finir par NULL)
	int		(*builtin)(t_main *, struct s_cmd *); // j'ai pas encore tout compris
} t_cmd;

typedef enum {
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    KEYWORD,
    STRING,
	EOF_TOKEN,
    VARIABLE,
    ERROR
} TokenType;


typedef struct {
    const char *input;
    size_t position;
} Lexer;

typedef struct {
    TokenType type;
    const char *value;
} Token;

void init_lexer(Lexer *lexer, const char *input);
Token get_next_token(Lexer *lexer);


char	*get_cmd(char **path, t_main *data_base, t_cmd *just_a_try);
char	*find_env_variable(char **envp, char *to_find);


// utils
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char *s, char c);
size_t	ft_strlen(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

// a changer
 
int	print_history(t_main *data_base);

// builtins
int	my_exit(t_main *tools, t_cmd *simple_cmd);
int (*look_for_builtin(char *name))(t_main *data_base, t_cmd *single_cmd);

#endif