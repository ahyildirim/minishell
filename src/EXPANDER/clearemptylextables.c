#include "../../includes/minishell.h"

void	clear_empty_lextables(void)
{
	t_lexlist	*lex_table;
	t_lexlist	*tmp_lex_table;

	lex_table = g_data.lex_table; //Listenin ilk node'u
	tmp_lex_table = g_data.lex_table; //Listenin ilk node'u
	while(lex_table)
	{
		if(lex_table->content == NULL) //Eğer content boş ise
		{
			if(lex_table == g_data.lex_table) //Eğer ilk node ise
			{
				g_data.lex_table = g_data.lex_table->next; //İlk node'u güncelle.
				tmp_lex_table = tmp_lex_table->next; //Geçici node'u da güncelle.
			}
			else //İlk node değil ise
				tmp_lex_table->next = lex_table->next; //Bir önceki node'un next'ini günceller. Böylece bağlı listenin bağlantısını kaybetmeyzi.
			free(lex_table); //Boş node'u serbest bırak.
			lex_table = tmp_lex_table; //Asıl node'u geçici node'a günceller.
		}
		tmp_lex_table = lex_table; //Geçici node'u günceller.
		if(lex_table) //Eğer var ise
			lex_table = lex_table->next; //Bir sonraki iterasyona geçer.
	}
}