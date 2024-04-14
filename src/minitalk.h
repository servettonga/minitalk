/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehosaf <sehosaf@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:09:53 by sehosaf           #+#    #+#             */
/*   Updated: 2024/04/15 22:36:04 by sehosaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "../lib/ft_printf.h"

//			Colors
# define	RED "\033[0;31m"
# define	GREEN "\033[1;32m"
# define	YELLOW "\033[0;33m"
# define	BLUE "\033[1;34m"
# define	END "\033[0m"
# define	CYAN "\033[1;36m"

// 		Server
void	handle_signal(int sig, siginfo_t *info, void *ucontext);

// 		Client
void	send_message(pid_t pid, char msg);
void	confirm_signal(int sig);

// 		Utils
int		ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);

#endif
