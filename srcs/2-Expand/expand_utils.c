/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:37:20 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/14 23:05:39 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_replacing_var(int start, int end, char *content, char *new_word)
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
		dest[i + j] = new_word[j] * -1;
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

	name = ft_substr(content, start + 1, end - (start));
	dest = NULL;
	tmp = env;
	while (tmp && ft_strcmp(tmp->key, name))
		tmp = tmp->next;
	if (!tmp)
	{
		dest = word_replacing_var(start, end, content, NULL);
		if (!dest)
			return (NULL);
		return (dest);
	}
	dest = word_replacing_var(start, end, content, tmp->val);
	if (!dest)
		return (NULL);
	return(dest);
}

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

void	ft_lstdelone_data(t_val *lst)
{
	
	free(lst);
	lst = NULL;
}
