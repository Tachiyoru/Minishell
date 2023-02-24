/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:32 by sleon             #+#    #+#             */
/*   Updated: 2023/02/24 12:55:56 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief behave like the cmd cd, changing the directory from wich we operate
 *
 * @param option possible option is a path to a directory
 * @return int
 */
int	b_in_cd(t_val *option)
{
	g_error = 0;
	if (!option || lst_size_val(option) > 1 || option->val[0] == '-')
		return (g_error = 1, msg("error in cd arg"), 1);
	if (chdir(option->val) == -1)
	{
		perror(NULL);
		g_error = 1;
	}
	return (1);
}
