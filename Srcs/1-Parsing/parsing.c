/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:48:54 by sleon             #+#    #+#             */
/*   Updated: 2023/02/08 19:00:04 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../GNL/get_next_line.h"

int	ft_begin(void)
{
	char	*buf;

	while (1)
	{
		write(STDIN_FILENO, "~", 1);
		buf = get_next_line(0, 0);
		if (!buf)
			return (0);
		else
			parsing(buf);
		free(buf);
	}
	get_next_line(0, 1);
	return (0);
}

void	parsing(char *str)
{
	t_val	*data = NULL;
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		j = i;
		while (str[j] != ' ' || str[j] != '('
			|| str[j] != '|' || str[j] != '&')
			j++;
		if (str[j] == ' ')
			set_val(str, data, i, j - i);
		else if (str[j] == '(')
		{
			while (str[j] != ')')
				j++;
			set_val(str, data, i, j - i);
		}
		else if (str[j] == '|')
			set_val(str, data, i, 1);
		else if (str[j] == '&')
			set_val(str, data, i, 2);
		j++;
		i = j;
	}
	printlist(data);
}

void	printlist(t_val *data)
{
	while (data)
	{
		printf("valeur dans data = %s\n", data->val);
		data = data->next;
	}
}

void	set_val(char *str, t_val *data, int i, int size)
{
	t_val	*new;
	int		j = i;

	new = ft_calloc(sizeof(t_val), 1);
	new->val = ft_calloc(sizeof(char), (size + 1));
	while (size--)
	{
		new->val[j] = str[j];
		j++;
	}
	if (!data)
		data = new;
	else
	{
		while (data->next)
			data = data->next;
		data->next = new;
	}
}
