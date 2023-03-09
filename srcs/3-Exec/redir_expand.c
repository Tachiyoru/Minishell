/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:57:37 by ajeanne           #+#    #+#             */
/*   Updated: 2023/03/09 09:02:34 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	h_var_exist(char *line, int i, int j)
{
	t_env	*env;

	env = *get_env();
	while (env && ft_strncmp(line + i + 1, env->key, j))
		env = env->next;
	if (!env)
		return (1);
	return (0);
}

int	h_len_word(char *line, int i)
{
	int	j;

	j = 0;
	while (line[(i + j) + 1]
			&& ((line[i] >= '0' && line[i] <= '9')
				|| (line[(i + j) + 1] >= 'A' && line[(i + j) + 1] <= 'Z')
				|| (line[(i + j) + 1] >= 'a' && line[(i + j) + 1] <= 'z')
				|| line[(i + j) + 1] == '_'))
				j++;
	return (j);
}

char	*h_replacing_var(char *line, int i, int *iadd)
{
	int		len;

	len = h_len_word(line, i);
	if (line[i + 1] && (line[i + 1] >= '0' && line[i + 1] <= '9'))
	{
		*iadd = *iadd - 1;
		return (h_word_replacing_var(i, i + 1, line, ""));
	}
	if (h_var_exist(line, i, len))
	{
		*iadd = *iadd - 1;
		return (h_word_replacing_var(i, i + len, line, ""));
	}
	return(h_var_replacing(i, i + len, line));
}

char	*h_expand_var(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			line = h_replacing_var(line, i, &i);
		if (!line[i])
			break ;
		i++;
	}
	return (line);
}
