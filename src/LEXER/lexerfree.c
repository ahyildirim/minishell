#include "../../includes/minishell.h"

static int	skip_heradoc(t_lexlist **lex_table, t_lexlist **tmp, t_lexlist *stop, int *flag)
{
	if(stop == *lex_table)
		*flag |= 1;
	if((*lex_table)->type == SIGN_DOUBLE_LESS && !*flag)
	{
		if(*lex_table && *lex_table != stop)
			*lex_table = (*lex_table)->next;
		*tmp = *lex_table;
		*lex_table = (*lex_table)->next;
		return (1);
	}
	return (0);
}

void	lexer_free_no_heradoc(t_lexlist *stop, t_data *data)
{
	t_lexlist	*lexer;
	t_lexlist	*tmp;
	int			flag;

	lexer = data->lex_table;
	flag = 0;
	while(lexer)
	{
		if(skip_heradoc(&lexer, &tmp, stop, &flag))
			continue;
		if(data->lex_table == lexer)
		{
			data->lex_table = data->lex_table->next;
			tmp = data->lex_table;
		}
		else
			tmp = tmp->next;
		free(lexer->content);
		free(lexer);
		if(data->lex_table == tmp)
			lexer = tmp;
		else
			lexer = tmp->next;
	}
}
