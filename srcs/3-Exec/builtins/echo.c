/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:29 by sleon             #+#    #+#             */
/*   Updated: 2023/02/25 13:55:02 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief behave like the echo functiun
 *
 * @param options if option 1 is -n then no \n at the end
 * @param fd where to write the output
 * @return int
 */
int	b_in_echo(t_val *options, int fd)
{
	int	n;

	n = 0;
	g_error = 0;
	if (!options)
		return (write(fd, "\n", 1), 1);
	while (options->val[0] == '-' && options->val[1] == 'n')
	{
		options = options->next;
		n = 1;
	}
	while (options)
	{
		if (options->val)
			ft_putstr_fd(fd, options->val);
		options = options->next;
		if (options)
			write(fd, " ", 1);
	}
	if (!n)
		write(fd, "\n", 1);
	return (1);
}
