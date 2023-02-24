/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:01:56 by sleon             #+#    #+#             */
/*   Updated: 2023/02/23 14:25:19 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief split the string and fill the tab via recursive
 *
 * @param line the char* move forward at each call so the recursive dont loop
 * @param tab
 * @param i number of word
 */
void	split_rec(char *line, char ***tab, int i)
{
	int	start;
	int	end;

	start = word_start(line);
	end = word_end(line, start);
	if (end > 0)
	{
		split_rec(line + end, tab, i + 1);
		(*tab)[i] = ft_substr(line, start, end - start);
		if (!(*tab)[i])
			return ;
	}
	if (end == 0)
	{
		(*tab) = ft_calloc(sizeof(char *), i + 1);
		if (!(*tab))
			return ;
		(*tab)[i] = NULL;
	}
}

/**
 * @brief put the value inside every tab of tab in link chain
 *
 * @param tab	tab of tab
 * @param data	linkchain
 */
void	tab_to_list(char **tab, t_val **data)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		set_val_tab(tab[i], data);
}

/**
 * @brief split the string then set it in linkchain
 *
 * @param buf value returned by readline in a char * to split
 */
void	split_pars(char *buf)
{
	t_val	*data;
	char	**tab;

	data = NULL;
	tab = NULL;
	split_rec(buf, &tab, 0);
	tab_to_list(tab, &data);
	free_tab(tab);
	if (data)
		check_token(data);
	return ;
}
