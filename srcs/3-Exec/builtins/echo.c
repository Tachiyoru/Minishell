/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:29 by sleon             #+#    #+#             */
/*   Updated: 2023/03/22 15:48:08 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *val)
{
	if (*val == '-')
		val++;
	else
		return (0);
	if (!*val)
		return (0);
	while (*val)
	{
		if (*val != 'n')
			return (0);
		val++;
	}
	return (1);
}

/**
 * @brief behave like the echo functiun
 *
 * @param options if option 1 is -n then no \n at the end
 * @param fd where to write the output
 * @return int
 */
int	b_in_echo(t_val *options, int fd)
{
	int		n;
	char	*a;

	n = 0;
	g_error = 0;
	if (!options)
		return (write(fd, "\n", 1), 1);
	while (options && options->val && check_n(options->val))
	{
		options = options->next;
		n = 1;
	}
	while (options)
	{
		if (options->val)
			ft_putstr_fd(fd, options->val);
		a = options->val;
		options = options->next;
		if (options && ft_strcmp(" ", a))
			write(fd, " ", 1);
	}
	if (!n)
		write(fd, "\n", 1);
	return (1);
}
