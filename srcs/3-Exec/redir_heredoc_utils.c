/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:04:58 by ajeanne           #+#    #+#             */
/*   Updated: 2023/03/28 12:34:06 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_hreplacing_var(int start, int end, char *content, char *new_word)
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
		dest[i + j] = new_word[j];
		j++;
	}
	end++;
	end_of_replacing(&dest, content, i + j, end);
	free_wr(content, new_word);
	return (dest);
}

void	incr_exp_h_var(int *j, int i, char *line)
{
	while (line[i + (*j)] && line[i + (*j) + 1]
		&& ((line[i + (*j) + 1] >= 'A' && line[i + (*j) + 1] <= 'Z')
			|| (line[i + (*j) + 1] >= 'a' && line[i + (*j) + 1] <= 'z')
			|| line[i + (*j) + 1] == '_' || line[i + (*j) + 1] == '?'))
			(*j)++;
}

void	unusual_case_exp_h_var(char *name, char **new_word)
{
	if (!ft_strcmp(name, "?"))
		*new_word = ft_itoa(g_error);
	else
		*new_word = ft_strdup(find_env(name));
}

char	*expand_heredoc_var(char *line)
{
	int		i;
	int		j;
	char	*new_word;
	char	*name;
	char	*dest;

	i = 0;
	j = 0;
	while (line && line[i])
	{
		while (line && line[i] && line[i] != '$')
			i++;
		if (line && !line[i])
			break ;
		incr_exp_h_var(&j, i, line);
		name = ft_substr(line, i + 1, j);
		if (!find_env(name))
			return (free(name), line);
		unusual_case_exp_h_var(name, &new_word);
		dest = word_hreplacing_var(i, i + j, line, new_word);
		if (name)
			free(name);
		line = dest;
		i = 0;
		j = 0;
	}
	return (dest);
}
