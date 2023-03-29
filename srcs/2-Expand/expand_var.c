/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:43:38 by ajeanne           #+#    #+#             */
/*   Updated: 2023/03/29 13:52:42 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Replacing, for being under 25 lines
 *
 * @param dest
 * @param content
 * @param i
 * @param end
 * @return char*
 */
void	end_of_replacing(char **dest, char *content, int i, int end)
{
	while (content && content[end])
	{
		dest[0][i] = content[end];
		end++;
		i++;
	}
}

/**
 * @brief Replacing var by her value
 *
 * @param start
 * @param end
 * @param content
 * @param new_word
 * @return char*
 */
char	*word_replacing_var(int start, int end, char *content, char *new_word)
{
	int		word_size;
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word_size = end - start;
	dest = ft_calloc((ft_strlen(content) - word_size) + ft_strlen(new_word), 1);
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
	end_of_replacing(&dest, content, i + j, end);
	free_wr(content, new_word);
	return (dest);
}

/**
 * @brief Replacing var by her value main
 *
 * @param start
 * @param end
 * @param content
 * @param i
 * @return char*
 */
char	*var_replacing(int start, int end, char *content, int *i)
{
	char	*name;
	char	*dest;
	t_env	*tmp;

	*i = *i;
	name = ft_substr(content, start + 1, end - (start));
	dest = NULL;
	tmp = *get_env();
	while (tmp && ft_strcmp(tmp->key, name))
		tmp = tmp->next;
	free_vr(name);
	if (!tmp)
	{
		dest = word_replacing_var(start, end, content, NULL);
		if (!dest)
			return (NULL);
		return (dest);
	}
	dest = word_replacing_var(start, end, content, ft_strdup(tmp->val));
	if (!dest)
		return (NULL);
	return (dest);
}

/**
 * @brief Unusual case treatment $1, $?
 *
 * @param content
 * @param i
 * @param j
 * @param data
 */
void	unusual_state(char *content, int i, int j, t_val *data)
{
	if (content[(i + j)] && content[(i + j) + 1]
		&& ((content[(i + j) + 1] == '?')))
	{
		j++;
		data->val = word_replacing_var(i, i + j, content, ft_itoa(g_error));
		return ;
	}
	if (content[(i + j)] && content[(i + j) + 1]
		&& ((content[(i + j) + 1] >= '0')
			&& (content[(i + j) + 1] <= '9')))
	{
		j++;
		data->val = word_replacing_var(i, i + j, content, NULL);
		return ;
	}
}

/**
 * @brief Treatment if var exist
 *
 * @param content
 * @param i
 * @param data
 * @param iadd
 * @return int
 */
int	is_var(char *content, int i, t_val *data, int *iadd)
{
	int	j;

	j = 0;
	if (content[(i + j) + 1] && ((content[(i + j) + 1] != '?'))
		&& ((content[(i + j) + 1] < '0') || (content[(i + j) + 1] > '9')))
	{
		while (content[(i + j) + 1]
			&& ((content[(i + j) + 1] >= 'A' && content[(i + j) + 1] <= 'Z')
				|| (content[(i + j) + 1] >= 'a' && content[(i + j) + 1] <= 'z')
				|| ((content[(i + j) + 1] >= '0')
					&& (content[(i + j) + 1] <= '9'))
				|| content[(i + j) + 1] == '_'))
			j++;
		data->val = var_replacing(i, i + j, content, iadd);
		if (!data->val)
			return (1);
		return (0);
	}
	unusual_state(content, i, j, data);
	return (0);
}
