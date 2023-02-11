/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:01:56 by sleon             #+#    #+#             */
/*   Updated: 2023/02/11 13:34:44 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	split_rec(char *line, char **tab, int i)
{
	int	start;
	int	end;

	start = word_start(line);
	end = word_end(line, start);
	(void)i;
	(void)tab;
}

void	split_pars(char *buf)
{
	t_val	*data;
	char	**tab;

	data = NULL;
	tab = NULL;
	split_rec(buf, tab, 0);
}

int	ft_begin2(char **envp)
{
	char	*buf;

	(void)envp;
	while (1)
	{
		buf = readline("Minishell ~");
		if (!buf)
			break ;
		else
		{
			add_history(buf);
			split_pars(buf);
		}
	}
	rl_clear_history();
	write(STDOUT_FILENO, "exit\n", 5);
	return (0);
}
// free(buf); MEMO free ou pas ?
