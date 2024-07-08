/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyaid <cyaid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:55:39 by abdmessa          #+#    #+#             */
/*   Updated: 2024/06/29 04:54:56 by cyaid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define FAILURE 1
# define BROKEN_PIPE 13
# define CAPACITY 20
# define DEFAULT_COMMAND_CAPACITY 4
# define MISSING_QUOTES "minishell: unexpected error when parsing quotes\n"
# define SYNTAX_ERROR "minishell: unexpected error when parsing `|<>`\n"
# define EXIT_ERR_NUM_ARG "minishell: exit: numeric argument required\n"
# define EXIT_TOO_MANY_ARGS "minishell: exit: too many arguments\n"
# define STOP_TOKEN_WORD "$'\" \t\n\v\f\r|<>"
# define STOP_TOKEN_REDIR "'\" \t\n\v\f\r|<>"
# define PIPE_INF_OUT "|<>"
# define PATH_MAX 4096
# define PIPE_INF_OUT_SPACE "|>< \t\v\r\n\f"
# ifndef READLINE_PROMPT
#  define READLINE_PROMPT "\e[38;5;415m1.42$ \033[0m"
# endif

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int					g_signum;

// struct pour lenv
typedef struct s_dynamic_arr
{
	size_t					capacity;
	size_t					len;
	char					**tab;
}							t_dynamic_arr;

typedef struct s_redir
{
	char					*redirection_name;
	int						fd[2];
}							t_redir;

// enum pour les tokens
enum						e_token
{
	TOKEN_DSUP,
	TOKEN_DINF,
	TOKEN_INF = '<',
	TOKEN_SUP = '>',
	TOKEN_PIPE = '|'
};

enum						e_builtin_id
{
	ENV,
	CD,
	ECHO,
	EXIT,
	UNSET,
	PWD,
	EXPORT,
	NONE
};

typedef struct s_command
{
	struct s_token			*infile;
	struct s_token			*outfile;
	struct s_token			*redirections;
	struct s_token			*last_redirection;
	t_dynamic_arr			*commands;
	struct s_command		*next;
	char					*delimiter;
	int						fd[2];
	int						pid;
	int						infile_fd;
	int						outfile_fd;
	enum e_builtin_id		builtin_id;
}							t_command;

// struct pour la tokenisation
typedef struct s_token
{
	char					*str;
	enum e_token			type;
	struct s_token			*next;
}							t_token;

typedef struct s_list
{
	int						content;
	int						pos;
	struct s_list			*next;
}							t_list;

// struct pour l expand
typedef struct s_var_expand
{
	char					*start;
	char					*var_value;
	char					*var_end;
	char					*new_str;
	int						ret_value;
}							t_var_expand;

enum						e_err
{
	OK,
	KO,
};

typedef struct s_minishell	t_minishell;
// array de built_in fonction
typedef int					(*t_Builtin)(t_minishell *, t_command *, bool);
// struct principal (pas tres propre mais a ranger avant de push)
typedef struct s_minishell
{
	t_Builtin				builtins[7];
	t_command				*command;
	t_command				*last_command;
	t_dynamic_arr			env;
	size_t					nb_commands;
	int						fd[2];
	int						prev_pipes;
	int						ret_value;
	char					*user_input;
	char					**path;
}							t_minishell;

//	init
int							init_sh(t_minishell *sh, char **envp, int argc,
								char **argv);

// 	fonction > heredoc
int							write_into_pipe(int fd, char *delim);
int							parent_process(t_minishell *sh, int children_pid);
void						child_proccess(t_minishell *sh, t_command *command);
void						close_doc(t_command *command, bool close_read,
								bool close_write);

// 	fonction > env
int							check_env_key(char *env_var, char *to_check);
int							init_env(t_minishell *sh, t_dynamic_arr *env,
								char **envp);
int							get_env_var_index(char **tab, char *to_find);
char						*get_env_var_value(char **tab, char *to_find);

//	fonction > dup
int							dup_wrapper(int *fd, int old_fd);
int							dup_and_save(int *fd, int old_fd);

// 	fonction > exec
void						close_fd(int *fd);
void						close_infile_outfile(t_command *command);
void						exec_command(t_minishell *sh,
								t_command *command_info);
int							handle_heredoc(t_minishell *sh);
int							try_open_close_redirection(t_token *tok);
int							try_open_close_redirection_builtin(t_minishell *sh,
								t_command *command, t_token *redirection,
								int *save_stdout);
int							redirect_stdout_stdin(t_minishell *sh,
								t_command *command);
bool						check_if_command_must_be_forked(t_minishell *sh,
								t_command *command, bool in_fork);

//	fonctions > print
void						print_msg(const char *msg, int fd);
void						print_msg_stderr(const char *msg);
void						print_msg_stdout(const char *msg);
int							print_error_and_set_exit_status(const char *msg,
								int err_code);
int							print_perror_and_set_exit_status(const char *msg,
								int err_code);
void						write_nl(bool *nl);

//	fonctions > signal
void						handle_signals(void);
void						sigint_handler(int signum);
void						set_heredoc_signal(void);
void						handle_signals_in_fork(void);

//	fonctions > readline esthetique
void						ft_affpwd(void);
//	fonctions > builtins
void						get_builtin_id(t_command *command);
int							call_builtin(t_minishell *sh, t_command *command,
								bool in_fork);
int							builtin_ft_pwd(t_minishell *sh, t_command *command,
								bool in_fork);
int							builtin_ft_echo(t_minishell *sh, t_command *command,
								bool in_fork);
int							builtin_ft_cd(t_minishell *sh, t_command *command,
								bool in_fork);
int							builtin_ft_exit(t_minishell *sh, t_command *command,
								bool in_fork);
int							builtin_ft_env(t_minishell *sh, t_command *command,
								bool in_fork);
int							builtin_ft_export(t_minishell *sh,
								t_command *command, bool in_fork);
int							builtin_ft_unset(t_minishell *sh,
								t_command *command, bool in_fork);
void						builtin_restore_stdout(t_minishell *sh,
								t_command *command, int save_fd);
int							builtin_dup_and_save_stdout(t_minishell *sh,
								t_command *command);
//	fonctions > utils tokenisation
bool						handle_quoted_word(t_dynamic_arr *arr, char *input,
								int i, int *_j);
bool						handle_unquoted_word(t_dynamic_arr *arr,
								char *input, int i, int *_j);
bool						tokenize(t_minishell *sh, char *input, int err);
bool						handle_dollars(t_dynamic_arr *arr, char **env,
								char *input, int *_j);
int							add_new_command_info_node(t_minishell *sh);
bool						add_word(t_dynamic_arr *arr, char *input, int i,
								int j);
char						*get_word(char *input, int *_i);

//	fonctions > parsing quotes
bool						is_valid_quote(const char *input, int i);
bool						is_end_quote(char current_char, char quote);
bool						is_valid_user_input(char *input, int i);

//	dynamic arr method
t_dynamic_arr				*dynamic_arr_init_dynamic_arr(size_t capacity);
bool						init_dynamic_arr_for_command(t_command *command,
								size_t capacity);
bool						dynamic_arr_init_stack_dynamic_arr(
								t_dynamic_arr *arr, size_t capacity);
int							dynamic_arr_push_back(t_dynamic_arr *arr,
								char *elem);
bool						dynamic_arr_update_element_by_index(
								t_dynamic_arr *arr, size_t index, char *value);
bool						dynamic_arr_remove_element_by_index(
								t_dynamic_arr *arr, size_t index);
void						dynamic_arr_clear(t_dynamic_arr *arr);
void						dynamic_arr_print_dynamic_arr(t_dynamic_arr *arr);

// fonctions > free.c
void						reset_struct(t_minishell *sh, t_command *command);
void						free_list(t_token *lst);
void						reset_struct(t_minishell *sh, t_command *command);
void						free_and_exit_success(t_minishell *sh,
								t_command *command);
void						free_and_exit_failure(t_minishell *sh,
								t_command *command);
void						free_and_exit_failure_message(t_minishell *sh,
								t_command *command, const char *err_msg);
void						free_and_exit(t_minishell *sh, t_command *command,
								int code, bool err);
void						free_commands(t_command **_command,
								t_command **last_command);
void						free_and_exit_failure_message_and_status(
								t_minishell *sh,
								t_command *command, const char *err_msg,
								int err_status);

// ************ libft functions **************************

int							ft_isspace(int c);
bool						ft_is_in(const char *str, char c);
char						*ft_itoa(int n);
int							ft_isdigit(int i);
void						ft_bzero(void *s, size_t n);
int							ft_isalpha(int i);
char						*ft_strchr(const char *s, int c);
size_t						ft_strlen(const char *s);
char						*ft_strdup(const char *s);
char						*ft_strjoin(char const *s1, char const *s2);
char						**ft_split(char const *s, char c);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
int							ft_strcmp(const char *s1, const char *s2);
void						*ft_calloc(size_t nmemb, size_t size);
size_t						ft_strlcpy(char *dst, const char *src, size_t size);
void						*ft_memset(void *s, int c, size_t n);
void						ft_putchar_fd(char c, int fd);
void						ft_putstr_fd(char *s, int fd);
void						ft_putendl_fd(char *s, int fd);
void						ft_free_elem(void **addr);
char						**ft_copy_tab(char **src, char **dest);
int							ft_isalnum(int i);
char						**ft_dup_tab(char **to_copy);
char						**ft_free_tab(char **tab);
char						**ft_free_tab_with_len(char **tab, size_t len);
int							ft_tab_len(char **tab);
void						ft_memcpy(void *destination, const void *source,
								size_t size);
char						*ft_strjoin_tab_with_len(char **tab, size_t len);
#endif
