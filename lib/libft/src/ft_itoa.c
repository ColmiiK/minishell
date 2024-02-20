/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:35:46 by alvega-g          #+#    #+#             */
/*   Updated: 2024/01/18 17:54:49 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	digit_count(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	fill_number(int j, int i, int n, char *s)
{
	while (j > i)
	{
		s[j - 1] = n % 10 + '0';
		n /= 10;
		j--;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = digit_count(n);
	s = (char *)malloc(sizeof(char) * j + 1);
	if (!s)
		return (0);
	if (n == -2147483648)
	{
		s[0] = '-';
		s[1] = '2';
		n = 147483648;
		i = 2;
	}
	if (n < 0)
	{
		s[0] = '-';
		i = 1;
		n = -n;
	}
	fill_number(j, i, n, s);
	s[j] = 0;
	return (s);
}
