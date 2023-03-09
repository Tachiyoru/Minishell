/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 08:36:31 by ajeanne           #+#    #+#             */
/*   Updated: 2023/03/09 08:37:23 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*h_word_replacing_var(int start, int end, char *content, char *new_word)
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
	printf("%s, %s, %s\n", content, new_word, dest);
	end++;
	dest = end_of_replacing(dest, content, i + j, end);
	free_wr(content, new_word);
	return (dest);
}

char	*h_var_replacing(int start, int end, char *line)
{
	t_env	*env;

	env = *get_env();
	while (ft_strncmp(line + start + 1, env->key, end))
		env = env->next;
	line = h_word_replacing_var(start, end, line, env->val);
	return (line);
}
