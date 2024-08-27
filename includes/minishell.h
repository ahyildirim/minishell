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

t_data 		g_data;

size_t		trim_left_spaces(char **command);

t_lexlist	*add_lex_node(t_lexlist **node);

char		*ft_strlcpy(char *dst, char *src, int len);
char		*is_meta_char(char *command);
char		*ft_itoa(int n);
char		*get_arg();

void		create_lexlist(char *command, t_lexlist **lex_table);
void		print_error(char *str1, char *str2, char *str3);
void		dollar_expander(char **dst, char **src);
void		str_append_char(char **dst, char c);
void		env_expander(char **dst, char *env);
void		set_lex_types(t_lexlist *lex_table);
void		ft_strjoin(char **dst, char *src);
void		clear_empty_lextables(void);
void		cmd_expander(char **cmd);
void		fill_cmdtable(void);
void		check_syntax(void);
void		expander(void);
void		lexer(void);

int			create_filelist(t_cmdlist *cmd_table, t_lexlist **lex_table);
int			print_lex_error(t_lexlist *lex_table);
int			ft_strcmp(char *str1, char *str2);

size_t		ft_strlen(const char *s);


#endif