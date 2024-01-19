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
int	execute(char **env, t_main *data_base)
{
	int errcode;
	char *cmd;
	char **cmd_path;
	t_cmd just_a_try;

	errcode = 0;
	cmd_path = ft_split(data_base->env_path, ':');
	cmd = get_cmd(cmd_path, data_base, &just_a_try);
	if(!cmd)
	{
		printf("no cmd return\n");
		return(0);
	}
	//printf("%s\n", cmd);
	//printf("%s\n", data_base->cmds_list[0].cmd_args[1]);
	data_base->pid1 = fork();
	if (data_base->pid1 == 0)
		errcode = execve(cmd, data_base->cmds_list->cmd_args, env);
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
int	count_token(Lexer *lexer, char *prompt)
{
	int	result;
	Token token_count;

	token_count.type = KEYWORD;
	result = 0;
	init_lexer(lexer, prompt);
	while(token_count.type != EOF_TOKEN)
	{
		token_count = get_next_token(lexer);
		result++;
	}
	return (result);
}
int	reset_data_base(t_main *data_base)
{
	data_base->index = 0;
	return(0);
}
int	main(int argc, char **argv, char **env)
{
	t_main	data_base;
	Lexer lexer;
	(void)argc;
	(void)argv;
	int i = 0;
	my_header();
	init_signal();
	init_shell(env, &data_base);
	data_base.env_tab = ft_arraydup(env);
	while (1)
	{
		i = 0;
		data_base.my_prompt_line = readline("\033[1;32mMy prompt \033[0m");
		//START LEXER //

		data_base.token_array = malloc(sizeof(Token) * count_token(&lexer, data_base.my_prompt_line) + 1);
		init_lexer(&lexer, data_base.my_prompt_line);
		data_base.token_array[i] = get_next_token(&lexer);
		while (data_base.token_array[i].type != 5)
		{
			i++;
			data_base.token_array[i] = get_next_token(&lexer);
			//printf("token : %s, type : %u\n", data_base.token_array[i].value, data_base.token_array[i].type);
		}
		// END LEXER //

		// START PARSING//
		data_base.cmds_list = parse_cmd(&data_base);
	//	printf("%s\n", data_base.cmds_list->cmd_args[1]);
		// END PARSING //
		add_history(data_base.my_prompt_line);
		add_myhistory(data_base.my_prompt_line);
		data_base.env_path = find_env_variable(env, "PATH");


		// EXECUTION //

		printf("%d\n", execute(env, &data_base));
		if (data_base.my_prompt_line)
			free (data_base.my_prompt_line);
		reset_data_base(&data_base);
	}
}
