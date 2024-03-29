/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:39 by rheck             #+#    #+#             */
/*   Updated: 2024/02/13 11:39:53 by mgigot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/mini.h"

int	my_header(int argc, char **argv)
{
	(void)argc;
	(void)argv;
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
	int i = 0;
	my_header(argc, argv);
	init_signal();
	init_shell(env, &data_base);
	data_base.env_tab = ft_arraydup(env);
	while (1)
	{
		i = 0;
		data_base.my_prompt_line = readline("\033[1;32mMy prompt \033[0m");
		data_base.token_array = malloc(sizeof(Token) * count_token(&lexer, data_base.my_prompt_line) + 1);
		init_lexer(&lexer, data_base.my_prompt_line);
		data_base.token_array[i] = get_next_token(&lexer);
		while (data_base.token_array[i].type != 5)
		{
			i++;
			data_base.token_array[i] = get_next_token(&lexer);
			printf("token : %s, type : %u\n", data_base.token_array[i].value, data_base.token_array[i].type);
		}
		expand_var(&data_base);
		data_base.cmds_list = parse_cmd(&data_base);
		super_history(data_base.my_prompt_line);
		data_base.env_path = find_env_variable(data_base.env_tab, "PATH");
		prepare_execute(&data_base);
		if (data_base.my_prompt_line)
			free (data_base.my_prompt_line);
		reset_data_base(&data_base);
	}
}
