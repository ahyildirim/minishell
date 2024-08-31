#ifndef MINISHELL_H
#define MINISHELL_H

#include "tables.h"
#include "macro.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

extern		int g_sig;

int			create_filelist(t_cmdlist *cmd_table, t_lexlist **lex_table, t_data *data);
int			print_lex_error(t_lexlist *lex_table);
int			ft_strcmp(char *str1, char *str2);

size_t		trim_left_spaces(char **command);
size_t		ft_strlen(const char *s);


char		*ft_strlcpy(char *dst, char *src, int len);
char		*is_meta_char(char *command, t_data *data);
char		*get_env_name(char *content);
char		*ft_strdup(const char *src);
char		*get_arg(t_data *data);
char		*ft_itoa(int n);

void		create_lexlist(char *command, t_lexlist **lex_table, t_data *data);
void		dollar_expander(char **dst, char **src, t_data *data);
void		create_files(t_cmdlist	*cmd_table, t_data *data);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		env_expander(char **dst, char *env, t_data *data);
void		set_lex_types(t_lexlist *lex_table, t_data *data);
void		print_error(char *str1, char *str2, char *str3);
void		cmd_expander(char **cmd, t_data *data);
void		fill_envs(t_data *data, char **env);
void		clear_empty_lextables(t_data *data);
void		str_append_char(char **dst, char c);
void		start_heradoc(t_cmdlist *cmd_table, t_data *data);
void		ft_strjoin(char **dst, char *src);
void		ft_putstr_fd(char *s, int fd);
void		init_metachars(t_data *data);
void		fill_cmdtable(t_data *data);
void		check_syntax(t_data *data);
void		expander(t_data *data);
void		lexer(t_data *data);
void		handle_signal(void);
void		parser(t_data *data);


t_lexlist	*add_lex_node(t_lexlist **node);


void print_lexer(t_data *data);
void	print_parser(t_data *data);
void print_cmd(t_data *data);

#endif
