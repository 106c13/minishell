/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:02:03 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/19 21:59:52 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	validate(char *input)
{
	int		op_type;
	int		is_cmd_start;
	int		is_file;
	int		file_len;
	char	quote;
	return 0;
	op_type = 0;
	quote = 0;
	is_file = 0;
	is_cmd_start = 0;
	while (*input)
	{
		if (is_whitespace(*input))
		{
			input++;
			continue ;
		}
		op_type = get_operator_type(input); 
		if (op_type != 0)
		{
			if (is_cmd_start || is_file)
				return (printerr_one("Invalid input"), 1);
			if (op_type == AND || op_type == OR)
				input++;
			input ++;
			continue ;
		}
		else if (*input == '>' || *input == '<')
		{
			input++;
			if (*input == '>')
				input++;
			is_file = 1;
			file_len = 0;
			input = trim_spaces(input);
			file_len = count_in_file(input);
			if (file_len == 0)
				return (printerr_one("syntax error near unexpected token `newline'"), 1);
		}
		if (is_quote(*input))
		{
			is_cmd_start = 1;
			input += count_in_quotes(input) + 2;
		}
		if (get_operator_type(input) && !is_cmd_start)
			return (printerr_one("Invalid input"), 1);
		else
			input++;
	}
	if (quote || op_type)
		return (printerr_one("Invalid input"), 1);
	return (0);
}*/
#include "minishell.h"

int	validate(char *input)
{
	int		op_type;
	int		is_cmd_start;
	int		is_file;
	int		file_len;
	char	quote;
	int		expect_command;
	int		paren_count;
	
	op_type = 0;
	quote = 0;
	is_file = 0;
	is_cmd_start = 0;
	expect_command = 1; // We expect a command at the start
	paren_count = 0;
	
	while (*input)
	{
		if (is_whitespace(*input))
		{
			input++;
			continue ;
		}
		
		// Check for operators (&&, ||, |)
		op_type = get_operator_type(input);
		if (op_type != 0)
		{
			if (expect_command || is_file)
				return (printerr_one("Invalid input"), 1);
			
			if (op_type == AND || op_type == OR)
				input += 2; // Skip both characters of && or ||
			else if (op_type == PIPE)
				input++; // Skip single character |
			else
				input++; // Handle other single character operators
			
			expect_command = 1; // After any operator, we expect a command
			is_cmd_start = 0;
			is_file = 0;
			continue ;
		}
		
		// Check for parentheses
		if (*input == '(')
		{
			if (!expect_command && is_cmd_start)
				return (printerr_one("Invalid input"), 1);
			paren_count++;
			input++;
			expect_command = 1; // After opening paren, expect command
			is_cmd_start = 0;
			continue ;
		}
		
		if (*input == ')')
		{
			if (paren_count == 0)
				return (printerr_one("syntax error near unexpected token `)'"), 1);
			if (expect_command)
				return (printerr_one("Invalid input"), 1);
			paren_count--;
			input++;
			expect_command = 0; // After closing paren, we have a complete expression
			is_cmd_start = 1;
			continue ;
		}
		
		// Check for redirection operators
		if (*input == '>' || *input == '<')
		{
			if (expect_command || !is_cmd_start)
				return (printerr_one("syntax error near unexpected token"), 1);
			
			input++;
			if (*input == '>' && *(input-1) == '>')
				input++; // Handle >> (append)
			
			is_file = 1;
			file_len = 0;
			input = trim_spaces(input);
			file_len = count_in_file(input);
			
			if (file_len == 0)
				return (printerr_one("syntax error near unexpected token `newline'"), 1);
			
			// Skip the filename
			input += file_len;
			is_file = 0;
			continue ;
		}
		
		// Handle quoted strings
		if (is_quote(*input))
		{
			quote = *input;
			input++;
			
			// Find matching quote
			while (*input && *input != quote)
				input++;
			
			if (!*input) // Unclosed quote
				return (printerr_one("Invalid input: unclosed quote"), 1);
			
			input++; // Skip closing quote
			is_cmd_start = 1;
			expect_command = 0;
			continue ;
		}
		
		// Handle regular tokens (commands, arguments, filenames)
		if (!is_whitespace(*input) && !is_quote(*input) && 
		    *input != '>' && *input != '<' && *input != '(' && *input != ')' &&
		    get_operator_type(input) == 0)
		{
			// Skip to end of current token
			while (*input && !is_whitespace(*input) && 
			       !is_quote(*input) && *input != '>' && 
			       *input != '<' && *input != '(' && *input != ')' &&
			       get_operator_type(input) == 0)
				input++;
			
			is_cmd_start = 1;
			expect_command = 0;
			continue ;
		}
		
		// If we reach here, we have an unhandled character
		input++;
	}
	
	// Final validation
	if (expect_command)
		return (printerr_one("Invalid input: expected command"), 1);
	
	if (paren_count != 0)
		return (printerr_one("syntax error: unmatched parentheses"), 1);
	
	return (0);
}
