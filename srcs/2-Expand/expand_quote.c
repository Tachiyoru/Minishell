/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:53:23 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/13 16:19:29 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	right_nb_quote(char *content)
{
	int		i;
	int		nb_quotes;
	char	c;

	i = 0;
	nb_quotes = 0;
	c = 0;
	if (content[0] == '\'')
		c = '\'';
	else
		c = '"';
	while (content[i])
	{
		if (content[i] == c)
			nb_quotes++;
		i++;
	}
	return (nb_quotes);
}

int	simple_quote_treat(char *content, t_val *val)
{
	int		i;
	int		j;
	int		q_nb;
	char	*dest;

	i = -1;
	j = 0;
	q_nb = right_nb_quote(content);
	if (q_nb % 2)
		return (msg("Quote error wrong quotes number"), 0);
	dest = ft_calloc(ft_strlen(content) - q_nb, 1);
	if (!dest)
		return (0);
	while (content[++i])
	{
		if (content[i] && content[i] != '\'')
		{
			dest[j] = content[i];
			j++;
		}
	}
	free(val->val);
	val->val = dest;
	return (1);
}

int	double_quote_treat(char *content, t_val *val)
{
	int	i;

	i = 0;
	if (right_nb_quote(content) % 2)
		return (msg("Quote error wrong quotes number"), 0);
	while (content[i])
	{

	}
}

int	quote_dispatcher(t_val *val)
{
	t_val	*tmp;

	tmp = val;
	while (tmp)
	{
		if (tmp->token == WORD && tmp->val[0] == '"')
		{
			double_quote_treat(tmp->val, tmp);
		}
		else if (tmp->token == WORD && tmp->val[0] == '\'')
		{
			simple_quote_treat(tmp->val, tmp);
		}
		tmp = tmp->next;
	}

}
