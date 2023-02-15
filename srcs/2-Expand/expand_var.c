/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:43:38 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/15 19:04:08 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*end_of_replacing(char *dest, char *content, int i, int end)
{
	while (content && content[end])
	{
		dest[i] = content[end];
		end++;
		i++;
	}
	return (dest);
}

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
	dest = end_of_replacing(dest, content, i + j, end);
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
		if (content)
			free(content);
		return (dest);
	}
	dest = word_replacing_var(start, end, content, tmp->val);
	if (!dest)
		return (NULL);
	if (content)
		free(content);
	return (dest);
}

int	is_var(char *content, int i, t_val *data, t_env *env)
{
	int	j;

	j = 0;
	while (content[i + j] && ((content[i + j] >= 'A' && content[i + j] <= 'Z')
			|| (content[i + j] >= 'a' && content[i + j] <= 'z')
			|| content[i + j] == '_' || content[i + j] == '$'))
		j++;
	j--;
	data->val = var_replacing(i, i + j, content, env);
	if (!data->val)
		return (1);
	return (0);
}
