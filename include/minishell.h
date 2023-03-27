/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:41:10 by sleon             #+#    #+#             */
/*   Updated: 2023/03/27 17:46:01 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <signal.h>
# include <sys/wait.h>
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

////SIGNAL/////
void	init_signal1(void);
void	init_signal2(void);
void	signal_heredoc(int sig);

/////\ ENV \//////
void	del_env(void);

t_env	**handle_env(char **env);
t_env	**get_env(void);
void	del_from_env(char *delete);
void	add_to_env(char *add);
void	store_env(char **env);
t_env	*init_env2(char *env, t_env *env_s);
t_env	*ft_last_env(t_env **data);
t_env	*init_env(char **env);
char	*find_env(char *find);

void	print_list2(t_env *data);
void	print_list(t_val *data);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
void	set_shlvl(void);

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
void	wait_child_exec(t_pipex *start);

int		set_redir_in(t_pipex *cmd);
int		set_redir_out(t_pipex *cmd);
int		set_redir_append(t_pipex *cmd);
int		set_redir_heredoc(t_pipex *cmd);

int		check_quote_limitor(t_val *red);
int		expand_heredoc(t_val *redir);
int		simple_heredoc(t_val *redir);
int		make_heredoc(int type);

void	error_cmd(char *cmd);
char	*open_cmd(char *val);
char	*fillpath(t_pipex *exec, char **env);
int		is_builtin2(char *cmd, t_pipex *exec, int res);
int		is_builtin(char *cmd, t_pipex *exec);

char	*is_exec(char *cmd);
char	*ft_strdup_env(t_env *env);
int		lst_size(t_env *env);
char	**make_env_tab(void);
char	**make_cmd_tab(t_val *cmd);
char	*pathfinder(char *val, char **env);

void	check_fd(t_pipex *exec);
int		setup_redir(t_pipex *cmd);
void	setup_pipe(t_pipex *cmd);

char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split2(char	*str, char set);

/////\ BUILTINS \//////

int		b_in_cd(t_val *option, int infile, int outfile);
int		b_in_echo(t_val *options, int fd);
int		b_in_exit(t_val *option, t_pipex *exec);
int		b_in_pwd(int fd_out);
int		unset_cmd(char *key_d);

/////\ UTILS \//////
//free
void	free_lst(t_val	*data);
void	free_tab(char **tab);
void	free_lst_exec(t_pipex *exec);
void	free_wr(char *content, char *nw);
void	free_vr(char *name);

//utils3
char	*ft_substr(char *s, unsigned int start, size_t len);
int		lst_size_val(t_val *env);
int		lst_size(t_env *env);
void	ft_putstr_fd(int fd, char *s);
t_env	*lst_env_new(char *key, char *val);

//utils2
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
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
int		contain_equals(char *key_val);
int		is_error_qm(char *content, t_val *tmp, t_val *tmp_prev);
int		is_error_qm_h(t_val *data);
int		simple_increment(char *content, int *i);

// expand
int		quote_treatment(t_val *data);
t_val	*ft_lstnew_token(void *content, t_val *next);
int		quote_parsing(char *content, t_val *data);
int		is_var(char *content, int i, t_val *data, int *iadd);
int		expand_space(char *content, t_val *data);
int		ambigous_redirect_checker(t_val *data);
char	*expand_heredoc_var(char *line);

// buildin
int		env_cmd(int fd);
int		unset_cmd(char *key_d);
int		export_cmd(char *key_val, int fd);
int		existing_key_replace_val(char *key, char *val);
int		existing_key(char *key);
int		key_checker(char *key);
int		env_add_back(char *key, char *val);
int		contain_equals(char *key_val);
void	end_of_replacing(char **dest, char *content, int i, int end);
char	*rem_whitespace_export(char *value);
void	back_to_positive(t_val *data);
int		quote_treatment_h(t_val *data);

#endif
