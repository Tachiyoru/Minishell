/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:08:10 by sleon             #+#    #+#             */
/*   Updated: 2023/03/08 14:08:47 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_signal(void)
{
	if (g_error == 128 + SIGTERM)
		ft_putstr_fd(STDERR_FILENO, "Terminated\n");
	else if (g_error == 128 + SIGSEGV)
		ft_putstr_fd(STDERR_FILENO, "Segmentation fault (core dumped)\n");
	else if (g_error == 128 + SIGQUIT)
		ft_putstr_fd(STDERR_FILENO, "Quit (core dumped)\n");
	else if (g_error == 128 + SIGABRT)
		ft_putstr_fd(STDERR_FILENO, "Aborted (core dumped)\n");
}

void	ret_child(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_error = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_error = 128 + WIFEXITED(status);
		error_signal();
	}
}

void	wait_child_exec(t_pipex *start)
{
	t_pipex	*save;

	while (start)
	{
		signal(SIGINT, SIG_IGN);
		if (start->pid > 0)
			ret_child(start->pid);
		init_signal1();
		save = start;
		start = start->next;
		if (save->fd[0] != STDIN_FILENO)
			close(save->fd[0]);
		if (save->fd[1] != STDOUT_FILENO)
			close(save->fd[1]);
	}
}
