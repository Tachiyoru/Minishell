/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:17:47 by sleon             #+#    #+#             */
/*   Updated: 2023/03/13 18:24:55 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cmd(char *cmd)
{
	g_error = 127;
	msg(cmd);
	msg(": command not found\n");
}

char	*fillpath(t_pipex *exec, char **env)
{
	if (exec->cmd->val[0] == '.' || exec->cmd->val[0] == '/')
		return (is_exec(exec->cmd->val));
	else
		return (pathfinder(exec->cmd->val, env));
}

int	is_builtin2(char *cmd, t_pipex *exec, int res)
{
	if (!ft_strcmp(cmd, "env"))
		res = env_cmd(exec->fd[1]);
	else if (!ft_strcmp(cmd, "export") && exec->cmd->next)
	{
		while (exec->cmd->next)
		{
			res = export_cmd(exec->cmd->next->val, exec->fd[1]);
			exec->cmd->next = exec->cmd->next->next;
		}
	}
	else if (!ft_strcmp(cmd, "export") && !exec->cmd->next)
		res = export_cmd(NULL, exec->fd[1]);
	return (res);
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
