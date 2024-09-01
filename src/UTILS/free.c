#include "../../includes/minishell.h"

static void free_filelist(t_filelist *files)
{
	t_filelist	*tmp;

	while(files)
	{
		tmp = files;
		files = files->next;
		if(tmp->fd > SSTDERR)
			close(tmp->fd);
		free(tmp);
	}
}

static void free_parser(t_data *data)
{
	t_cmdlist	*parser;
	t_cmdlist	*tmp;

	parser = data->cmd_table;
	while(parser)
	{
		tmp = parser;
		parser = parser->next;
		free_filelist(tmp->files);
		if(tmp->path)
			free(tmp->path);
		if(tmp->heradoc_values)
			free(tmp->heradoc_values);
		free(tmp);
	}
	data->cmd_table = NULL;
}

static void	free_lexer(t_data *data)
{
	t_lexlist	*lexer;
	t_lexlist	*tmp;

	lexer = data->lex_table;
	while(lexer)
	{
		tmp = lexer;
		lexer = lexer->next;
		if(tmp->content)
			free(tmp->content);
		free(tmp);
	}
	data->lex_table = NULL;
}

void	free_loop(t_data *data)
{
	if(data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if(data->lex_table)
		free_lexer(data);
	if(data->cmd_table)
		free_parser(data);
	if(data->heradoc_fd > SSTDERR)
	{
		close(data->heradoc_fd);
		data->heradoc_fd = 0;
	}
}
