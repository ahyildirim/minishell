#include "../../includes/minishell.h"

t_lexlist *add_lex_node(t_lexlist **node)
{
	t_lexlist *new;

	if(!*node)
	{
		new = malloc(sizeof(t_lexlist));
		new->content = NULL;
		new->type = 0;
		new->next = NULL;
		node = new;
		return (node);
	}
	new = *node;
	while(new->next)
		new = new->next;
	new = malloc(sizeof(t_lexlist));
	new->content = NULL;
	new->type = 0;
	new->next = NULL;
	return (new);
}