/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:57:48 by sleon             #+#    #+#             */
/*   Updated: 2023/02/15 16:12:13 by sleon            ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*word_replacing(int start, int end, char *content, char *new_word)
{
	int		word_size;
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word_size = end - start;
	dest = calloc((ft_strlen(content) - word_size) + ft_strlen(new_word), 1);
	if (!dest)
		return (NULL);
	while (content && i < start)
	{
		dest[i] = content[i];
		i++;
	}
	while (new_word && new_word[j])
	{
		dest[i + j] = new_word[j];
		j++;
	}
	end++;
	while (content && content[end])
	{
		dest[i + j] = content[end];
		end++;
		i++;
	}
	return (dest);
}

/**
 * @brief duplicate only the size received from the string
 *
 * @param s the string
 * @param size the size
 * @return the new string of size == size
 */
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
