/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:24:59 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/24 18:28:04 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_quote_len(const char *command, t_data *data)
{
	int		len;
	char	c;

	len = 0;
	while (*command)
	{
		if (*command == '\'' || *command == '"')
			break ;
		command++;
	}
	if (*command == '\0')
		return (len);
	c = *command;
	command++;
	len++;
	while (*command)
	{
		len++;
		if (*command == c)
			break ;
		command++;
	}
	if (*command == '\0')
		data->output = -1;
	return (len);
}

static int	get_command_len(char *command, t_data *data)
{
	size_t	len;
	int		quote_len;
	char	*meta;

	len = 0;
	while (command && *command && *command != 32)
	{
		meta = is_meta_char(command, data);
		if (meta)
		{
			if (!len)
				len += ft_strlen(meta);
			break ;
		}
		if (*command == *SINGLE_QUOTE || *command == *DOUBLE_QUOTE)
		{
			quote_len = get_quote_len(command, data);
			len += quote_len;
			command += quote_len;
			continue ;
		}
		len++;
		command++;
	}
	return (len);
}

static void	parse_command(char **command, t_lexlist *last_node, t_data *data)
{
	int		len;
	char	*temp;

	len = get_command_len(*command, data);
	temp = (char *)malloc(len + 1);
	last_node->content = temp;
	temp[len] = 0;
	while (len--)
		*(temp++) = *((*command)++);
}

void	create_lexlist(char *command, t_lexlist **lex_table, t_data *data)
{
	t_lexlist	*last_node;

	if (!command || !*command)
		return ;
	trim_left_spaces(&command);
	last_node = add_lex_node(lex_table);
	parse_command(&command, last_node, data);
	create_lexlist(command, lex_table, data);
}

void	lexer(t_data *data)
{
	data->lex_table = NULL;
	create_lexlist(data->input, &(data->lex_table), data);
	set_lex_types(data->lex_table, data);
	check_quotes(data->lex_table, data);
	if (data->output == -1)
		quote_error(data->lex_table, data);
	check_syntax(data);
}
