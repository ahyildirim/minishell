/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setlextypes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:04 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/24 18:28:17 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_quotes(t_lexlist *lex_table, t_data *data)
{
	if (lex_table && (ft_strcmp(lex_table->content, "\'\'")
			|| ft_strcmp(lex_table->content, "\"\"")))
	{
		print_error("-bash: ", " :", " command not found\n");
		lexer_free_no_heradoc(lex_table, data);
		data->last_output = 127;
	}
}

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
