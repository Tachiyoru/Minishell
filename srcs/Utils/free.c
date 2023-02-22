/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:13:30 by sleon             #+#    #+#             */
/*   Updated: 2023/02/21 18:08:44 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_lst(t_val	*data)
{
	t_val	*save;

	while (data)
	{
		save = data;
		data = data->next;
		free(save->val);
		free(save);
	}
	data = NULL;
}

void	free_lst_env(t_env	*data)
{
	t_env	*save;

	while (data)
	{
		save = data;
		data = data->next;
		free(save->key);
		free(save->val);
		free(save);
	}
	data = NULL;
}

// void	free_char(char **cmd, char **env, char *path);

// void	free_struct(t_pipex *start)
// {
// }
