/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:32 by sleon             #+#    #+#             */
/*   Updated: 2023/02/22 19:30:37 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_in_cd(t_val *option, int in, int out)
{
	g_error = 0;
	if (in != STDIN_FILENO || out != STDOUT_FILENO)
		return (1);
	if (!option || lst_size_val(option) > 1 || option->val[0] == '-')
		return (g_error = 1, msg("error in cd arg"), 1);
	if (chdir(option->val) == -1)
	{
		perror(NULL);
		g_error = 1;
	}
	return (1);
}
