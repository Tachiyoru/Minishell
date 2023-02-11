/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:05:48 by sleon             #+#    #+#             */
/*   Updated: 2023/02/11 20:42:24 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// WORD = Si c'est pas autre choses c'est un mot
// FD = always after < > << >>
// LIMITOR = Cat du HDOC le mot apres et le limiteur || voir si autre cas
// R_IN = Redirection in donc <
// HDOC (HEREDOC)= Redirection << [LIMITEUR]
// R_OUT = redirection out donc >
// APPEND = >>
// PIPE = |

/**
 * @brief check if the parsing is correct and possible
 *
 * @param data linkchain
 * @return 0 if problem else 1
 */
int	good_parsing(t_val *data)
{
	int	prev;

	prev = -1;
	while (data)
	{
		if (prev == HEREDOC && data->token != LIMITOR)
			return (msg("error token to be define"), 0);
		if ((prev == R_OUT || prev == APPEND) && data->token != FD)
			return (msg("error token to be define"), 0);
		if (data->token == PIPE && (prev == PIPE || prev == R_IN
				|| prev == APPEND || prev == HEREDOC))
			return (msg("error token to be define"), 0);
		if (data->token == PIPE && prev == -1)
			return (msg("error token to be define"), 0);
		prev = data->token;
		data = data->next;
	}
	if (prev == PIPE || prev == R_IN || prev == R_OUT || prev == APPEND
		|| prev == HEREDOC)
		return (msg("error token to be define"), 0);
	return (1);
}

/**
 * @brief determinate what the kind of token
 *
 * @param str the token
 * @param prev used for special case like limitor and fd
 * @return the matching one
 */
int	what_token(char *str, int prev)
{
	size_t	size;

	size = ft_strlen(str);
	if (size == 1)
	{
		if (*str == '>')
			return (R_IN);
		else if (*str == '<')
			return (R_OUT);
		else if (*str == '|')
			return (PIPE);
	}
	else
	{
		if (str[0] == '>' && str[1] == '>')
			return (APPEND);
		else if (str[0] == '<' && str[1] == '<')
			return (HEREDOC);
		else if (prev == HEREDOC)
			return (LIMITOR);
		else if (prev == APPEND || prev == R_OUT || prev == R_IN)
			return (FD);
	}
	return (WORD);
}

/**
 * @brief go trhough the linkchain et set what kind of token it is
 *
 * @param data the linkchain
 */
void	check_token(t_val *data)
{
	t_val	*head;
	int		prev;

	prev = 0;
	head = data;
	while (head)
	{
		head->token = what_token(head->val, prev);
		prev = head->token;
		head = head->next;
	}
	if (!good_parsing(data))
		return ;
		// free_lst(data);
}
