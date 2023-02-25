/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:55:50 by sleon             #+#    #+#             */
/*   Updated: 2023/02/25 02:24:02 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief make a new string starting at start from a string
 *
 * @param s
 * @param start
 * @param len
 * @return the new str
 */
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	y;

	if (s == 0)
		return (0);
	if (start > (size_t)ft_strlen((char *)s))
		return (ft_strdup(""));
	if (ft_strlen((char *)s) - start < len)
		len = ft_strlen((char *)s) - start;
	str = (char *)malloc(sizeof (char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	y = 0;
	while (s[i])
	{
		if (i >= start && y < len)
		{
			str[y++] = s[i];
		}
		i++;
	}
	str[y] = '\0';
	return (str);
}

int	lst_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	lst_size_val(t_val *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	ft_putstr_fd(int fd, char *s)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

t_env	*lst_env_new(char *key, char *val)
{
	t_env	*new_element;

	new_element = malloc(sizeof(t_env));
	new_element->key = ft_strdup(key);
	new_element->val = ft_strdup(val);
	if (!new_element)
		return (NULL);
	new_element->next = NULL;
	return (new_element);
}
