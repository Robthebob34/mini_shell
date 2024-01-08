/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:55 by rheck             #+#    #+#             */
/*   Updated: 2023/12/21 14:54:57 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <get_next_line.h>
# include </Users/mgigot/.brew/Cellar/readline/8.2.7/include/readline/readline.h>
# include </Users/mgigot/.brew/Cellar/readline/8.2.7/include/readline/history.h>


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
	int		(*builtin)(t_main *, struct s_cmd *); // j'ai pas encore tout compris
} t_cmd;

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
int (*look_for_builtin(char *name))(t_main *data_base, t_cmd *single_cmd);

// builtins utils
void add_myhistory(char *str);

//signal 
void    init_signal(void);

#endif