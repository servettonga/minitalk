/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehosaf <sehosaf@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:37:52 by sehosaf           #+#    #+#             */
/*   Updated: 2024/04/13 23:18:23 by sehosaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		The ft_printf() function formats and prints a series of characters and
		values to the standard output stream stdout. Format specifications,
		beginning with a percent sign (%), determine the output format for any
		argument-list following the format-string. The format-string is a
		multibyte character string beginning and ending in its initial shift
		state.

	PARAMETERS
		C string that contains the text to be written to stdout.
		It can optionally contain embedded format specifiers that are replaced
		by the values specified in subsequent additional arguments and formatted
		as requested.

		A format specifier follows this prototype: [see compatibility note below]
		%[flags][width][.precision][length]specifier

		specifier	Output
		c			Character
		s			String of characters
		p			Pointer address
		d or i		Signed decimal integer
		u			Unsigned decimal integer
		x			Unsigned hexadecimal integer
		X			Unsigned hexadecimal integer (uppercase)
		%			A % followed by another % character will write a single
					% to the stream.

	RETURN VALUE
		Upon successful return, this function returns the number of characters
		printed (excluding the null byte used to end output to strings).
*/

#include "ft_printf.h"

static void	__printf_specifier(const char *format, va_list args, size_t *count)
{
	if (*format == 'c')
		ft_printf_c(va_arg(args, int), count);
	else if (*format == 's')
		ft_printf_s(va_arg(args, const char *), count);
	else if (*format == 'p')
		ft_printf_p(va_arg(args, void *), count);
	else if (*format == 'd' || *format == 'i')
		ft_printf_i(va_arg(args, int), count);
	else if (*format == 'u')
		ft_printf_u(va_arg(args, int), count);
	else if (*format == 'x' || *format == 'X')
		ft_printf_x(va_arg(args, unsigned int), *format == 'X', count);
	else if (*format == '%')
		ft_printf_c('%', count);
}

static bool	__is_specifier(char format)
{
	const char	*g_specifiers = "cspdiuxX%";

	while (*g_specifiers)
		if (*g_specifiers++ == format)
			return (true);
	return (false);
}

static int	ft_printf_arg(const char *format, va_list args)
{
	size_t	count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (__is_specifier(*format))
				__printf_specifier(format, args, &count);
		}
		else
			ft_printf_c(*format, &count);
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	count;

	if (!format || *format == '\0')
		return (0);
	va_start(args, format);
	count = ft_printf_arg(format, args);
	va_end(args);
	return (count);
}
