#include "../../includes/minishell.h"

t_lexlist *add_lex_node(t_lexlist **node)
{
	t_lexlist *new;
	t_lexlist *temp;

	new = malloc(sizeof(t_lexlist));
	if (!new)
		return (NULL); // malloc başarısız olursa NULL döner
	new->content = NULL;
	new->type = 0;
	new->next = NULL;

	if (!*node)
	{
		*node = new; // Liste boşsa yeni düğüm ilk düğüm olur
		return (*node);
	}
	temp = *node;
	while (temp->next) // Listenin sonuna git
		temp = temp->next;
	temp->next = new; // Yeni düğümü listeye ekle
	return (new); // Yeni eklenen düğümü döndür
}