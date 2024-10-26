/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillcmdtable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:40 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/05 19:25:41 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**create_path(t_lexlist *lex_table)
{
	char	**path;
	int		text_count;

	text_count = 0;
	while (lex_table && lex_table->type != SIGN_PIPE)
	{
		if (lex_table->type == TEXT && lex_table->content)
			text_count++;
		else
		{
			lex_table = lex_table->next;
			if (lex_table)
				lex_table = lex_table->next;
			continue ;
		}
		lex_table = lex_table->next;
	}
	if (!text_count)
		return (NULL);
	path = (char **)malloc(sizeof(char *) * (text_count + 1));
	path[text_count] = NULL;
	return (path);
}

static void	fill_cmdnode(t_cmdlist *cmd_table, t_lexlist **lex_table,
		t_data *data)
{
	char	**tmp_path;
	int		start;

	cmd_table->path = create_path(*lex_table);
	tmp_path = cmd_table->path;
	start = 0;
	while (*lex_table && (*lex_table)->type != SIGN_PIPE)
	{
		if (create_filelist(cmd_table, lex_table, data))
			continue ;
		if (start == 0 && (*lex_table)->type != SIGN_PIPE)
		{
			cmd_expander(&((*lex_table)->content), data);
			start++;
		}
		if ((*lex_table)->content)
			*(tmp_path++) = (*lex_table)->content;
		*lex_table = (*lex_table)->next;
	}
	if (cmd_table->path)
		cmd_table->command = cmd_table->path[0];
}

void	fill_cmdtable(t_data *data)
{
	t_cmdlist	*tmp_cmdtable;
	t_lexlist	*tmp_lextable;

	if (!data->cmd_table)
		return ;
	tmp_cmdtable = data->cmd_table;
	tmp_lextable = data->lex_table;
	while (tmp_cmdtable)
	{
		fill_cmdnode(tmp_cmdtable, &tmp_lextable, data);
		if (tmp_lextable && *tmp_lextable->content == *PIPE)
			tmp_lextable = tmp_lextable->next;
		tmp_cmdtable = tmp_cmdtable->next;
	}
}
