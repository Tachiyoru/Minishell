/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:37 by sleon             #+#    #+#             */
/*   Updated: 2023/02/22 19:15:52 by sleon            ###   ########.fr       */
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
 * @brief check if the cmd that will be executed is a builtin or not
 *
 * @param cmd the cmd to execute
 * @param exec the struct
 * @return int
 */
int	is_builtin(char *cmd, t_pipex *exec)
{
	int	res;

	res = 0;
	if (!ft_strcmp(cmd, "cd"))
		res = b_in_cd(exec->cmd->next, exec->fd[0], exec->fd[1]);
	else if (!ft_strcmp(cmd, "echo"))
		res = b_in_echo(exec->cmd->next, exec->fd[1]);
	else if (!ft_strcmp(cmd, "pwd"))
		res = b_in_pwd(exec->fd[1]);
	return (res);
}
	// else if (!ft_strcmp(cmd, "export"))
	// 	res = b_in_export((*exec)->cmd->next);
	// else if (!ft_strcmp(cmd, "unset"))
	// 	res = b_in_unset((*exec)->cmd->next);
	// else if (!ft_strcmp(cmd, "env"))
	// 	res = b_in_env((*exec)->fd[1]);
	// else if (!ft_strcmp(cmd, "exit"))
	// 	res = b_in_exit((*exec)->cmd->next, cmd);

/**
 * @brief call all the functiun before the exec
 *
 * @param cmd
 */
void	exec_pipex(t_pipex **exec)
{
	t_pipex	*start;
	int		builtin;

	builtin = 0;
	start = *exec;
	while (*exec)
	{
		if ((*exec)->next)
			setup_pipe(*exec);
		if ((*exec)->redir)
			setup_redir(*exec);
		if (!is_builtin((*exec)->cmd->val, (*exec)))
			exec_call((*exec), start);
		if ((*exec)->fd[0] != STDIN_FILENO)
			close((*exec)->fd[0]);
		if ((*exec)->fd[1] != STDOUT_FILENO)
			close((*exec)->fd[1]);
		(*exec) = (*exec)->next;
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
		return ;
	exec_pipex(&cmd);
}
