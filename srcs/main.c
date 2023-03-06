/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:24:33 by sleon             #+#    #+#             */
/*   Updated: 2023/03/06 15:56:52 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	main(int ac, char **av, char **envp)
{
	char	*buf;

	(void)av;
	(void)ac;
	store_env(envp);
	set_shlvl();
	init_signal(0);
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
	del_env();
	rl_clear_history();
	write(STDOUT_FILENO, "exit\n", 5);
	return (g_error);
}
