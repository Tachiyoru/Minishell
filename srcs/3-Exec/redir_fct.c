/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:42:31 by sleon             #+#    #+#             */
/*   Updated: 2023/02/28 19:29:52 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief setup the redir in if the file exist else return 0
 *
 * @param cmd
 */
int	set_redir_in(t_pipex *cmd)
{
	int	fd;

	if (!cmd->redir->next)
		return (0);
	fd = open(cmd->redir->next->val, O_RDONLY);
	if (fd < 0)
		return (0);
	if (cmd->fd[0] != 0)
	{
		dup2(fd, cmd->fd[0]);
		close(cmd->fd[0]);
	}
	cmd->fd[0] = fd;
	return (1);
}

/**
 * @brief Setup the redir out if it can else return 0
 *
 * @param cmd
 * @return 1 good 0 not good
 */
int	set_redir_out(t_pipex *cmd)
{
	int	fd;

	if (!cmd->redir->next)
		return (0);
	fd = open(cmd->redir->next->val, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (0);
	if (cmd->fd[1] != 1)
	{
		dup2(fd, cmd->fd[1]);
		close(cmd->fd[1]);
	}
	cmd->fd[1] = fd;
	return (1);
}

/**
 * @brief Set the redir append if it can else return 0
 *
 * @param cmd
 * @return 1 good 0 not good
 */
int	set_redir_append(t_pipex *cmd)
{
	int	fd;

	if (!cmd->redir->next)
		return (0);
	fd = open(cmd->redir->next->val, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (0);
	if (cmd->fd[1] != 1)
	{
		dup2(fd, cmd->fd[1]);
		close(cmd->fd[1]);
	}
	cmd->fd[1] = fd;
	return (1);
}

int	set_redir_heredoc(t_pipex *cmd)
{
	int	fd;

	fd = check_quote_limitor(cmd->redir);
	if (fd == 1)
		fd = expand_heredoc(cmd->redir);
	else if (!fd)
		fd = simple_heredoc(cmd->redir);
	if (fd < 0)
		return (0);
	close(fd);
	fd = make_heredoc(0);
	if (cmd->fd[0] != STDIN_FILENO)
	{
		dup2(fd, cmd->fd[0]);
		close(cmd->fd[0]);
	}
	cmd->fd[0] = fd;
	return (1);
}
