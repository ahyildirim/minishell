/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:25:46 by ahyildir          #+#    #+#             */
/*   Updated: 2024/10/19 19:00:20 by ahyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_cmdnode(t_cmdlist *cmd_table)
{
	cmd_table->pid = -1;
	cmd_table->input_file = SSTDIN;
	cmd_table->output_file = SSTDOUT;
	cmd_table->command = NULL;
	cmd_table->path = NULL;
	cmd_table->next = NULL;
	cmd_table->heradoc_values = NULL;
	cmd_table->files = NULL;
}

static void	create_cmd_nodes(int pipe_count, t_data *data)
{
	t_cmdlist	*tmp_cmdtable;

	data->cmd_table = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	init_cmdnode(data->cmd_table);
	tmp_cmdtable = data->cmd_table;
	while (--pipe_count)
	{
		tmp_cmdtable->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		init_cmdnode(tmp_cmdtable->next);
		tmp_cmdtable = tmp_cmdtable->next;
	}
}

static void	create_cmdlist(t_lexlist *lex_table, t_data *data)
{
	int	pipe_count;

	if (!lex_table)
		return ;
	pipe_count = 1;
	while (lex_table)
	{
		if (lex_table->type == SIGN_PIPE)
			pipe_count++;
		lex_table = lex_table->next;
	}
	data->cnt_pipe = pipe_count;
	create_cmd_nodes(pipe_count, data);
}

void	parser(t_data *data)
{
	data->cmd_table = NULL;
	create_cmdlist(data->lex_table, data);
	fill_cmdtable(data);
	create_files(data->cmd_table, data);
}
