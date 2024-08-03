#ifndef TABLES_H
#define TABLES_H

typedef struct s_lexlist
{
	char type;
	char *content;
	struct s_lexlist *next;
}				t_lexlist;

typedef struct s_data
{
	char		*input;
	char		**metachars;
	int			is_reading;
	int			output;
	t_lexlist	*lex_table;
}				t_data;

#endif