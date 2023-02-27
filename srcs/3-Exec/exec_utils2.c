/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:17:47 by sleon             #+#    #+#             */
/*   Updated: 2023/02/27 20:25:21 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		res = env_cmd();
	else if (!ft_strcmp(cmd, "export") && exec->cmd->next)
	{
		while (exec->cmd->next)
		{
			res = export_cmd(exec->cmd->next->val);
			exec->cmd->next = exec->cmd->next->next;
		}
	}
	else if (!ft_strcmp(cmd, "export") && !exec->cmd->next)
		res = export_cmd(NULL);
	return (res);
}
