#include "../../includes/minishell.h"

static t_filelist	*add_filelist_node(t_filelist **file_list, char *file_name, char *meta_char)
{
	t_filelist *tmp;
	
	if(!file_name || !meta_char)
		return (NULL);
	if(!*file_list)
	{
		*file_list = (t_filelist *)malloc(sizeof(t_filelist));
		tmp = *file_list;
	}
	else
	{
		tmp = *file_list;
		while(tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = (t_filelist *)malloc(sizeof(t_filelist));
		tmp = tmp->next;
	} 
	tmp->fd = 0;
	tmp->file_name = file_name;
	tmp->meta_char = meta_char;
	tmp->next = NULL;
	return(tmp);
}

int	create_filelist(t_cmdlist *cmd_table, t_lexlist **lex_table, t_data *data)
{
	char		*meta_char;
	char		*file_name;
	t_filelist	*temp_filelist;

	if(!cmd_table || !lex_table || !(*lex_table))
		return (0);
	if((*lex_table)->type == TEXT) //Eğer gelen ilk lex düğümü TEXT ise dosya oluşturulamayacağı için programdan çık.
		return (0);
	meta_char = is_meta_char((*lex_table)->content, data); //Meta karakterin hangisi olduğunu bul.
	file_name = NULL; //Dosya adını boşalt.
	if((*lex_table)->next) //Eğer lex table'da sonraki var ise dosyanın ismi vardır, bu yüzden dosya ismini belirle.
		file_name = (*lex_table)->next->content;
	if(*meta_char != *PIPE) //Eğer gelen meta karakter "|" değil ise yeni bir file node'u oluştur
	{
		temp_filelist = add_filelist_node(&(cmd_table->files), file_name, meta_char);
		if(!temp_filelist)
			return (0);
		if(*lex_table)
			temp_filelist->meta_char = (*lex_table)->content;
	}
	*lex_table = (*lex_table)->next; //Bir sonraki lex düğümüne geç
	if(*lex_table) //Eğer bir sonraki düğüm mevcut ise, o düğümü de geçmemiz gerekiyor örneğin "< ahmet" yaptığımız zaman hem < işaretçisini hem de ahmet düğümünü geçmemiz gerek ki işlemlerimiz hatasız olsun.
		*lex_table = (*lex_table)->next;
	return (1);
}
