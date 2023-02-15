/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:37:20 by ajeanne           #+#    #+#             */
/*   Updated: 2023/02/15 18:45:45 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_val	*ft_lstnew_token(void *content, t_val *next)
{
	t_val	*new_element;

	new_element = malloc(sizeof(t_val));
	if (!new_element)
		return (NULL);
	new_element->val = content;
	new_element->token = WORD;
	new_element->next = next;
	return (new_element);
}
