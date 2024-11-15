/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:56:53 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/15 13:45:56 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

size_t	iput_c(va_list ap);
size_t	putvar(const char format_i, va_list ap);
size_t	iput_s(va_list ap);
size_t	iputchar(char c);
size_t iput_p_x(va_list ap,const char format_i);
size_t iputstr(char *str);
size_t iput_d( va_list ap);
int rec_iput_d(int i);
int rec_iput_p(unsigned long int adr, char *bhex, int len);
size_t iput_u(va_list ap);

int	ft_printf(const char *format, ...)
{
	size_t		len;
	size_t		i;
	va_list		ap;
	const char	*cur_arg;

	i = 0;
	len = 0;
	if (!format)
		return (0);
	cur_arg = format;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
			len = len + iputchar(format[i]);
		else
			len = len + putvar(format[++i], ap);
		i++;
	}
	return (len);
}
size_t	iputchar(const char c)
{
	if (!c)
		return (0);
	return (write(1, &c, 1));
}

size_t	putvar(const char format_i, va_list ap)
{
	if (!format_i)
		return (-1);
	if (format_i == 's')
		return (iput_s(ap));
	if (format_i == 'c')
		return (iput_c(ap));
	if (format_i == 'p' || format_i == 'x' || format_i == 'X')
		return (iput_p_x(ap, format_i));
	if (format_i == '%')
		return (iputchar('%'));
	if (format_i == 'd' || format_i =='i')
		return (iput_d(ap));
	if (format_i == 'u')
		return (iput_u(ap));
	return (0);
}
size_t	iput_u(va_list ap)
{
	long int	u;
	char		tab[10];
	size_t		len;
	size_t		i;

	len = 9;
	i = 0;
	u = (va_arg(ap, unsigned int));
	if (u == 0)
		return (write(1, "0", 1));
	while (u != 0)
	{
		tab[len] = (u % 10) + '0';
		u = u / 10;
		len --;
	}
	while (++len <= 9)
		i = i + write(1, &tab[len], 1);
	return (i);
}

size_t	iput_s(va_list ap)
{
	int	i;
	char * s;

	s = va_arg(ap, char*);
	if (!s)
		return (write(1, "(null)", 6 ));
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}
size_t iput_d( va_list ap)
{
	long int i;
	int len;

	len = 0;
	i = (va_arg(ap, int));
	if(i == 0)
		return (write(1, "0", 1));
	if (i < 0)
	{
		write(1,"-",1);
		len++;
		i = -i;
	}
	len = len + rec_iput_d(i);
	return(len);
}
int rec_iput_d(int i)
{
	char c;
	if (!i)
		return(0);
	c = i % 10 + '0';
	i = i / 10;
	return (rec_iput_d(i) + write (1, &c, 1));
}
size_t iput_p_x(va_list ap, char format_i)
{
	char *bhex;
	unsigned long int adr;
	int len;

	len = 0;
	if (format_i == 'X')
		bhex = "0123456789ABCDEF";
	else
		bhex = "0123456789abcdef";
	if (format_i == 'p')
	{
		adr = (va_arg(ap, unsigned long int));
			if(!adr)
				return (write(1, "(nil)", 5 ));
		len = write(1, "0x", 2);
	}
	else
		adr = (va_arg(ap, unsigned int));
	if (!adr)
		return (write(1, "0", 1));
	return (len + rec_iput_p(adr, bhex, len));
}
int rec_iput_p(unsigned long adr, char *bhex, int len)
{
	if(!adr)
		return (0);
	return (rec_iput_p(adr / 16, bhex, len) + write(1, &bhex[adr % 16], 1));
}
size_t iputstr(char *str)
{
	size_t i;

	if(!str)
		return (0);
	i = 0;
	while(str[i])
		{
			if(write(1, &str[i], 1))
			i++;
		}
	return(i);

}

size_t	iput_c(va_list ap)
{
	char c;

	c = (char)va_arg(ap, int);
	return ((write(1, &c, 1)));
}

int main()
{
	char *format = "123\n%%s1:\n%s\n%%s2:\n%s\nchar c:\n%c\nvoid p:\n%p\ndecimal d:\n%d\ninteger i:\n%i\nunsigned u;\n%u\nHexa x:\n%x\nHEXA X:\n%X\nreturn value:";
	char *s1 = "string1";
	char *s2 = NULL;
	char c = 'c';
	int d = -0x424242;
	unsigned int u = -2944548;

	void *p = s2;


	printf("\n**ft_printf**\n");
	printf("\n%d\n", ft_printf(format, s1, s2, c, p, d, d, u, u, u));
	printf("\n**printf**\n");
	printf("\n%d\n", printf(format, s1, s2, c, p, d, d, u, u, u));
	return 0;
}
