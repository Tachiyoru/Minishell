/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:24:33 by sleon             #+#    #+#             */
/*   Updated: 2023/02/13 16:17:34 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	main(int ac, char **av, char **envp)
{
	char	*buf;

	(void)envp;
	(void)av;
	(void)ac;
	buf = NULL;
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
	return (g_error);
}
