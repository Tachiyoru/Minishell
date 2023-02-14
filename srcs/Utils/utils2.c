/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:57:48 by sleon             #+#    #+#             */
/*   Updated: 2023/02/14 16:11:14 by ajeanne          ###   ########.fr       */
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

char	*var_replacing(int start, int end, char *content, t_env *env)
{
	char	*name;
	char	*dest;
	t_env	*tmp;

	name = ft_substr(content, start + 1, end - (start - 1));
	dest = NULL;
	tmp = env;
	while (tmp && tmp->key != name)
		tmp = tmp->next;
	if (!tmp)
	{
		dest = word_replacing(start, end, content, NULL);
		if (!dest)
			return (NULL);
		return (0);
	}
	dest = word_replacing(start, end, content, tmp->val);
	if (!dest)
		return (NULL);
	return(dest);
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
