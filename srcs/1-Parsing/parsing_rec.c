/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:01:56 by sleon             #+#    #+#             */
/*   Updated: 2023/02/13 08:52:01 by ajeanne          ###   ########.fr       */
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
	}
	if (end == 0)
	{
		(*tab) = ft_calloc(sizeof(char *), i + 1);
		if (!(*tab))
			return ;
		(*tab)[i] = NULL;
	}
}
// TODO Allouer le tableau avant de le remplir ?
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
// TODO On ne devrait pas faire avancer data avant de l'envoyer ?
void	print_list(t_val *data)
{
	while (data)
	{
		printf("%s \n", data->val);
		data = data->next;
	}
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
	print_list(data);
	// free_tab(tab);
	if (data)
		check_token(data);
	return ;
}
	// TODO On free le tab ?
	// TODO call token
