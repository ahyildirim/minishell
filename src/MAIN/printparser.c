#include "../../includes/minishell.h"

void	print_parser(t_data *data)
{
	int	node;
	int	i;
	t_cmdlist	*tmp;
	//t_filelist	*filelist;

	node = 1;
	tmp = data->cmd_table;
	//filelist = tmp->files;
	while(tmp)
	{
		i = 0;
		printf("-------NODE %d------\n", node++);
		printf("PATH: ");
		while(tmp->path && tmp->path[i])
			printf("%s: ", tmp->path[i++]);
		printf("\nCMD: %s\n", tmp->command);
		printf("infile: %d\n", tmp->input_file);
		printf("outfile: %d\n", tmp->output_file);
		printf("pid: %d\n", tmp->pid);
		/* printf("~FILES~\n");
		while(filelist)
		{
			printf("{fd: %d, redirect: %s, filename: %s}", filelist->fd, filelist->meta_char, filelist->file_name);
			filelist = filelist->next;
		}
		printf("\n\n"); */
		tmp = tmp->next;
	}
}