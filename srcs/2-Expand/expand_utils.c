/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:37:20 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/25 03:25:11 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add token in list
 *
 * @param content
 * @param next
 * @return t_val*
 */
t_val	*ft_lstnew_token(void *content, t_val *next)
{
	t_val	*new_element;

	new_element = malloc(sizeof(t_val));
	if (!new_element)
		return (NULL);
	new_element->val = content;
	new_element->token = WORD;
	new_element->next = next;
	return (new_element);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_putchar_err(char c)
{
	write(STDERR_FILENO, &c, 1);
}
