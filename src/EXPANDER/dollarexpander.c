#include "../../includes/minishell.h"

static void	handle_dollar_value(char **dst, char **src, t_data *data)
{
	int		len;
	char	*str;

	len = 0;
	str = (*src) + 1; //İşaretçiyi dolardan bir sonraki karaktere taşı.
	while(*str != ' ' && *str && *str != *SINGLE_QUOTE && *str != *DOUBLE_QUOTE && *str != '$') //Metin bitene kadar boyutunu ölç.
	{
		len++;
		str++;
	}
	str = ft_strlcpy(NULL, (*src) + 1, len); //Üstte boyutunu ölçtüğümüz text'i str'a kopyala.
	env_expander(dst, str, data); //Aldığımız variable ismini environment table'ın içine doldur.
	free(str);
	*src += len;
}

static void	handle_single_dollar(char **dst)
{
	str_append_char(dst, *DOLLAR);
}

static void	handle_question_mark(char **dst, char **src, t_data *data)
{
	char	*ret;

	ret = ft_itoa(data->last_output);
	ft_strjoin(dst, ret);
	free(ret);	
	(*src)++;
}

static void	handle_double_dollar(char **dst, char **src, t_data *data)
{
	char	*ret;
	
	ret = ft_itoa(data->main_pid);
	ft_strjoin(dst, ret);
	free(ret);
	(*src)++;
}

void	dollar_expander(char **dst, char **src, t_data *data)
{
	char	*str;

	str = (*src) + 1; //İşaretçimizi dolar işaretinden hemen sonraki karaktere ayarlıyoruz ki ne olduğuna bakalım.
	if(*str == *DOLLAR)
		handle_double_dollar(dst, src, data); //Eğer yine dolar var ise bu komut bizim shellimizin process id'sini yazar. (Shell'i açıp $$ yaz ve çıktıyı gör).
	else if(*str == *QUSTION_MARK)
		handle_question_mark(dst, src, data); //Eğer soru işareti var ise bu komut shell ile son çalıştırılan programın return değerini döndürür. (Shell'de return 10 verdiğin bir main yaz ve çalıştır sonra $? komutunu gir, 10 çıktısını alıcaksın.)
	else if(*str == ' ' || *str == '\0' || *str == *DOUBLE_QUOTE || *str == *SINGLE_QUOTE)
		handle_single_dollar(dst); //Eğer sadece tek bir dolar var ise sadece genişleticeğimiz texte $ işaretini ekle.
	else
		handle_dollar_value(dst, src, data); //Eğer text var ise bu bir variable ismidir ve o isimi işlememiz gerekir.
}
