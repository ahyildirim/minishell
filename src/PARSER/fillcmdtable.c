#include "../../includes/minishell.h"

static char **create_path(t_lexlist *lex_table)
{
	char	**path; //Yolu tutacak bir değişken
	int		text_count; //Kaç adet text türünde düğüm var onu sayar.
	
	text_count = 0;
	while(lex_table && lex_table->type != SIGN_PIPE)
	{
		if(lex_table->type == TEXT && lex_table->content) //Eğer text türündeyse ve içeriği boş değil ise count'ı bir arttırır.
			text_count++;
		else //Text türünde değil ise
		{
			lex_table = lex_table->next; //Şuan var olduğu elemanı geçer.
			if (lex_table) //Eğer text türünde değil ise zaten bir metakarater türündedir, bu yüzden ondan sonra gelen herhangi bir elemanı işleme almamak için bir kere daha ilerletiriz.
				lex_table = lex_table->next;
			continue;
		}
		lex_table = lex_table->next;
	}
	if(!text_count) //Eğer text türünde hiç düğüm yok ise NULL döndür.
		return (NULL);
	path = (char **)malloc(sizeof(char *) * (text_count + 1)); //Kaç tane text türünde düğüm var ise o kadar yer aç, sonuna NULL ata ve döndür.
	path[text_count] = NULL;
	return (path);
}

static void	fill_cmdnode(t_cmdlist *cmd_table, t_lexlist **lex_table)
{
	char	**tmp_path;
	int		start;

	cmd_table->path = create_path(*lex_table); //Bir lex düğümünden komut yolunu oluşturur ve cmd düğümünün yolunu doldurur.
	tmp_path = cmd_table->path; //Yolu tutmak için geçici bir değişken.
	start = 0; //Komutun başlangıcı takip edilir.
	while (*lex_table && (*lex_table)->type != SIGN_PIPE)
	{
		if(create_filelist(cmd_table, lex_table)) //Eğer gelen düğüm ile dosya oluşturulabiliyor ise oluşturur ve bir sonraki iterasyona geçer.
			continue;
		if(start == 0 && (*lex_table)->type != SIGN_PIPE) //Eğer komutun başındaysak komut yolunu bulmak için fonksiyon çağırılır ve lex
		//Örneğin "ls -l file.txt > output.txt" komutunda start 0 olduğu için ls komut yolunu bulmak için fonksiyon çağırılır fakat -l bir komut yoluna ihtiyaç duymadığı için start arttırılır ve bu fonksiyon bir daha çalışmaz. 
		{
			cmd_expander(&((*lex_table)->content));
			start++;
		}
		if((*lex_table)->content) //İlk komuttan sonra gelecek olan flagleri tutmak için önce içeriği var mı diye kontrol edilir, eğer var ise path'ın içine atıyoruz.
			*(tmp_path++) = (*lex_table)->content; //Yukarıda verdiğim örnekte ls genişletildikten sonra kalan "-l" ve "file.txt" argümanları path'ın içine atılır.
		*lex_table = (*lex_table)->next;
	}
	if(cmd_table->path) //Eğer önceki örnekteki gibi argümanlar var ise commandi path'ın ilk elemanı olduğunu belirtmemiz gerekir.
		cmd_table->command = cmd_table->path[0]; //path[0] = "bin/ls", path[1] = "-l", path[2] = "file.txt"
}

void	fill_cmdtable(void)
{
	t_cmdlist	*tmp_cmdtable;
	t_lexlist	*tmp_lextable;

	if(!g_data.cmd_table)
		return ;
	tmp_cmdtable = g_data.cmd_table;
	tmp_lextable = g_data.lex_table;
	while(tmp_cmdtable)
	{
		fill_cmdnode(tmp_cmdtable, &tmp_lextable); //Her iterasyonda bir komut düğümünü doldurmak için bu fonksiyonu kullanıyoruz.
		if(tmp_lextable && *tmp_lextable->content == *PIPE) //Eğer gelen düğüm PIPE ise bir sonraki düğüme geç.
			tmp_lextable = tmp_lextable->next;
		tmp_cmdtable = tmp_cmdtable->next;
	}
}