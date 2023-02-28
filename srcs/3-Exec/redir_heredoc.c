/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:06:28 by sleon             #+#    #+#             */
/*   Updated: 2023/02/28 18:56:57 by sleon            ###   ########.fr       */
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
			printf("%s \n", red->val);
			if (red->val[0] == '\'' || red->val[0] == '"')
				return (0);
		}
		red = red->next;
	}
	return (1);
}

int	expand_heredoc(t_val *redir)
{
	int		fd;
	char	*line;

	fd = make_heredoc(1);
	if (fd < 0)
		return (msg("error"), fd);
	while (1)
	{
		line = readline(">>");
		if (!line)
			break ;
		if (!ft_strcmp(line, redir->next->val))
			break ;
		if (ft_strchr(line, '$'))
			write(fd, "ca doit expand la", 17);
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
