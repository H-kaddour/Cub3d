/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:34:02 by hkaddour          #+#    #+#             */
/*   Updated: 2021/12/03 18:22:07 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*s1;

	i = 0;
	s1 = (char *)s;
	while (n > i)
	{
		s1[i] = 0;
		i++;
	}
}
