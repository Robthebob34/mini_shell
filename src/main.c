/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:39 by rheck             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/06 11:12:52 by rheck            ###   ########.fr       */
=======
/*   Updated: 2024/02/07 11:06:01 by mgigot           ###   ########.fr       */
>>>>>>> ccbebe2dc1930d6da0d904b52f375375cb70e063
/*                                                                            */
/******************************************************************************/

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

<<<<<<< HEAD
	errcode = 0;
	cmd_path = ft_split(data_base->env_path, ':');
	cmd = get_cmd(cmd_path, data_base, data_base->cmds_list);
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
=======
//fait marcher la commande "history" mais je ne pense pas que l'on puisse utiliser la fonction history_get
int	print_history(void)
{
	int	i;
>>>>>>> ccbebe2dc1930d6da0d904b52f375375cb70e063

int	count_token(Lexer *lexer, char *prompt)
{
	int	result;
	Token token_count;

	token_count.type = KEYWORD;
	result = 0;
	init_lexer(lexer, prompt);
	int i = 0;
	while(token_count.type != EOF_TOKEN)
	{
		token_count = get_next_token(lexer);
		printf("type : %d   value : %s\n", token_count.type, token_count.value);
		result++;
		i++;
	}
	return (result);
}
int	reset_data_base(t_main *data_base)
{
	data_base->index = 0;
	data_base->fork_index = 0;
	data_base->redirection = 0;
	data_base->heredoc = 0;
	data_base->pipes = 0;
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
			printf("token : %s, type : %u\n", data_base.token_array[i].value, data_base.token_array[i].type);
		}
		// END LEXER //
		expand_var(&data_base);
		// START PARSING//
		data_base.cmds_list = parse_cmd(&data_base);
		// END PARSING //
		super_history(data_base.my_prompt_line);
		data_base.env_path = find_env_variable(data_base.env_tab, "PATH");


		// EXECUTION //

		prepare_execute(&data_base);
		if (data_base.my_prompt_line)
			free (data_base.my_prompt_line);
		reset_data_base(&data_base);
	}
}
