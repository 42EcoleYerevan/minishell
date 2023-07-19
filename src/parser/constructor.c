/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:14:23 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:14:58 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist	*ft_constructor(t_shell *shell, char **tokens)
{
	t_mlist	*list;

	list = ft_create_list(shell, tokens);
	return (list);
}
