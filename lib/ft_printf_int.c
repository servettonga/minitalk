/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehosaf <sehosaf@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:38:13 by sehosaf           #+#    #+#             */
/*   Updated: 2024/04/13 23:23:44 by sehosaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_i(int n, size_t *count)
{
	long	num;
	char	*buffer;
	int		i;

	num = n;
	buffer = ft_calloc(12, sizeof(char));
	if (num < 0)
		num *= -1;
	i = 11;
	if (num == 0)
		buffer[--i] = '0';
	while (num > 0)
	{
		buffer[--i] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		buffer[--i] = '-';
	buffer[11] = '\0';
	ft_printf_s(buffer + i, count);
	free(buffer);
}

void	ft_printf_u(unsigned int n, size_t *count)
{
	char	*buffer;
	int		i;

	buffer = ft_calloc(20, sizeof(char));
	i = 19;
	if (n == 0)
		buffer[--i] = '0';
	while (n > 0)
	{
		buffer[--i] = (n % 10) + '0';
		n /= 10;
	}
	buffer[19] = '\0';
	ft_printf_s(buffer + i, count);
	free(buffer);
}

void	ft_printf_x(unsigned int n, bool upper, size_t *count)
{
	const char	*hex;
	char		buffer[16];
	int			i;

	hex = "0123456789abcdef";
	if (upper)
		hex = "0123456789ABCDEF";
	i = 14;
	while (n >= 16)
	{
		buffer[i--] = hex[n % 16];
		n /= 16;
	}
	buffer[i--] = hex[n];
	buffer[i] = '\0';
	buffer[15] = '\0';
	ft_printf_s(buffer + i + 1, count);
}
