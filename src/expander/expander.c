/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:29:24 by rheck             #+#    #+#             */
/*   Updated: 2024/02/05 13:40:54 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int	is_dollar(const char *input)
{
	int	i;

	i = 0;
	while(input[i])
	{
		if (input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int find_index(const char *input)
{
	int		i;
	int		index;

	i = 0;
	index = 0;
	while(input[i])
	{
		if (input[i] == '$' && input[i + 1] != '\0' && input[i + 1] != ' ')
		{
			while(input[i] != '\0' && input[i] != ' ')
				i++;
			index = i;
		}
		if (input[i] == '\0')
				break;
		i++;
	}
	return (index);
}

char *complete_line(int length_1, const char *input, char *var_name)
{
	char *part_1;
	char *part_2;
	char *var;

	var = getenv(var_name);
	part_1 = malloc(sizeof(char) * (length_1 + 1));
	ft_memcpy(part_1, input, length_1);
	part_1[length_1] = '\0';
	part_2 = ft_strjoin(part_1, var);
	return (ft_strjoin(part_2, &input[find_index(input)]));
}

char *replace_env_variables(const char *input)
{
	int		i;
	int		cursor;
	int		length_1;
	char	*var_name;
	const char	*begin;

	i = 0;
	cursor = 0;
	if (input[0] == '$' && input[1] == '?')
		return(ft_strjoin(ft_itoa(my_global.last_err_code), &input[2]));
	while(input != NULL && input[i] != '\0')
	{
		if (input[i] == '$' && input[i + 1] != '\0' && input[i + 1] != ' ')
		{
			begin = &input[i + 1];
			length_1 = i;
			i++;
			while(input[i] != '\0' && input[i] != ' ')
			{
				cursor++;
				i++;
			}
			var_name = malloc(sizeof(char) * (cursor + 1));
			ft_strlcpy(var_name, begin, cursor + 1);
			if (!getenv(var_name))
				return ("\n");
			if (input[i] == '\0')
				break;
		}
		i++;
	}
	return (complete_line(length_1, input, var_name));
}


void expand_var(t_main *data_base)
{
	int i;
	
	i = 0;
	while(data_base->token_array[i].type != EOF_TOKEN)
	{
		if (is_dollar(data_base->token_array[i].value) && data_base->token_array[i].type != STRING)
			data_base->token_array[i].value = replace_env_variables(data_base->token_array[i].value);			
		i++;
	}
}