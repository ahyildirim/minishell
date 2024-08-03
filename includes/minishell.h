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

char		*is_meta_char(char *command);
char		*get_arg();

void		set_lex_types(t_lexlist *lex_table);
void		print_error(char *str1, char *str2, char *str3);
void		str_append_char(char **dst, char c);
void		create_lexlist(char *command, t_lexlist **lex_table);
void		ft_strjoin(char **dst, char *src);
void		check_syntax(void);
void		lexer(void);

int			print_lex_error(t_lexlist *lex_table);

size_t	ft_strlen(const char *s);


#endif