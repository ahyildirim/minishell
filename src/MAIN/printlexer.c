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

void print_cmd(t_data *data)
{
	t_cmdlist *tmp;

	tmp = data->cmd_table;
	printf("----CMD-----\n");
	while(tmp)
	{
		printf("command: %s, Path: %s\n", tmp->command, *(tmp->path));
		tmp = tmp->next;
	}
}