/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:31:01 by ajeanne           #+#    #+#             */
/*   Updated: 2023/03/31 14:47:46 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_increment_h(char *content, int *i)
{
	(*i)++;
	while (content[*i] != '\'')
	{
		if (!content[*i])
			return (1);
		(*i)++;
	}
	return (0);
}

int	double_increment_h(char *content, int *i)
{
	(*i)++;
	while (content[*i] != '"')
	{
		if (!content[*i])
			return (1);
		(*i)++;
	}
	return (0);
}

int	is_error_qm_h(t_val *data)
{
	int	i;
	int	q;

	q = 0;
	while (data)
	{
		i = -1;
		while (data->val[++i])
		{
			if (data->val[i] == '\'')
			{
				q++;
				if (simple_increment_h(data->val, &i))
					return (1);
			}
			if (data->val[i] == '"')
			{
				q++;
				if (double_increment_h(data->val, &i))
					return (1);
			}
		}
		data = data->next;
	}
	return (q);
}

int	quote_treatment_h(t_val *data)
{
	t_val	*tmp;
	t_val	*tmp_prev;

	tmp = data;
	tmp_prev = NULL;
	while (tmp)
	{
		if (tmp->token == WORD || tmp->token == FD || tmp->token == LIMITOR)
		{
			if (is_error_qm2(tmp->val, tmp))
				return (free_lst(data), 0);
			back_to_positive(tmp);
		}
		else
			tmp_prev = NULL;
		tmp = tmp->next;
	}
	return (0);
}
