/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:41:10 by sleon             #+#    #+#             */
/*   Updated: 2023/02/11 13:36:04 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <signal.h>
# include <wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

extern int					g_error;

typedef struct s_pipex		t_pipex;
typedef enum e_fd			t_fd;
typedef struct s_val		t_val;
typedef struct s_env		t_env;

// enum e_fd{
// 	DEFAULT = -1,
// 	IN,
// 	OUT,
// 	MAX_FD,
// 	HEREDOC,
// };

struct s_env{
	char	*key;
	char	*val;
	t_env	*next;
};

struct s_val{
	char	*val;
	int		token;
	t_val	*next;
};

struct s_pipex
{
	pid_t	pid;
	int		fd[2];
	t_val	*cmd;
	t_val	*redir;
	t_pipex	*next;
};

void	printlist(t_val *data);

/////\ PARSING \//////
// --parsing_recursive utils--
int		word_end(char *line, int start);
int		word_start(char *line);
// --parsing_recursive--
int		ft_begin2(char **envp);

// --parsing--
void	parsing(t_val *data, char *str);
int		ft_begin(char **envp);
void	set_val(char *str, t_val **data, int i, int size);

/////\ FREE-PARSING \//////

/////\ BUILTINS \//////
/////\ UTILS \//////
int		ft_strchr(const char *str, int c);
int		ft_ccmp(char a, char b);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(char *a, char *b, size_t l);
int		ft_strlen2( char *str);
void	msg(char *str);

#endif
