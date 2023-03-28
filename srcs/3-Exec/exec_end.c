/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:08:10 by sleon             #+#    #+#             */
/*   Updated: 2023/03/28 01:14:48 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_signal(int *cnt)
{
	if (g_error == 128 + SIGTERM)
		ft_putstr_fd(STDERR_FILENO, "Terminated\n");
	else if (g_error == 128 + SIGSEGV)
		ft_putstr_fd(STDERR_FILENO, "Segmentation fault (core dumped)\n");
	else if (g_error == 128 + SIGQUIT && !(*cnt))
	{
		ft_putstr_fd(STDERR_FILENO, "Quit (core dumped)\n");
		(*cnt)++;
	}
	else if (g_error == 128 + SIGABRT)
		ft_putstr_fd(STDERR_FILENO, "Aborted (core dumped)\n");
}

void	ret_child(int pid, int *cnt)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_error = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_error = 128 + WTERMSIG(status);
		error_signal(cnt);
	}
}

void	wait_child_exec(t_pipex *start)
{
	t_pipex	*save;
	int		cnt;

	cnt = 0;
	while (start)
	{
		signal(SIGINT, SIG_IGN);
		if (start->pid > 0)
			ret_child(start->pid, &cnt);
		init_signal1();
		save = start;
		start = start->next;
		if (save->fd[0] != STDIN_FILENO)
			close(save->fd[0]);
		if (save->fd[1] != STDOUT_FILENO)
			close(save->fd[1]);
		free_lst(save->cmd);
		free_lst(save->redir);
		free(save);
	}
}
