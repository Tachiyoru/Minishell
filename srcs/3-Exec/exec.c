/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:37 by sleon             #+#    #+#             */
/*   Updated: 2023/03/11 14:59:59 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_call2(t_pipex *exec, t_pipex *start)
{
	char	**cmd;
	char	**env;
	char	*path;

	(void)start;
	check_fd(exec);
	env = make_env_tab();
	cmd = make_cmd_tab(exec->cmd);
	path = fillpath(exec, env);
	free_lst_exec(start);
	if (path)
	{
		init_signal2();
		execve(path, cmd, env);
	}
	if (env)
		free_tab(env);
	if (cmd)
		free_tab(cmd);
	del_env();
	exit(g_error);
}

/**
 * @brief create child process give him his list of action so that he can
 * execute his cmd
 *
 * @param exec the cmd
 * @param start the whole struct to free in the child
 */
void	exec_call(t_pipex *exec, t_pipex *start)
{
	pid_t	pid;

	g_error = 0;
	if (!exec->cmd->val)
		return ;
	pid = fork();
	if (pid == -1)
		printf("Error fork on cmd = %s\n", exec->cmd->val);
	else if (pid == 0)
		exec_call2(exec, start);
	else
		exec->pid = pid;
}

/**
 * @brief call all the functiun before the exec
 *
 * @param cmd
 */
void	exec_pipex(t_pipex **exec)
{
	t_pipex	*start;
	int		error_check;

	error_check = 1;
	start = *exec;
	while (*exec)
	{
		if ((*exec)->next)
			setup_pipe(*exec);
		if ((*exec)->redir)
			error_check = setup_redir(*exec);
		if (error_check == -1)
			break ;
		if (error_check && !is_builtin((*exec)->cmd->val, (*exec)))
			exec_call((*exec), start);
		if ((*exec)->fd[0] != STDIN_FILENO)
			close((*exec)->fd[0]);
		if ((*exec)->fd[1] != STDOUT_FILENO)
			close((*exec)->fd[1]);
		(*exec) = (*exec)->next;
	}
	wait_child_exec(start);
}

/**
 * @brief make a new struct, each node is for a pipe
 *
 * @param data the former linkchain not pipe separated
 * @param exec final linkchain one node at a time
 * @return int
 */
int	make_struct_exec(t_val *data, t_pipex **exec)
{
	t_pipex	*head;
	t_val	*save;

	save = data;
	head = *exec;
	while (data)
	{
		if (data->token == WORD)
			add_word(exec, &data);
		else if (data->token == PIPE)
		{
			if (!init_cmd(exec))
				return (0);
			save = data->next;
			free(data->val);
			free(data);
			data = save;
			(*exec) = (*exec)->next;
		}
		else
			add_redir(exec, &data);
	}
	*exec = head;
	return (1);
}

/**
 * @brief call functiun to make a proper linkchain wich fit to the exec
 *	then send it to execpipex
 *
 * @param data old linkchain
 */
void	exec(t_val	*data)
{
	t_pipex	*cmd;

	cmd = NULL;
	if (!init_cmd(&cmd))
		return ;
	if (!make_struct_exec(data, &cmd))
		return ;
	if (!cmd)
	{
		free_lst(data);
		return ;
	}
	exec_pipex(&cmd);
}
	// free_lst_exec(cmd);
	// free_lst(data);
