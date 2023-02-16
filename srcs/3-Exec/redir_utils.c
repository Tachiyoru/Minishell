/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:37 by sleon             #+#    #+#             */
/*   Updated: 2023/02/16 18:28:37 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_redir(t_pipex *cmd)
{
	while (cmd->redir)
	{
		if (cmd->redir->token == R_IN)
			set_redir_in(cmd);
		else if (cmd->redir->token == R_OUT)
			set_redir_out(cmd);
		else if (cmd->redir->token == APPEND)
			set_redir_appen(cmd);
		cmd->redir = cmd->redir->next;
	}
}
		// if (cmd->redir->token == HEREDOC)
		// 	set_redir_heredoc(cmd);
//	MEMO a faire apres que l'expand soit termine !!!

void	setup_pipe(t_pipex *cmd)
{
	int	tmp_pipe[2];

	pipe(tmp_pipe);
	cmd->fd[1] = tmp_pipe[1];
	cmd->next->fd[0] = tmp_pipe[0];
}
