/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:42:31 by sleon             #+#    #+#             */
/*   Updated: 2023/02/20 13:23:55 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redir_in(t_pipex *cmd)
{
	int	fd;

	if (!cmd->redir->next)
		return ;
	fd = open(cmd->redir->next->val, O_RDONLY);
	if (fd < 0)
		return ;
	if (cmd->fd[0] != 0)
	{
		dup2(fd, cmd->fd[0]);
		close(cmd->fd[0]);
	}
	cmd->fd[0] = fd;
}

void	set_redir_out(t_pipex *cmd)
{
	int	fd;

	if (!cmd->redir->next)
		return ;
	fd = open(cmd->redir->next->val, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return ;
	if (cmd->fd[1] != 1)
	{
		dup2(fd, cmd->fd[1]);
		close(cmd->fd[1]);
	}
	cmd->fd[1] = fd;
}

void	set_redir_append(t_pipex *cmd)
{
	int	fd;

	if (!cmd->redir->next)
		return ;
	fd = open(cmd->redir->next->val, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return ;
	if (cmd->fd[1] != 1)
	{
		dup2(fd, cmd->fd[1]);
		close(cmd->fd[1]);
	}
	cmd->fd[1] = fd;
}

// void	set_redir_heredoc(t_pipex *cmd)
// {}
