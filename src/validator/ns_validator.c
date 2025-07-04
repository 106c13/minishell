/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ns_validator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:52:12 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/23 17:51:54 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

bool	ns_validate_op(char *input);

bool	ns_validate_redirects(char *input);

bool	ns_validate_quotes(char *input);

bool	ns_validate_brackets(char *input);

bool	ns_validate_not_required_chars(char *input);

bool	ns_validate_cmd_subst(char *input);

bool	ns_validate_parens_and_context(char *input);

bool	ns_validate(char *input)
{
	if (!ns_validate_quotes(input))
		return (printerr1("syntax error: invalid quotes"), false);
	if (!ns_validate_brackets(input))
		return (printerr1("syntax error: invalid brackets"), false);
	if (!ns_validate_not_required_chars(input))
		return (printerr1("syntax error: unsupported characters"), false);
	if (!ns_validate_op(input))
		return (printerr1("syntax error "
				"near unexpected token ('&&', '||', '|')"), false);
	if (!ns_validate_redirects(input))
		return (printerr1("syntax error "
				"near unexpected token ('>', '<', '>>', '<<')"), false);
	if (!ns_validate_cmd_subst(input))
		return (printerr1("syntax error: command substitution"), false);
	if (!ns_validate_parens_and_context(input))
		return (printerr1("syntax error: hard cases"), false);
	return (true);
}
