/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:57:48 by sleon             #+#    #+#             */
/*   Updated: 2023/02/14 15:50:06 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief duplicate the string and returns it
 *
 * @param s the string to duplicate
 * @return a copy malloced
 */
char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;
	int		size;

	size = 0;
	while (s[size])
		size++;
	str = (char *)malloc(sizeof (char) * (size + 1));
	i = 0;
	if (str == 0)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strndup(const char *s, int size)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof (char) * (size + 1));
	i = 0;
	if (str == 0)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
