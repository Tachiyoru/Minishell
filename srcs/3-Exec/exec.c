/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:37 by sleon             #+#    #+#             */
/*   Updated: 2023/03/06 17:05:40 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	**cmd;
	char	**env;
	char	*path;

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
		path = fillpath(exec, env);
		free_lst_exec(start);
		if (path)
		{
			init_signal(1);
			execve(path, cmd, env);
		}
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
		res = b_in_cd(exec->cmd->next);
	else if (!ft_strcmp(cmd, "echo"))
		res = b_in_echo(exec->cmd->next, exec->fd[1]);
	else if (!ft_strcmp(cmd, "pwd"))
		res = b_in_pwd(exec->fd[1]);
	else if (!ft_strcmp(cmd, "exit"))
		res = b_in_exit(exec->cmd->next, exec);
	else if (!ft_strcmp(cmd, "unset"))
	{
		while (exec->cmd->next)
		{
			res = unset_cmd(exec->cmd->next->val);
			exec->cmd->next = exec->cmd->next->next;
		}
	}
	return (is_builtin2(cmd, exec, res));
}

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
		init_signal(0);
		save = start;
		start = start->next;
		if (save->fd[0] != STDIN_FILENO)
			close(save->fd[0]);
		if (save->fd[1] != STDOUT_FILENO)
			close(save->fd[1]);
		// free_lst(save->redir);
		// free_lst(save->cmd);
		// free(save);
	}
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
	free_lst_exec(cmd);
	free_lst(data);
}
