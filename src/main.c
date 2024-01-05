/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:39 by rheck             #+#    #+#             */
/*   Updated: 2023/12/21 15:40:22 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int	my_header(void)
{
	printf("___  ___      _____ _          _ _ \n");
	printf("|  \\/  |     /  ___| |        | | |\n");
	printf("| .  . |_   _\\ `--.| |__   ___| | |\n");
	printf("| |\\/| | | | |`--. \\ '_ \\ / _ \\ | |\n");
	printf("| |  | | |_| /\\__/ / | | |  __/ | |\n");
	printf("\\_|  |_/\\__, \\____/|_| |_|\\___|_|_|\n");
	printf("         __/ |                     \n");
	printf("        |___/                      \n");
	return(0);
}
// permet d'executer depuis l'entre utilisateur des commandes simple sans arguments
int	execute(char **env, char *env_path, t_main *data_base)
{
	int errcode;
	char *cmd;
	char **cmd_path;
	t_cmd just_a_try;

	errcode = 0;
	//just_a_try.cmd_args[1] = NULL;
	cmd_path = ft_split(env_path, ':');
	cmd = get_cmd(cmd_path, data_base, &just_a_try);
	char *tab[] = {cmd, NULL}; // pour rajouter des arguments tu peux completer ce tableau avec les arguments sous formes de chaines de caracteres attention a bien rajouter NULL en fin de tableau 
	//printf("%s\n", cmd);
	data_base->pid1 = fork();
	if (data_base->pid1 == 0)
		errcode = execve(cmd, tab, env);
	waitpid(data_base->pid1, NULL, 0);
	return (errcode);
}
//fait marcher la commande "history" mais je ne pense pas que l'on puisse utiliser la fonction history_get
int	print_history(void)
{
	int	i;

	i = 1;
	HIST_ENTRY *historyList = NULL;
	historyList = history_get(i);
	while(historyList)
	{
		historyList = history_get(i);
		if (!historyList)
			break;
    	printf("%s\n", historyList->line);
		i++;
	}
	return(0);
}

int	main(int argc, char **argv, char **env)
{
	t_main	data_base;
	(void)argc;
	(void)argv;
	my_header();
	init_signal();
	// charger les argument dans la structures main;
	data_base.env_tab = ft_arraydup(env);
	while (1)
	{
		data_base.my_prompt_line = readline("\033[1;32mMy prompt \033[0m");
		add_history(data_base.my_prompt_line);
		data_base.env_path = find_env_variable(env, "PATH");
		// LEXER // 

		// PARSING // 

		// EXECUTION //

		printf("%d\n", execute(env, data_base.env_path, &data_base));
		if (data_base.my_prompt_line)
			free (data_base.my_prompt_line);
	}
}
