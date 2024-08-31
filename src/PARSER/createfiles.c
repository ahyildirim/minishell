#include "../../includes/minishell.h"

static void	create_outfile(t_cmdlist *cmd_table, t_filelist *file)
{
	char	*outfile_path;
}

void	create_files(t_cmdlist	*cmd_table, t_data *data)
{
	t_filelist	*tmp;

	if(!cmd_table)
		return ;
	start_heradoc(cmd_table, data); //Her şeyden önce ilk olarak heradoc bakıyoruz, bunun için heradoc fonksiyonunu başlatıyoruz.
	if(data->output || !cmd_table) //Eğer cmd table dolmadıysa returnla.
		return ;
	while(cmd_table) //Yine tüm komut tablosu üstünde gez, dosya oluşturulacak mı bak.
	{
		tmp = cmd_table->files;
		while (tmp)
		{
			if(*tmp->meta_char == *SINGLE_GREAT) //Eğer '>' gelirse bu bir output dosyasıdır, o yüzden bir outfile oluşturma fonksiyonu ile dosyayı oluştur.
				create_outfile(cmd_table, tmp); //TODO
		}
	}
}