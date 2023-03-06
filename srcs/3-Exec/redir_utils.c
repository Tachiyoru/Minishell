/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:37 by sleon             #+#    #+#             */
/*   Updated: 2023/03/06 16:18:48 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check if the fd is not the same a standart
 *
 * @param exec
 */
void	check_fd(t_pipex *exec)
{
	if (exec->fd[0] != STDIN_FILENO)
	{
		dup2(exec->fd[0], STDIN_FILENO);
		close(exec->fd[0]);
	}
	if (exec->fd[1] != STDOUT_FILENO)
	{
		dup2(exec->fd[1], STDOUT_FILENO);
		close(exec->fd[1]);
	}
}

/**
 * @brief detup the redirection depending on the token
 *
 * @param cmd
 */
int	setup_redir(t_pipex *cmd)
{
	int	res;

	while (cmd->redir)
	{
		if (cmd->redir->token == R_IN)
			res = set_redir_in(cmd);
		else if (cmd->redir->token == R_OUT)
			res = set_redir_out(cmd);
		else if (cmd->redir->token == APPEND)
			res = set_redir_append(cmd);
		else if (cmd->redir->token == HEREDOC)
			res = set_redir_heredoc(cmd);
		if (res != 1)
			break ;
		cmd->redir = cmd->redir->next;
	}
	if (cmd->redir)
		return (res);
	return (1);
}
//	MEMO a faire apres que l'expand soit termine !!!

/**
 * @brief Set the up pipe between the two command
 *
 * @param cmd
 */
void	setup_pipe(t_pipex *cmd)
{
	int	tmp_pipe[2];

	pipe(tmp_pipe);
	cmd->fd[1] = tmp_pipe[1];
	cmd->next->fd[0] = tmp_pipe[0];
}
