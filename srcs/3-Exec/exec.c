/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:37 by sleon             #+#    #+#             */
/*   Updated: 2023/02/20 17:48:52 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_call(t_pipex *exec, t_pipex *start)
{
	pid_t	pid;
	char	**cmd;
	char	**env;
	char	*path;

	(void)start;
	g_error = 0;
	if (!exec->cmd->val)
		return ;
	pid = fork();
	if (pid == -1)
		printf("Error fork on cmd = %s\n", exec->cmd->val);
	else if (pid == 0)
	{
		check_fd(exec);
		env = make_env_tab();
		cmd = make_cmd_tab(exec->cmd);
		path = pathfinder(exec->cmd->val, env);
		if (path)
			execve(path, cmd, env);
		exit(g_error);
	}
	else
		exec->pid = pid;
}

/**
 * @brief call all the functiun before the exec
 *
 * @param cmd
 */
void	exec_pipex(t_pipex **cmd)
{
	t_pipex	*start;
	int		builtin;

	builtin = 0;
	start = *cmd;
	while (*cmd)
	{
		if ((*cmd)->next)
			setup_pipe(*cmd);
		if ((*cmd)->redir)
			setup_redir(*cmd);
		if (!builtin)
			exec_call((*cmd), start);
		// if ((*cmd)->fd != STDIN_FILENO)
		// 	close((*cmd)->fd[0]);
		// if ((*cmd)->fd != STDOUT_FILENO)
		// 	close((*cmd)->fd[1]);
		(*cmd) = (*cmd)->next;
	}
	while (start)
	{
		waitpid(start->pid, NULL, 0);
		start = start->next;
	}
}
//check if the functiun called is a builtin in exec_pipex

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
	if (!init_cmd(exec))
		return (0);
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
	if (!make_struct_exec(data, &cmd))
		return ;
	if (!cmd)
		return ;
	exec_pipex(&cmd);
}
