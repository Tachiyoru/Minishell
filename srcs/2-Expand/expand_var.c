/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:43:38 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/16 00:36:49 by ajeanne          ###   ########.fr       */
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

char	*var_replacing(int start, int end, char *content)
{
	char	*name;
	char	*dest;
	t_env	*tmp;

	name = ft_substr(content, start + 1, end - (start));
	dest = NULL;
	tmp = *get_env();
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

void	unusual_state(char *content, int i, int j, t_val *data)
{
	if (content[(i + j) + 1] && ((content[(i + j) + 1] == '?')))
	{
		j++;
		data->val = word_replacing_var(i, i + j, content, ft_itoa(g_error));
	}
	if (content[(i + j) + 1] && ((content[(i + j) + 1] >= '0')
			&& (content[(i + j) + 1] <= '9')))
	{
		j++;
		data->val = word_replacing_var(i, i + j, content, NULL);
	}
}

int	is_var(char *content, int i, t_val *data)
{
	int	j;

	j = 0;
	if (content[(i + j) + 1] && ((content[(i + j) + 1] != '?'))
		&& ((content[(i + j) + 1] < '0') && (content[(i + j) + 1] > '9')))
	{
		while (content[(i + j) + 1]
			&& ((content[(i + j) + 1] >= 'A' && content[(i + j) + 1] <= 'Z')
				|| (content[(i + j) + 1] >= 'a' && content[(i + j) + 1] <= 'z')
				|| content[(i + j) + 1] == '_'))
			j++;
		data->val = var_replacing(i, i + j, content);
		if (!data->val)
			return (1);
	}
	unusual_state(content, i, j, data);
	return (0);
}
