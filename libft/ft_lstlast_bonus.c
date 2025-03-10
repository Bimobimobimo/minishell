/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 08:16:29 by amonfret          #+#    #+#             */
/*   Updated: 2024/10/23 14:28:22 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	if (lst)
	{
		ptr = lst;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
	}
	else
	{
		return (NULL);
	}
	return (ptr);
}
