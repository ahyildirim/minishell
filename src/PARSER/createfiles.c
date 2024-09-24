#include "../../includes/minishell.h"

static int	check_directory_error(char *file_name)
{
	char	*tmp;

	tmp = file_name;
	while(file_name && *file_name)
	{
		if(*(file_name++) == '/')
		{
			print_error("-bash: ", tmp, ": is a directory\n");
			return (0);
		}
	}
	return (1);
}

static int	check_file_error(t_filelist *file, int *fd)
{
	int	error_flag;

	error_flag = 0;
	if(!file->file_name)
		error_flag = 1;
	if(!check_directory_error(file->file_name))
		error_flag = 1;
	if(!error_flag && *file->file_name == '\"')
	{
		error_flag = 1;
		print_error("-bash: No such file or directory\n", NULL, NULL);
	}
	else if(!error_flag && *file->file_name == '$')
	{
		error_flag = 1;
		print_error("-bash: ", file->file_name, ": ambiguous redirect\n");
	}
	if(!error_flag)
		return (error_flag);
	file->fd = SSTDERR;
	*fd = file->fd;
	return (error_flag);
}

static void	create_outfile(t_cmdlist *cmd_table, t_filelist *file)
{
	char	*outfile_path;
	char	buf[256];

	if(check_file_error(file, &cmd_table->output_file))
		return ;
	outfile_path = NULL;
	ft_strjoin(&outfile_path, (char *)getcwd(buf, 256));
	str_append_char(&outfile_path, '/');
	ft_strjoin(&outfile_path, file->file_name);
	if(file->meta_char[1] == DOUBLE_GREAT[1])
		file->fd = open(outfile_path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		file->fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	cmd_table->output_file = file->fd;
	free(outfile_path);
}

void	create_infile(t_cmdlist *cmd_table, t_filelist *file, t_data *data)
{
	char	*infile_path;
	char	buf[256];

	if(file->meta_char[1] == DOUBLE_LESS[1])
	{
		cmd_table->input_file = HERADOC;
		return;
	}
	if(check_file_error(file, &cmd_table->input_file))
		return;
	infile_path = NULL;
	ft_strjoin(&infile_path, (char *)getcwd(buf, 256));
	str_append_char(&infile_path, '/');
	ft_strjoin(&infile_path, file->file_name);
	if(access(infile_path, F_OK) == 0)
		file->fd = open(infile_path, O_RDONLY, 0777);
	if(file->fd <= SSTDERR && file->fd != HERADOC)
	{
		print_error("-bash: ", file->file_name, ": No such file or directory\n");
		data->output = 1;
		file->fd = SSTDERR;
	}
	cmd_table->input_file = file->fd;
	free(infile_path);
}

void	create_files(t_cmdlist	*cmd_table, t_data *data)
{
	t_filelist	*tmp;

	if(!cmd_table)
		return ;
	
	run_heradoc(cmd_table, data); //Her şeyden önce ilk olarak heradoc bakıyoruz, bunun için heradoc fonksiyonunu başlatıyoruz.
	if(data->output || !cmd_table) //Eğer cmd table dolmadıysa returnla.
		return ;
	while(cmd_table) //Yine tüm komut tablosu üstünde gez, dosya oluşturulacak mı bak.
	{
		tmp = cmd_table->files;
		while (tmp)
		{
			if(*tmp->meta_char == *SINGLE_GREAT) //Eğer '>' gelirse bu bir output dosyasıdır, o yüzden bir outfile oluşturma fonksiyonu ile dosyayı oluştur.
				create_outfile(cmd_table, tmp);
			else
				create_infile(cmd_table, tmp, data);
			if(tmp->fd == SSTDERR)
			{
				data->output = 1;
				break;
			}
			tmp = tmp->next;
		}
		cmd_table = cmd_table->next;
	}
}
