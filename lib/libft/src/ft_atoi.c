/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frangome <frangome@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:49:05 by frangome          #+#    #+#             */
/*   Updated: 2023/04/25 20:27:40 by frangome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	c;
	int	num;
	int	sign;

	sign = 1;
	c = 0;
	num = 0;
	while (str[c] == ' ' || str[c] == '\n' || str[c] == '\t'
		|| str[c] == '\r' || str[c] == '\v' || str[c] == '\f')
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			sign = -1;
		c++;
	}
	while ((str[c] >= '0' && str[c] <= '9'))
	{
		num = num * 10 + (str[c] - '0');
		c++;
	}
	return (sign * num);
}
