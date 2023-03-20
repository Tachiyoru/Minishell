/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:21:20 by sleon             #+#    #+#             */
/*   Updated: 2023/03/20 12:24:56 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief turn the option in char to be written
 *
 * @param str
 * @return int
 */
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result *= sign);
}

/**
 * @brief check if there is only digit in the option
 *
 * @param str
 * @return int
 */
int	option_is_digit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

/**
 * @brief behave like the exit functiun
 *
 * @param option only one and only digit
 * @param exec the struc to free
 * @return int
 */
int	b_in_exit(t_val *option, t_pipex *exec)
{
	g_error = 0;
	if (exec->fd[0] != STDIN_FILENO || exec->fd[1] != STDOUT_FILENO)
		return (1);
	write(exec->fd[1], "exit\n", 5);
	if (option)
	{
		if (!option_is_digit(option->val))
		{
			msg("Minishell ~ exit: ");
			msg(option->val);
			msg(": numeric argument required\n");
			g_error = 2;
		}
		else if (lst_size_val(option) > 1)
			return (g_error = 1,
				msg("Minishell ~ exit: too many arguments\n"), 1);
		if (option_is_digit(option->val))
			g_error = ft_atoi(option->val);
	}
	del_env();
	free_lst_exec(exec);
	rl_clear_history();
	exit(g_error);
	return (1);
}
