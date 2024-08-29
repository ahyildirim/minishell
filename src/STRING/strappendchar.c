#include "../../includes/minishell.h"

void str_append_char(char **dst, char c)
{
    size_t len = (*dst) ? strlen(*dst) : 0; // Mevcut uzunluğu al
    char *updated_str = malloc(len + 2); // 1 karakter ve 1 null terminatör için yer ayır
    if (!updated_str)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    // Mevcut karakterleri yeni belleğe kopyala
    if (*dst)
    {
        char *tmp_src = *dst;
        char *tmp_dst = updated_str;
        while (*tmp_src)
        {
            *tmp_dst++ = *tmp_src++;
        }
        free(*dst); // Eski belleği serbest bırak
    }

    // Yeni karakteri ve null terminatörü ekle
    updated_str[len] = c;
    updated_str[len + 1] = '\0';

    *dst = updated_str; // Yeni belleği `*dst` işaretçisine ata
}

