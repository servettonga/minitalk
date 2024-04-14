/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehosaf <sehosaf@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:38:04 by sehosaf           #+#    #+#             */
/*   Updated: 2024/04/13 23:23:33 by sehosaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	__ptr_len(uintptr_t num)
{
	size_t	digits;

	digits = 0;
	while (num)
	{
		num /= 16;
		digits++;
	}
	return (digits);
}
static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_printf_p(void *ptr, size_t *count)
{
	uintptr_t	addr;
	char		*buffer;
	size_t		len;

	addr = (uintptr_t)ptr;
	if (!addr)
		return (ft_printf_s("(nil)", count));
	len = __ptr_len(addr);
	buffer = ft_calloc(len + 3, sizeof(char));
	buffer[len + 2] = '\0';
	while (addr > 0)
	{
		buffer[--len + 2] = "0123456789abcdef"[addr % 16];
		addr /= 16;
	}
	buffer[1] = 'x';
	buffer[0] = '0';
	ft_printf_s(buffer, count);
	free(buffer);
}

void	ft_printf_c(unsigned char c, size_t *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_printf_s(const char *str, size_t *count)
{
	int	len;

	if (str == NULL)
		return (ft_printf_s("(null)", count));
	len = ft_strlen(str);
	write(1, str, len);
	*count += len;
}
