/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:04:58 by ajeanne           #+#    #+#             */
/*   Updated: 2023/03/11 14:34:27 by ajeanne          ###   ########.fr       */
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

char	*expand_heredoc_var(char *line)
{
	int		i;
	int		j;
	char	*new_word;
	char	*name;
	char	*dest;
	
	i = 0;
	j = 0;
	dest = NULL;
	name = NULL;
	new_word = NULL;
	while (line && line[i])
	{
		while (line && line[i] && line[i] != '$')
			i++;
		while (line[i + j] && line[(i + j) + 1]
				&& ((line[(i + j) + 1] >= 'A' && line[(i + j) + 1] <= 'Z')
					|| (line[(i + j) + 1] >= 'a' && line[(i + j) + 1] <= 'z')
					|| line[(i + j) + 1] == '_'))
			j++;
		name = ft_substr(line, i + 1, j);
		new_word = find_env(name);
		if (name)
			free(name);
		dest = word_hreplacing_var(i, i + j, line, new_word);
		line = dest;
		if (line[i])
			i = 0;
		j = 0;
	}
	return (dest);
}