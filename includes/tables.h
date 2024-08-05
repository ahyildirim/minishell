#ifndef TABLES_H
#define TABLES_H

typedef struct s_env
{
	char			*env_name;
	char			*content;
	struct s_env	*next;
	
}				t_env;

typedef struct s_lexlist
{
	char			type;
	char 			*content;
	struct s_lexlist *next;
}				t_lexlist;

typedef struct s_data
{
	char		*input;
	char		**metachars;
	int			is_reading;
	int			last_output;
	int			output;
	int			main_pid;
	t_lexlist	*lex_table;
	t_env		*env_table;
}				t_data;

#endif