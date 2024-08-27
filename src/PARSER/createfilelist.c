#include "../../includes/minishell.h"

static t_filelist	*add_filelist_node(t_filelist **file_list, char *file_name, char *meta_char)
{
	t_filelist	*new_node; //yeni oluşturulacak node
	t_filelist	*last_node; //en sone node'u tutar.

	new_node = (t_filelist *)malloc(sizeof(t_filelist)); //yer aç.
	new_node->file_name = file_name; //gelen parametreler ile doldur
	new_node->meta_char = meta_char;
	new_node->next = NULL;
	if(!*file_list) //Eğer oluşacak ilk node ise
	{
		*file_list = new_node; //Listenin ilk başını direkt oluşturulan node eşitle
		new_node->fd = 0; //Dosya fd'sini 0'a eşitle
		return (new_node); //Oluştuurlan node'u döndür
	}
	last_node = *file_list; //Son node değişkenine ilk node'u at
	while(last_node)
		last_node = last_node->next; //Son node değişkenini liste bitene kadar ilerlet.
	last_node->next = new_node; //En sondan sonraki node'u yeni oluşturulan node olarak belirle
	new_node->fd = 0; //fd'yi 0 a eşitle
	return(new_node); //Oluşturulan son node'u döndür.
}

int	create_filelist(t_cmdlist *cmd_table, t_lexlist **lex_table)
{
	char		*meta_char;
	char		*file_name;
	t_filelist	*temp_filelist;

	if((*lex_table)->type == TEXT) //Eğer gelen ilk lex düğümü TEXT ise dosya oluşturulamayacağı için programdan çık.
		return (0);
	meta_char = is_meta_char((*lex_table)->content); //Meta karakterin hangisi olduğunu bul.
	file_name = NULL; //Dosya adını boşalt.
	if((*lex_table)->next) //Eğer lex table'da sonraki var ise dosyanın ismi vardır, bu yüzden dosya ismini belirle.
		file_name = (*lex_table)->next->content;
	if(*meta_char != *PIPE) //Eğer gelen meta karakter "|" değil ise yeni bir file node'u oluştur
	{
		temp_filelist = add_filelist_node(&(cmd_table->files), file_name, meta_char);
		temp_filelist->meta_char = (*lex_table)->content;
	}
	*lex_table = (*lex_table)->next; //Bir sonraki lex düğümüne geç
	if(*lex_table) //Eğer bir sonraki düğüm mevcut ise, o düğümü de geçmemiz gerekiyor örneğin "< ahmet" yaptığımız zaman hem < işaretçisini hem de ahmet düğümünü geçmemiz gerek ki işlemlerimiz hatasız olsun.
		*lex_table = (*lex_table)->next;
	return (1);
}