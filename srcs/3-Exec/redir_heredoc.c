/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:06:28 by sleon             #+#    #+#             */
/*   Updated: 2023/03/11 15:02:35 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_heredoc(int type)
{
	int		ret;

	if (type)
	{
		ret = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ret < 0)
			ret = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		ret = open("/tmp/.heredoc", O_RDONLY | O_CREAT, 0644);
		if (ret < 0)
			ret = open(".heredoc", O_RDONLY | O_CREAT, 0644);
	}
	return (ret);
}

int	check_quote_limitor(t_val *red)
{
	while (red)
	{
		if (red->token == LIMITOR)
		{
			if (is_error_qm(red->val))
				return (-1);
			if (red->val[0] == '\'' || red->val[0] == '"')
				return (0);
		}
		red = red->next;
	}
	return (1);
}

void	rem_quotes(t_val *redir)
{
	int		len;
	char	*dest;

	dest = NULL;
	len = ft_strlen(redir->next->val);
	if ((redir->next->val[0] == '"' && redir->next->val[len - 1] == '"')
		|| (redir->next->val[0] == '\'' && redir->next->val[len - 1] == '\''))
		dest = ft_substr(redir->next->val, 1, len - 2);
	else if (redir->next->val[0] == '\'' || redir->next->val[0] == '"')
		dest = ft_substr(redir->next->val, 1, len);
	if (redir->next->val && dest)
		free(redir->next->val);
	if (dest)
		redir->next->val = dest;
}

int	expand_heredoc(t_val *redir)
{
	int		fd;
	char	*line;

	fd = make_heredoc(1);
	if (fd < 0)
		return (msg("error"), fd);
	rem_quotes(redir);
	while (1)
	{
		line = readline(">>");
		if (!line)
			break ;
		if (!ft_strcmp(line, redir->next->val))
			break ;
		if (ft_strchr(line, '$'))
			line = expand_heredoc_var(line);
		if (line)
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
	}
	return (fd);
}

int	simple_heredoc(t_val *redir)
{
	int		fd;
	char	*line;

	fd = make_heredoc(1);
	if (fd < 0)
		return (msg("error"), fd);
	rem_quotes(redir);
	while (1)
	{
		line = readline(">>");
		if (!line)
			break ;
		if (!ft_strcmp(line, redir->next->val))
			break ;
		if (line)
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
	}
	return (fd);
}
