/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:48:54 by sleon             #+#    #+#             */
/*   Updated: 2023/02/11 13:22:07 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_readline(char *str)
{
	str = readline("~~");
	add_history(str);
	return (str);
}

int	ft_begin(char **envp)
{
	t_val	*data;
	char	*buf;

	(void)envp;
	data = ft_calloc(sizeof(t_val), 1);
	buf = NULL;
	while (1)
	{
		buf = ft_readline(buf);
		if (!buf)
			return (0);
		else
			parsing(data, buf);
		free(buf);
	}
	return (0);
}

void	parsing(t_val *data, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < ft_strlen2(str))
	{
		while (str[j] != '\n' && str[j] != '"' && str[j] != '<'
			&& str[j] != '>' && str[j] != ' ' && str[j] != '|')
			j++;
		if (str[j] == '"')
		{
			i = j++;
			while (str[j] != '"')
				j++;
			set_val(str, &data, i + 1, j - i - 1);
			j++;
			if (str[j] == ' ')
					j++;
			i = j - 1;
		}
		else if ((str[j] == ' ' && str[j + 1] == '>') || str[j] == '>')
		{
			if (str[j] == '>')
			{
				if (str[j + 1] == '>')
				{
					set_val(str, &data, i + 1, j - i + 1);
					j += 2;
				}
				else
				{
					set_val(str, &data, i + 1, j - i);
					j++;
				}
				if (str[j] == ' ')
					j++;
				i = j - 1;
			}
			else
			{
				set_val(str, &data, i + 1, j - i - 1);
				j++;
				if (str[j] == ' ')
					j++;
				i = j - 1;
			}
		}
		else if (str[j] == '<' || (str[j] == ' ' && str[j + 1] == '<'))
		{
			if (str[j] == '<')
			{
				if (str[j + 1] == '<')
				{
					set_val(str, &data, i + 1, j - i + 1);
					j += 2;
				}
				else
				{
					set_val(str, &data, i + 1, j - i);
					j++;
				}
				if (str[j] == ' ')
					j++;
				i = j - 1;
			}
			else
			{
				set_val(str, &data, i + 1, j - i - 1);
				j++;
				if (str[j] == ' ')
					j++;
				i = j - 1;
			}
		}
		else if ((str[j] == ' ' && str[j + 1] == '|') || str[j] == '|')
		{
			if (str[j] == '|')
			{
				set_val(str, &data, i + 1, j - i);
				j++;
				if (str[j] == ' ')
					j++;
			}
			else
			{
				set_val(str, &data, i, j - i);
				j++;
			}
		}
		else if (str[j] == ' ')
		{
			set_val(str, &data, i, j - i);
			j++;
		}
		i = j - 1;
	}
	printlist(data);
}

// salut decverv >> "fr4 def <> rrg" << gtfrv >>
//                                           42
void	printlist(t_val *data)
{
	while (data)
	{
		printf("valeur dans data = %s\n", data->val);
		data = data->next;
	}
}

void	set_val(char *str, t_val **data, int i, int size)
{
	t_val	*new;
	t_val	*tmp;
	int		s;

	s = 0;
	tmp = *data;
	new = ft_calloc(sizeof(t_val), 1);
	new->val = ft_calloc(sizeof(char), (size + 1));
	while (size--)
	{
		new->val[s] = str[i];
		i++;
		s++;
	}
	if (!tmp->val)
	{
		tmp = new;
		*data = tmp;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
