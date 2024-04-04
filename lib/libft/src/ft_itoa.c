/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:36:36 by frangome          #+#    #+#             */
/*   Updated: 2023/04/25 20:32:08 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_size(int n)
{
	int	c;

	if (n == 0)
		return (1);
	c = 0;
	while (n > 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

char	*fill_str(char *str, int n, int neg, int min)
{
	int	size;
	int	c;

	size = get_size(n);
	if (neg)
		size = get_size(n) + 1;
	str[size] = 0;
	c = 0;
	while (c < size)
	{
		if (min && c == 0)
			str[size - c - 1] = (n % 10) + 49;
		else
			str[size - c - 1] = (n % 10) + 48;
		n /= 10;
		c++;
	}
	if (neg)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		neg;
	int		min;

	neg = 0;
	min = 0;
	if (n == -2147483648)
	{
		n++;
		min = 1;
	}
	size = get_size(n);
	if (n < 0)
	{
		n *= -1;
		size = get_size(n) + 1;
		neg = 1;
	}
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (0);
	str = fill_str(str, n, neg, min);
	return (str);
}
