/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:04:39 by sleon             #+#    #+#             */
/*   Updated: 2023/03/11 13:02:28 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief look for the string PATH= in an other string
 *
 * @param big big string from env that may contain PATH=
 * @param little PATH=
 * @param len
 * @return char*
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief count the number of word for the malloc
 *
 * @param str
 * @param set
 * @return int
 */
int	word_count(char *str, char set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == set)
			i++;
		while (str[i] && str[i] != set)
		{
			if (str[i + 1] == set || str[i + 1] == '\0')
				j++;
			i++;
		}
	}
	return (j);
}

/**
 * @brief count the number of char to copy
 *
 * @param str
 * @param set
 * @param pos
 * @return int
 */
int	char_count(char *str, char set, int pos)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && str[i] == set)
			i++;
		while (str[i] && str[i] != set)
		{
			if (j == pos)
				k++;
			if (str[i + 1] == set || str[i + 1] == '\0')
				j++;
			i++;
		}
	}
	return (k);
}

/**
 * @brief set up the words in the tab
 *
 * @param str
 * @param tab
 * @param set
 * @param pos
 * @return char*
 */
char	*ft_putword(char *str, char *tab, char set, int pos)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && str[i] == set)
			i++;
		while (str[i] && str[i] != set)
		{
			if (j == pos)
			{
				tab[k] = str[i];
				k++;
			}
			if (str[i + 1] == set || str[i + 1] == '\0')
				j++;
			i++;
		}
	}
	tab[k] = '\0';
	return (tab);
}

/**
 * @brief split used for aking the path of cmd
 *
 * @param str
 * @param set
 * @return char**
 */
char	**ft_split2(char	*str, char set)
{
	int		j;
	char	**tab;

	j = 0;
	if (!str)
		return (NULL);
	tab = ft_calloc(sizeof(char *), word_count(str, set) + 1);
	if (!tab)
		return (NULL);
	while (j < word_count(str, set))
	{
		tab[j] = ft_calloc(sizeof(char), char_count(str, set, j));
		if (!tab[j])
			return (free_tab(tab), NULL);
		tab[j] = ft_putword(str, tab[j], set, j);
		j++;
	}
	tab[j] = 0;
	free(str);
	return (tab);
}
