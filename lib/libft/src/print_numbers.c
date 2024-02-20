/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:26:00 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/14 11:34:40 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	digit_count(int n)
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

int	print_integer(int nb)
{
	ft_putnbr_fd(nb, 1);
	if (nb == -2147483648)
		return (11);
	return (digit_count(nb));
}

static int	unsigned_digit_count(unsigned int n)
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

static void	unsigned_ft_putnbr_fd(unsigned int n, int fd)
{
	if (n < 10)
	{
		ft_putchar_fd(n + 48, fd);
		return ;
	}
	else
		ft_putnbr_fd(n / 10, fd);
	ft_putnbr_fd(n % 10, fd);
}

int	print_unsigned(unsigned int nb)
{
	unsigned_ft_putnbr_fd(nb, 1);
	return (unsigned_digit_count(nb));
}
