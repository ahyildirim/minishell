/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addlexnode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:24:50 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:24:51 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexlist	*add_lex_node(t_lexlist **node)
{
	t_lexlist	*new;
	t_lexlist	*temp;

	new = (t_lexlist *)malloc(sizeof(t_lexlist));
	if (!new)
		return (NULL);
	new->content = NULL;
	new->type = 0;
	new->next = NULL;
	if (!*node)
	{
		*node = new;
		return (*node);
	}
	temp = *node;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (new);
}
