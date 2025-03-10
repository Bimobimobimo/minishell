/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:27:26 by amonfret          #+#    #+#             */
/*   Updated: 2024/10/23 14:28:25 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (lst && *lst)
	{
		current = *lst;
		while (current != NULL)
		{
			next = current->next;
			if (del)
				del(current->content);
			free(current);
			current = next;
		}
		*lst = NULL;
	}
}
