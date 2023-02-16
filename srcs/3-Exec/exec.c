/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:37 by sleon             #+#    #+#             */
/*   Updated: 2023/02/16 13:12:03 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_word(t_pipex **exec, t_val **data)
{
	t_val	*list;
	t_val	*next;

	list = *data;
	if (!(*exec)->cmd)
		(*exec)->cmd = list;
	else
		ft_last(&(*exec)->cmd)->next = list;
	next = list->next;
	*data = next;
	list->next = NULL;
}

void	add_redir(t_pipex **exec, t_val **data)
{
	t_val	*list;
	t_val	*next;

	list = *data;
	if (!(*exec)->redir)
		(*exec)->redir = list;
	else
		ft_last(&(*exec)->redir)->next = list;
	next = list->next;
	*data = next;
	list->next = NULL;
}

t_pipex	*ft_last_cmd(t_pipex **data)
{
	t_pipex	*tmp;

	tmp = *data;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	init_cmd(t_pipex **cmd)
{
	t_pipex	*tmp;

	tmp = ft_calloc(sizeof(t_pipex), 1);
	if (!tmp)
		return (0);
	tmp->fd[0] = STDIN_FILENO;
	tmp->fd[1] = STDOUT_FILENO;
	tmp->pid = 0;
	tmp->cmd = NULL;
	tmp->redir = NULL;
	if (!(*cmd))
		(*cmd) = tmp;
	else
		ft_last_cmd(cmd)->next = tmp;
	return (1);
}
// MEMO pas sur d'avoir besoin de tmp.redir si il est compris dans cmd en soit.

int	make_struct_exec(t_val *data, t_pipex **exec)
{
	t_pipex	*head;
	t_val	*save;

	save = data;
	if (!init_cmd(exec))
		return (0);
	head = *exec;
	while (data)
	{
		if (data->token == WORD)
			add_word(exec, &data);
		else if (data->token == PIPE)
		{
			if (!init_cmd(exec))
				return (0);
			save = data->next;
			free(data->val);
			free(data);
			data = save;
			(*exec) = (*exec)->next;
		}
		else
			add_redir(exec, &data);
	}
	return (1);
}

void	exec(t_val	*data)
{
	t_pipex	*cmd;

	cmd = NULL;
	if (! make_struct_exec(data, &cmd))
		return ;
}
