/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:24:32 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/24 16:44:19 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "macro.h"
# include "tables.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>

extern int	g_sig;

int			create_filelist(t_cmdlist *cmd_table, t_lexlist **lex_table,
				t_data *data);
int			update_env(t_data *data, char *env_name, char *new_arg);
int			print_lex_error(t_lexlist *lex_table, t_data *data);
int			quote_error(t_lexlist *lex_table, t_data *data);
int			env_arg_control(char *env, t_data *data);
int			ft_strcmp(char *str1, char *str2);
int			ft_atoi(const char *str);
int			get_array_len(char **ar);
int			is_builtin(char *cmd);
int			ft_isdigit(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			type_control(t_data *data, t_cmdlist *cmd, char **envs);

size_t		trim_left_spaces(char **command);
size_t		ft_strlen(const char *s);

char		*ft_strlcpy(char *dst, char *src, int len);
char		*is_meta_char(char *command, t_data *data);
char		*get_env_name(char *content);
char		*ft_strdup(const char *src);
char		*get_arg(t_data *data);
char		*get_cmd(char *cmd);
char		*ft_itoa(int n);

void		run_builtin(t_data *data, t_cmdlist *cmd, int builtin, int *fd);
void		exec_command(t_data *data, t_cmdlist *cmd_l, int *fd, int fd_index);
void		create_lexlist(char *command, t_lexlist **lex_table, t_data *data);
void		run_process(t_data *data, t_cmdlist *cmd, int *fd, int fd_index);
void		create_dup(t_cmdlist *cmd, t_data *data, int *fd, int fd_index);
void		lexer_free_no_heradoc(t_lexlist *lex_table, t_data *data);
void		dollar_expander(char **dst, char **src, t_data *data);
void		create_files(t_cmdlist *cmd_table, t_data *data);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		env_expander(char **dst, char *env, t_data *data);
void		run_heradoc(t_cmdlist *cmd_table, t_data *data);
void		set_lex_types(t_lexlist *lex_table, t_data *data);
void		print_error(char *str1, char *str2, char *str3);
void		com_export(t_cmdlist *cmd_node, t_data *data);
void		com_env(t_cmdlist *cmd_node, t_data *data);
void		com_cd(t_data *data, t_cmdlist *cmd_node);
void		com_unset(t_cmdlist *cmd, t_data *data);
void		cmd_expander(char **cmd, t_data *data);
void		com_exit(t_cmdlist *cmd, t_data *data);
void		delete_env(char *name, t_data *data);
void		fill_envs(t_data *data, char **env);
void		clear_empty_lextables(t_data *data);
void		str_append_char(char **dst, char c);
void		ft_strjoin(char **dst, char *src);
void		ft_putstr_fd(char *s, int fd);
void		init_metachars(t_data *data);
void		free_env_cpy(char **envlist);
void		free_metachars(t_data *data);
void		main_executor(t_data *data);
void		fill_cmdtable(t_data *data);
void		free_envtable(t_data *data);
void		check_syntax(t_data *data);
void		com_echo(t_cmdlist *cmd, t_data *data);
void		free_utils(t_data *data);
void		free_loop(t_data *data);
void		free_core(t_data *data);
void		com_pwd(t_cmdlist *cmd, t_data *data);
void		init_data(t_data *data);
void		expander(t_data *data);
void		wait_all(t_data *data);
void		parser(t_data *data);
void		lexer(t_data *data);
void		handle_signal(void);
void		clear_pipe(int *fd);
void		handle_sigint(int sig);
void		check_quotes(t_lexlist *lex_table, t_data *data);

t_env		*add_new_envnode(t_env **env_table, char *env);

t_lexlist	*add_lex_node(t_lexlist **node);

#endif
