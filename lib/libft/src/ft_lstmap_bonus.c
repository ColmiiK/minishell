/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:24:43 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/18 17:55:13 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*aux;
	t_list	*node;
	t_list	*actual;

	if (!lst || !f || !del)
		return (0);
	aux = 0;
	actual = lst;
	while (actual)
	{
		node = ft_lstnew(f(actual->content));
		if (!node)
		{
			ft_lstclear(&aux, del);
			return (0);
		}
		ft_lstadd_back(&aux, node);
		actual = actual->next;
	}
	return (aux);
}
