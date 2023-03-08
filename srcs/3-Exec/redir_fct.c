/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:42:31 by sleon             #+#    #+#             */
/*   Updated: 2023/03/08 16:23:52 by sleon            ###   ########.fr       */
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
	int	stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	fd = check_quote_limitor(cmd->redir);
	signal(SIGINT, &signal_heredoc);
	if (!fd)
		fd = expand_heredoc(cmd->redir);
	else
		fd = simple_heredoc(cmd->redir);
	if (fd < 0)
		return (0);
	close(fd);
	if (g_error == 128)
		return (dup2(stdin_copy, 0), init_signal1(), close(stdin_copy),
			write(STDOUT_FILENO, "\n", 1), g_error = 130, -1);
	close(stdin_copy);
	init_signal1();
	fd = make_heredoc(0);
	if (cmd->fd[0] != STDIN_FILENO)
	{
		dup2(fd, cmd->fd[0]);
		close(cmd->fd[0]);
	}
	return (cmd->fd[0] = fd, 1);
}
