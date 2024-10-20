/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearemptylextables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:24:40 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:24:41 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_empty_lextables(t_data *data)
{
	t_lexlist	*lex_table;
	t_lexlist	*tmp_lex_table;

	lex_table = data->lex_table;
	tmp_lex_table = data->lex_table;
	while (lex_table)
	{
		if (lex_table->content == NULL)
		{
			if (lex_table == data->lex_table)
			{
				data->lex_table = data->lex_table->next;
				tmp_lex_table = tmp_lex_table->next;
			}
			else
				tmp_lex_table->next = lex_table->next;
			free(lex_table);
			lex_table = tmp_lex_table;
		}
		tmp_lex_table = lex_table;
		if (lex_table)
			lex_table = lex_table->next;
	}
}
