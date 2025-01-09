/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehosaf <sehosaf@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:37:12 by sehosaf           #+#    #+#             */
/*   Updated: 2025/01/09 12:21:47 by sehosaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

int		ft_printf(const char *format, ...);

// 		Specifiers
void	ft_printf_c(unsigned char c, size_t *count);
void	ft_printf_s(const char *str, size_t *count);
void	ft_printf_i(int n, size_t *count);
void	ft_printf_p(void *ptr, size_t *count);
void	ft_printf_u(unsigned int n, size_t *count);
void	ft_printf_x(unsigned int n, bool upper, size_t *count);

// 		Utils
void	*ft_calloc(size_t count, size_t size);

#endif
