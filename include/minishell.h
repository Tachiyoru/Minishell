/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:41:10 by sleon             #+#    #+#             */
/*   Updated: 2023/02/24 22:22:30 by ajeanne          ###   ########.fr       */
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

enum e_token
{
	WORD,
	R_IN,
	FD,
	R_OUT,
	LIMITOR,
	HEREDOC = 6,
	APPEND = 8,
	PIPE = 10,
};

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

/////\ ENV \//////
t_env	**handle_env(char **env);
t_env	**get_env(void);
void	del_from_env(char *delete);
void	add_to_env(char *add);
void	store_env(char **env);
t_env	*init_env2(char *env, t_env *env_s);
t_env	*ft_last_env(t_env **data);
t_env	*init_env(char **env);
char	*find_env(char *find);

void	print_list(t_val *data);

int		main(int ac, char **av, char **envp);

/////\ PARSING \//////
// --parsing_recursive utils--
void	check_token(t_val *data);

// --parsing_recursive utils--
t_val	*ft_last(t_val **data);
int		set_val_tab(char *str, t_val **data);
int		word_end(char *line, int start);
int		word_start(char *line);
// --parsing_recursive--
void	split_pars(char *buf);

/////\ EXEC \//////
void	add_word(t_pipex **exec, t_val **data);
void	add_redir(t_pipex **exec, t_val **data);
t_pipex	*ft_last_cmd(t_pipex **data);
int		init_cmd(t_pipex **cmd);
void	exec(t_val	*data);

void	set_redir_in(t_pipex *cmd);
void	set_redir_out(t_pipex *cmd);
void	set_redir_append(t_pipex *cmd);

char	*ft_strdup_env(t_env *env);
int		lst_size(t_env *env);
char	**make_env_tab(void);
char	**make_cmd_tab(t_val *cmd);
char	*pathfinder(char *val, char **env);

void	check_fd(t_pipex *exec);
void	setup_redir(t_pipex *cmd);
void	setup_pipe(t_pipex *cmd);

char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split2(char	*str, char set);

/////\ BUILTINS \//////

int		b_in_cd(t_val *option, int in, int out);
int		b_in_echo(t_val *options, int fd);
int		b_in_pwd(int fd_out);

/////\ UTILS \//////
//free
void	free_lst(t_val	*data);
void	free_lst_env(t_env	*data);
void	free_tab(char **tab);

//utils3
char	*ft_substr(char *s, unsigned int start, size_t len);
int		lst_size_val(t_val *env);
int		lst_size(t_env *env);
void	ft_putstr_fd(int fd, char *s);
t_env	*lst_env_new(char *key, char *val);

//utils2
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
char	*word_replacing(int start, int end, char *content, char *new_word);
char	*var_replacing(int start, int end, char *content, int *i);
char	*ft_strndup(const char *s, int size);
int		ft_strcmp(const char *s1, const char *s2);

//utils
int		ft_strchr(const char *str, int c);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen( char *str);
void	msg(char *str);
char	*ft_itoa(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putchar_err(char c);

// expand
int		quote_treatment(t_val *data);
t_val	*ft_lstnew_token(void *content, t_val *next);
int		quote_parsing(char *content, t_val *data);
int		is_var(char *content, int i, t_val *data, int *iadd);
int		expand_space(char *content, t_val *data);
int		ambigous_redirect_checker(t_val *data);

// buildin
int		env_cmd();
int		unset_cmd(char *key_d);
int		export_cmd(char *key_val);

#endif
