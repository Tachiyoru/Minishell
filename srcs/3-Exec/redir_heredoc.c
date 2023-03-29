/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:06:28 by sleon             #+#    #+#             */
/*   Updated: 2023/03/29 10:06:24 by ajeanne          ###   ########.fr       */
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

	line = NULL;
	fd = make_heredoc(1);
	if (fd < 0)
		return (msg("error"), fd);
	if (quote_treatment_h(redir))
		return (fd);
	while (1)
	{
		line = readline(">>");
		if (!line)
			break ;
		if (!ft_strcmp(line, redir->next->val))
			break ;
		if (ft_strchr(line, '$'))
			if (find_env(line))
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

	line = NULL;
	fd = make_heredoc(1);
	if (fd < 0)
		return (msg("error"), fd);
	if (quote_treatment_h(redir))
		return (fd);
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
