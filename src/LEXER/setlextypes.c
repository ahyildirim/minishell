/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setlextypes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:04 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:25:05 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_lex_types(t_lexlist *lex_table, t_data *data)
{
	char	*meta_chars;

	if (!lex_table)
		return ;
	while (lex_table)
	{
		meta_chars = is_meta_char(lex_table->content, data);
		if (meta_chars)
			lex_table->type = (*meta_chars - 1) * ft_strlen(meta_chars);
		else
			lex_table->type = 0;
		lex_table = lex_table->next;
	}
}
