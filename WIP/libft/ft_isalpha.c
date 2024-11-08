/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:10:55 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/03 16:30:42 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha( int character )
{
	if (!((character >= 'a' && character <= 'z')
			|| (character >= 'A' && character <= 'Z')))
		return (0);
	return (1);
}