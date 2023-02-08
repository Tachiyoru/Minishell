/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:24:33 by sleon             #+#    #+#             */
/*   Updated: 2023/02/08 18:49:06 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		msg("run as ./minishell with no argument.");
		return (EXIT_FAILURE);
	}
	else
		ft_begin();
}
