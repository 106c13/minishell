/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2025/06/16 17:02:03 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/19 23:09:29 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

static int is_empty(char *str)
{
    if (!str)
        return 1;
    while (*str)
    {
        if (!isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

int check_quotes(const char *str)
{
    char quote = 0;

    while (*str)
    {
        if (*str == '\'' || *str == '"')
        {
            if (!quote)
                quote = *str;
            else if (quote == *str)
                quote = 0;
        }
        str++;
    }
    return (quote == 0); // 1 = ок, 0 = ошибка
}
int check_brackets(const char *str)
{
    int depth = 0;
    int i = 0;

    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            char quote = str[i++];
            while (str[i] && str[i] != quote)
                i++;
            if (!str[i])
                return 0;
        }
        else if (str[i] == '(')
        {
            depth++;
            int j = i + 1;
            int has_content = 0;

            while (str[j] && str[j] != ')')
            {
                if (!isspace((unsigned char)str[j]) && str[j] != '(')
                    has_content = 1;

                if (str[j] == '\'' || str[j] == '"')
                {
                    char q = str[j++];
                    while (str[j] && str[j] != q)
                        j++;
                    if (!str[j])
                        return 0;
                }
                j++;
            }

            if (!str[j])
                return 0; // нет закрывающей скобки
            if (!has_content)
                return 0; // пустые скобки

            i = j; // перескакиваем на ')'
        }
        else if (str[i] == ')')
        {
            if (depth == 0)
                return 0; // лишняя закрывающая
            depth--;
        }
        i++;
    }

    return (depth == 0);
}



int check_syntax(const char *str)
{
    int i = 0;

    while (str[i])
    {
        // Пропускаем кавычки
        if (str[i] == '\'' || str[i] == '"')
        {
            char quote = str[i++];
            while (str[i] && str[i] != quote)
                i++;
        }
        // Логические операторы: &&, ||
        else if ((str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i + 1] == '|'))
        {
            i += 2;

            // Пропускаем пробелы
            while (str[i] && isspace((unsigned char)str[i]))
                i++;

            // Если сразу закрывающая скобка, конец строки или другой оператор — ошибка
            if (!str[i] || str[i] == ')' || str[i] == '|' || str[i] == '&')
                return 0;
        }
        else if (str[i] == '|')
        {
            // Одинарный пайп: та же логика
            int j = i + 1;
            while (str[j] && isspace((unsigned char)str[j])) j++;
            if (!str[j] || str[j] == '|' || str[j] == '&' || str[j] == ')')
                return 0;
        }
        i++;
    }
    return 1;
}
int check_invalid_chars(const char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            char quote = str[i++];
            while (str[i] && str[i] != quote)
                i++;
        }
        else if (str[i] == ';' || (str[i] == '&' && str[i + 1] != '&'))
        {
            // одиночные ; или & — ошибка
            return 0;
        }
        i++;
    }
    return 1;
}


int validate(char *input)
{
	if (is_empty(input))
	{
		printerr_one("syntax error: empty input");
		return (1);
	}
	if (!check_invalid_chars(input))
    {
        printerr_one("syntax error: invalid character ';' or '&'");
        return 1;
    }
	if (!check_quotes(input))
	{
		printerr_one("syntax error: unclosed quote");
		return (1);
	}
	if (!check_brackets(input))
	{
		printerr_one("syntax error: invalid_brackets");
		return (1);
	}
	if (!check_syntax(input))
	{
		printerr_one("syntax error: near unexpected token");
		return (1);
	}
	return (0);
}
