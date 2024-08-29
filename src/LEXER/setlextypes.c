#include "../../includes/minishell.h"

void	set_lex_types(t_lexlist *lex_table, t_data *data)
{
	char	*meta_chars;

	if(!lex_table)
		return ;
	while(lex_table)
	{
		meta_chars = is_meta_char(lex_table->content, data); //meta karakter var ise type belirlememiz gerekiyor.
		if(meta_chars)
			lex_table->type = (*meta_chars - 1) * ft_strlen(meta_chars); //type ise ascii karakterinin bir eksiği ve boyutu ile çarpılarak bulunuyor.
		else
			lex_table->type = 0; //eğer meta karakter yoksa normal text'dir ve type'ı 0 dır.
		lex_table = lex_table->next;
	}
}