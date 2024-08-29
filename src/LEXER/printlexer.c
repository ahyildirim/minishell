#include "../../includes/minishell.h"

void print_lexer(t_data *data)
{
	t_lexlist *tmp;

	tmp = data->lex_table;
	printf("----LEXER-----\n");
	while(tmp)
	{
		printf("TYPE: %d, CONTENT: %s\n", tmp->type, tmp->content);
		tmp = tmp->next;
	}
}