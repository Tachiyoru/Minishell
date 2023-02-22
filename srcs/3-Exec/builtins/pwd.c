/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:27 by sleon             #+#    #+#             */
/*   Updated: 2023/02/22 17:03:58 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(int fd, char *s)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

/**
 * @brief find the pwd thanks to getpwd
 *
 * @param fd_out the fd to write in
 * @return setup the glob_err and return one so the original cmd doesn't execute
 */
int	b_in_pwd(int fd_out)
{
	char	*result;

	result = getcwd(NULL, 0);
	if (!result)
		return (g_error = 127, msg("getcwd fail"), 1);
	ft_putstr_fd(fd_out, result);
	write(fd_out, "\n", 1);
	free(result);
	return (g_error = 0, 1);
}
