/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:55 by rheck             #+#    #+#             */
/*   Updated: 2024/01/16 16:44:19 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>
# include <get_next_line.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_main
{
	char	*my_prompt_line; // ligne d'entre utilisateur
	char	*env_path; // a recuperer dans la varible env
	char	**env_tab; // copie des variables d'environnement
	char	*pwd; // a recuperer dans la variable env
	char	*old_pwd; // a recuperer dans la variable env
	pid_t	pid1; // variable de processus
	int		*output;
	int		history_file; // permet de savoir si le shell a deja ete lancer
} t_main;

typedef struct s_global {
	int		last_err_code; // code erreur du dernier processus achever
} t_global;

typedef struct s_cmd {
	char	*cmd_name; // nom de la commande 
	char	**cmd_args; // tableau commande + argument (doit finir par NULL)
	int		(*builtin)(t_main *, struct s_cmd *);
} t_cmd;

typedef enum {
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    KEYWORD,
    STRING,
	EOF_TOKEN,
    VARIABLE,
	OPTION_ARGUMENT,
	OPTION,
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

t_global my_global;

char	*get_cmd(char **path, t_main *data_base, t_cmd *just_a_try);
char	*find_env_variable(char **envp, char *to_find);

// utils
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char *s, char c);
size_t	ft_strlen(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	free_arr(char **split_arr);
char	**ft_arraydup(char **tab);
char	*ft_strdup(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

// a changer
 
int	print_history(void);

// builtins
int	my_exit(t_main *tools, t_cmd *simple_cmd);
int	my_history(t_main *data_base, t_cmd *simple_cmd);
int my_cd(t_main *tools, t_cmd *simple_cmd);
int	my_env(t_main *data_base, t_cmd *simple_cmd);
int	my_echo(t_main *tools, t_cmd *simple_cmd);
int (*look_for_builtin(char *name))(t_main *data_base, t_cmd *single_cmd);

// builtins utils
void add_myhistory(char *str);

//signal 
void    init_signal(void);

// robin lexer 
void	init_lexer(Lexer *lexer, const char *input);
int		is_operator_char(char c);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_isdigit(int c);
int		is_space(char c);
int		ft_isalpha(int c);
Token	get_next_token(Lexer *lexer);
const char	*read_operator(Lexer *lexer);
const char	*create_operator_str(Lexer *lexer, int start_position);
const char	*read_regular_operator(Lexer *lexer, int start_position);
const char	*read_double_quote(Lexer *lexer, int start_position);
const char	*read_single_quote(Lexer *lexer, int start_position);
const char	*read_quoted_string(Lexer *lexer, char quote_type);
const char	*read_option(Lexer *lexer);
char		*complete_line(int length_1, const char *input, char *var_name);
char		*replace_env_variables(const char *input);
int			find_closing_quote(Lexer *lexer, char quote_type);
const char	*read_identifier(Lexer *lexer);
int			is_valid_identifier_char(char c);
const char	*read_number(Lexer *lexer);
int			ft_isalnum(char c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void *my_realloc(void *ptr, size_t old_size, size_t new_size);

#endif