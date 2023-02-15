/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:37 by sleon             #+#    #+#             */
/*   Updated: 2023/02/15 16:48:04 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_val	*add_word(t_val *data)
{
	return (data.)
}

t_pipex	*ft_last_cmd(t_pipex **data)
{
	t_pipex	*tmp;

	tmp = *data;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	init_cmd(t_pipex **cmd, t_pipex *tmp)
{
	tmp = ft_calloc(sizeof(t_pipex), 1);
	if (!tmp)
		return (0);
	tmp->fd[0] = STDIN_FILENO;
	tmp->fd[1] = STDOUT_FILENO;
	tmp->pid = 0;
	tmp->cmd = NULL;
	tmp->redir = NULL;
	if (!(*cmd))
		(*cmd) = tmp;
	else
		ft_last_cmd(cmd)->next = tmp;
	return (1);
}
// MEMO pas sur d'avoir besoin de tmp.redir si il est compris dans cmd en soit.

int	make_struct_exec(t_val *data, t_pipex **cmd)
{
	t_pipex	*tmp;
	t_val	*save;

	tmp = *cmd;
	save = data;
	if (!init_cmd(cmd, tmp))
		return (0);
	while (data)
	{
		if (data->token == WORD)
			ft_last(tmp->cmd) = add_word(data);
	}
	return (1);
}

void	exec(t_val	*data)
{
	t_pipex	*cmd;

	cmd = NULL;
	if (!make_struct_exec(data, &cmd))
		return ;
}
