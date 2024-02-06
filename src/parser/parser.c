/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:02:19 by rheck             #+#    #+#             */
/*   Updated: 2024/02/06 12:48:35 by mgigot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/mini.h"

t_cmd	*parse_cmd(t_main *data_base)
{
	t_cmd *cmd_line;

	int	i = 0;
	data_base->pipes = count_pipe(data_base->token_array);
	printf("pipes 2 = %d\n", data_base->pipes);
	cmd_line = malloc(sizeof(t_cmd) * (data_base->pipes + 2));
	cmd_line[i] = parse_next_cmd(data_base);
	printf("cmd name %s\n", cmd_line[i].cmd_name);
	while(cmd_line[i].cmd_name != NULL)
	{
		i++;
		cmd_line[i] = parse_next_cmd(data_base);
		printf("cmd name %s\n", cmd_line[i].cmd_name);
	}
	return (cmd_line);
}
int	count_pipe(Token *lexer_list)
{
	int i;
	int	count; 

	i = 0;
	count = 0;
	while(lexer_list[i].type != EOF_TOKEN)
	{
		if(lexer_list[i].type == PIPE)
			count++;
		i++;
	}
	// count++;
	return(count);
}
int	count_args(Token *lexer_list)
{
	int		i;

	i = 0;
	while (lexer_list[i].type != PIPE && lexer_list[i].type != EOF_TOKEN)
	{
		i++;
	}
	return (i);
}

t_cmd   parse_next_cmd(t_main *data_base)
{
    int j = 0;
    char **ret_tab;
	t_cmd ret;
	int		count_arg;

	count_arg = count_args(data_base->token_array + data_base->index);
	if(data_base->token_array[data_base->index].type == PIPE)
	{
		ret_tab = malloc(sizeof(char *) * 2);
		ret_tab[0] = ft_strdup("|");
		ret_tab[1] = NULL;
		ret.cmd_name = ft_strdup("|");
		place_redirection(&ret, data_base, data_base->index);
		data_base->index++;
		return(ret);
	}
	ret_tab = malloc(sizeof(char *) * (count_arg + 1));
	if(data_base->token_array[data_base->index].type == EOF_TOKEN)
	{
		ret.cmd_name = NULL;
		return (ret);
	}
    if(data_base->token_array[data_base->index].type == IDENTIFIER)
    {
        ret_tab[j] = ft_strdup(data_base->token_array[data_base->index].value);
		data_base->index = place_redirection(&ret, data_base, data_base->index);
		data_base->index++;
        while(is_valid_arg(data_base->token_array[data_base->index].type) == 0)
        {
			data_base->index = place_redirection(&ret, data_base, data_base->index);
        	j++;
            ret_tab[j] = ft_strdup(data_base->token_array[data_base->index].value);
			data_base->index++;
		}
    }
	j++;
	printf("j = %d\n", j);
	ret_tab[j] = NULL;
	// for(int x = 0; ret_tab[x] != NULL; x++)
	// {
	// 	printf("%s\n", ret_tab[x]);
	// }
	ret.cmd_name = ft_strdup(ret_tab[0]); 
	ret.cmd_args = ret_tab;
	//free ret_tab ?? 
	return (ret);
	//else commande error ?
}
int	is_valid_arg(TokenType type)
{
	if(type == OPTION || type == VARIABLE || type == STRING || type == NUMBER || type == OPERATOR)
		return (0);
	else
		return (1);
}
int	place_redirection(t_cmd *new_dir, t_main *data_base, int pos)
{
	data_base->redirection += 1;
	if(data_base->token_array[data_base->index].type == OPERATOR)
	{
		if(data_base->token_array[pos].value[0] == '<')
		{
			new_dir->redirection_name = ft_strdup(data_base->token_array[pos + 1].value);
			new_dir->redirection_name2 = ft_strdup(data_base->token_array[pos + 1].value);
			new_dir->redirection = ft_strdup(data_base->token_array[pos].value);
			new_dir->fd_in = 1;
		}
		if(data_base->token_array[pos].value[0] == '>')
		{
			new_dir->redirection_name = ft_strdup(data_base->token_array[pos + 1].value);
			new_dir->redirection_name2 = ft_strdup(data_base->token_array[pos + 1].value);
			new_dir->redirection = ft_strdup(data_base->token_array[pos].value);
			new_dir->fd_out = 1;
		}
		pos += 1;
	}
	else
	{
		new_dir->redirection_name = NULL;
		new_dir->redirection_name2 = NULL;
		new_dir->redirection = NULL;
	}
	return(pos);
}