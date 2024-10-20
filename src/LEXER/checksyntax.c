/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksyntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:24:53 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:28:52 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	complete_arg(t_lexlist *lex_table, t_data *data)
{
	char	*str;

	str = get_arg(data);
	if (!str)
		return (1);
	create_lexlist(str, &lex_table, data);
	set_lex_types(lex_table, data);
	str_append_char(&data->input, ' ');
	ft_strjoin(&data->input, str);
	free(str);
	return (-1);
	return (1);
}

static int	check_pipe_error(t_lexlist *lex_table, t_data *data)
{
	if (lex_table->next && lex_table->next->type == SIGN_PIPE)
		return (print_lex_error(lex_table, data));
	else if (!lex_table->next)
		return (complete_arg(lex_table, data));
	return (1);
}

static int	check_file(t_lexlist *lex_table, t_data *data)
{
	if (!lex_table->next || (lex_table->next && lex_table->next->type != TEXT))
	{
		if (lex_table->next)
		{
			print_error("-bash syntax error near unexpected token '",
				lex_table->next->content, "'\n");
			data->last_output = 258;
			lexer_free_no_heradoc(lex_table, data);
			return (1);
		}
		else
		{
			print_error("-bash syntax error near unexpected token '", "newline",
				"'\n");
			data->last_output = 258;
			lexer_free_no_heradoc(lex_table, data);
			return (1);
		}
	}
	return (1);
}

static int	check_errors(t_lexlist *lex_table, t_data *data)
{
	int	pipe_error;

	if (lex_table == data->lex_table && lex_table->type == SIGN_PIPE)
	{
		print_lex_error(lex_table, data);
		return (-1);
	}
	else if (lex_table->type != TEXT && lex_table->type != SIGN_PIPE)
	{
		if (check_file(lex_table, data))
			return (-1);
	}
	else if (lex_table->type == SIGN_PIPE)
	{
		pipe_error = check_pipe_error(lex_table, data);
		if (pipe_error < 0)
			return (0);
		else if (pipe_error == 0)
			return (-1);
	}
	return (1);
}

void	check_syntax(t_data *data)
{
	t_lexlist	*lex_table;
	int			error;

	lex_table = data->lex_table;
	while (lex_table)
	{
		error = check_errors(lex_table, data);
		if (error == -1)
			break ;
		else if (error == 0)
			continue ;
		if (data->lex_table)
			lex_table = lex_table->next;
		else
			lex_table = NULL;
	}
}
