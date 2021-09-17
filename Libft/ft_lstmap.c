/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 09:52:04 by abrun             #+#    #+#             */
/*   Updated: 2020/12/04 18:33:54 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*newlst;
	t_list		*tmp;

	newlst = malloc(sizeof(t_list));
	if (!newlst)
		return (0);
	(void)(del);
	if (lst)
	{
		newlst = ft_lstnew((f)(lst->content));
		if (!newlst)
			return (0);
		lst = lst->next;
	}
	while (lst)
	{
		tmp = ft_lstnew((f)(lst->content));
		if (!tmp)
			return (0);
		lst = lst->next;
		ft_lstadd_back(&newlst, tmp);
	}
	return (newlst);
}
