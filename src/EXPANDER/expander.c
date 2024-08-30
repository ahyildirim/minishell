#include "../../includes/minishell.h"

void	env_expander(char **dst, char *env, t_data *data)
{
	t_env	*tmp_env;

	tmp_env = data->env_table;
	while(tmp_env) //Tüm environment nodeları içinde dolaş
	{
		if(ft_strcmp(env, tmp_env->env_name)) //env adları eşleşiyor ise
		{
			ft_strjoin(dst, tmp_env->content); //genişleteceğimiz text'e o environmentin adı olarak belirle.
			break;
		}
		tmp_env = tmp_env->next;
	}
}

static void	set_order(char **dst, char **src, t_data *data)
{
	if(**src == *DOLLAR) //Eğer dolar ise bu bir custom belirlenmiş environment variabledır. Bu yüzden doların devamında ne olduğuna bakmamız gerekiyor.
		dollar_expander(dst, src, data);
	if(**src == *TILDA)
		env_expander(dst, "HOME", data); //Eğer ~ ise direkt HOME environmentini atamamız gerekir. (~ Shell'de anadizini ifade eder.)
}

static void	text_expander(t_lexlist *lex_table, int meta, t_data *data)
{
	char	*command;
	char	*expanded_text;
	int		flag;

	command = lex_table->content; //Conteni command adlı pointera atıyoruz ki orijinal content pointerı değişmesin
	expanded_text = NULL;
	flag = 0; //Tırnak içinde olup olmadığımızı kontrol etmemizi sağlayan bir flag
	while(*command)
	{
		if(*command == '\'' && (flag == 0 || flag == 1)) //Eğer tek tırnak geldiyse ve flag 0 veya 1 ise
			flag ^= 1;  //Flag'i 1 ile XOR operatörünü uygula. XOR operatörü eğer değerler aynı ise 0 çıktısını verir farklı ise kıyaslandığı sayı ile asıl sayının toplamını döndürür.
			//Yani tırnak içinde değilsek (flag 0 ise), tırnak içinde olduğumuzu doğrulayan flag 1 olur, sonraki iterasyonlarda tekrar tırnağa denk gelirsek flag 1 olduğu için 1'in 1 ile XOR kıyaslaması 0 olur ve tırnaktan çıktığımızı belirleriz.
		else if(*command == '\"' && (flag == 0 || flag == 2)) //Yukarıdakinin aynı mantığı fakat çift tırnak versiyonu.
			flag ^= 2;
		else if((*command == *DOLLAR || *command == *TILDA) && (flag == 0 || flag == 2)) //Eğer $ veya ~ var ise bunların ne yapması gerektiğini belirliyoruz.
			set_order(&expanded_text, &command, data); //Daha iyi anlamak için shell'de environment variables'ı detaylı bir şekilde araştır.
		else
			str_append_char(&expanded_text, *command); //Eğer hiçbirisi değil ise sadece genişleticeğimiz text'e  harfi ekle.
		command++;
	}
	if(meta && expanded_text == NULL) //Eğer meta karakterden sonra geliyor ise yani 1 olarak yolladıysak direkt return et.
		return ;
	free(lex_table->content);
	lex_table->content = expanded_text; //Content'i genişlettiğimiz, anlam kazandırdığımız text ile eşitle..
}

static void	lexlist_value_expander(t_data *data)
{
	t_lexlist	*lex_table;

	lex_table = data->lex_table;
	while(lex_table)
	{
		if(lex_table->type == TEXT) //Eğer gelen content metin ise;
			text_expander(lex_table, 0, data); //Meta karakter flagi 0 olarak bu metine anlam kazandır.
		else if(lex_table->type != SIGN_PIPE &&  lex_table->next) //Eğer | değilse ve bir sonraki node var ise
			if(lex_table->type != SIGN_DOUBLE_LESS) //Eğer << değilse
				text_expander(lex_table, 1, data); //Yine aynı fonksiyonu çalıştır fakat meta karakter olduğu için 1 flagi ile yolla.
		lex_table = lex_table->next;
	}
}

void	expander(t_data *data)
{
	if(data->output == 2)
		return ;
	lexlist_value_expander(data); //Lexer ile doldurduğumuz lexlist'in içindeki contentlere parser bölümü için anlam kazandırır.
	clear_empty_lextables(data); //Eğer hiçbişeye anlam kazandıramadıysak, yani node içinde content'i boş olan var ise bu node'ları silmemizi sağlayan fonksiyon.
}
