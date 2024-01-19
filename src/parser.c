/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:02:19 by rheck             #+#    #+#             */
/*   Updated: 2024/01/04 13:40:51 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"
t_cmd	*parse_cmd(t_main *data_base)
{
	t_cmd *cmd_line;

	int	i = 0;
	cmd_line = malloc(sizeof(t_cmd) * (count_cmd(data_base->token_array) + 1));
	cmd_line[i] = parse_next_cmd(data_base);
	while(cmd_line[i].cmd_name != NULL)
	{
		i++;
		cmd_line[i] = parse_next_cmd(data_base);
	}
	//printf("%s\n", cmd_line[0].cmd_args[1]);
	return (cmd_line);
}
int	count_cmd(Token *lexer_list)
{
	int i;
	int	count; 

	i = 0;
	count = 0;
	while(lexer_list[i].type != EOF_TOKEN)
	{
		if(lexer_list[i].type == OPERATOR)
			count++;
		i++;
	}
	count++;
	return(count);
}
int	count_args(Token *lexer_list)
{
	int		i;

	i = 0;
	while (lexer_list[i].type != OPERATOR && lexer_list[i].type != EOF_TOKEN)
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

	ret_tab = malloc(sizeof(char *) * (count_args(data_base->token_array) + 1));
	if(data_base->token_array[data_base->index].type == EOF_TOKEN)
	{
		ret.cmd_name = NULL;
		return (ret);
	}
    if(data_base->token_array[data_base->index].type == IDENTIFIER)
    {
        ret_tab[j] = ft_strdup(data_base->token_array[data_base->index].value);
		//ft_lexerdelone(&data_base->token_array, i);
		data_base->index++;
        while(is_valid_arg(data_base->token_array[data_base->index].type) == 0)
        {
        	j++;
            ret_tab[j] = ft_strdup(data_base->token_array[data_base->index].value);
			//ft_lexerdelone(&data_base->token_array, i);
			data_base->index++;
		}
    }
	j++;
	ret_tab[j] = NULL;
	//for(int x = 0; ret_tab[x] != NULL; x++)
	//{
	//	printf("%s\n", ret_tab[x]);
	//}
	ret.cmd_name = ft_strdup(ret_tab[0]);
	ret.cmd_args = ret_tab;
	//free ret_tab ?? 
	return (ret);
	//else commande error ?
}
int	is_valid_arg(TokenType type)
{
	if(type == OPTION || type == VARIABLE || type == STRING || type == NUMBER)
		return (0);
	else
		return (1);
}