/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:37 by sleon             #+#    #+#             */
/*   Updated: 2023/02/16 15:16:56 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief will go to the last node of cmd part and add the t_val node
 *
 * @param exec 
 * @param data the cmd to add
 */
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

/**
 * @brief will go to the last node of redir part and add the t_val node
 *
 * @param exec
 * @param data the redir add
 */
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

/**
 * @brief return the last node of t_pipex
 *
 * @param data
 * @return t_pipex*
 */
t_pipex	*ft_last_cmd(t_pipex **data)
{
	t_pipex	*tmp;

	tmp = *data;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/**
 * @brief init a node to receive all info for inside one pipe
 *
 * @param cmd
 * @return int
 */
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
