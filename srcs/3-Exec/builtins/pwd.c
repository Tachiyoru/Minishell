/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:22:27 by sleon             #+#    #+#             */
/*   Updated: 2023/03/21 16:52:08 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (g_error = 127, msg("getcwd fail\n"), 1);
	ft_putstr_fd(fd_out, result);
	write(fd_out, "\n", 1);
	free(result);
	return (g_error = 0, 1);
}
