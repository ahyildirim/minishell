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

static void create_cmd_nodes(int pipe_count, t_data *data)
{
	t_cmdlist	*tmp_cmdtable;

	data->cmd_table = (t_cmdlist *)malloc(sizeof(t_cmdlist)); //yer aç
	init_cmdnode(data->cmd_table); //ilk komut için node oluştur.
	tmp_cmdtable = data->cmd_table;
	while(--pipe_count) //kalanlar için node oluştur.
	{
		tmp_cmdtable->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		init_cmdnode(tmp_cmdtable->next);
		tmp_cmdtable = tmp_cmdtable->next;
	}
}

static void	create_cmdlist(t_lexlist *lex_table, t_data *data)
{
	int	pipe_count; //Kaç adet komut düğümü oluşturulacağımız.

	if(!lex_table)
		return ;
	pipe_count = 1; //Her türlü 1 tane komut girileceği için 1'den başlatıyoruz.
	while(lex_table)
	{
		if(lex_table->type == SIGN_PIPE) //Her PIPE geldiğinde yeni komuta geçmemiz gerektiği için bu sayı kaç adet komut düğümü oluşturuacağımız için gerekli.
			pipe_count++;
		lex_table = lex_table->next;
	}
	data->cnt_pipe = pipe_count;
	create_cmd_nodes(pipe_count, data); //Node'ları oluşturuyoruz.
}

void	parser(t_data *data)
{
	data->cmd_table = NULL;
	create_cmdlist(data->lex_table, data);
	fill_cmdtable(data);
	create_files(data->cmd_table, data);
}
