/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:56:53 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/08 17:03:26 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

size_t	iput_c(va_list ap);
size_t	putvar(const char format_i, const char *cur_arg, va_list ap);
size_t	iput_s(const char *s, va_list ap);
size_t	iputchar(char c);
size_t iput_p(va_list ap);
size_t iputstr(char *str);
size_t iput_d( va_list ap);
int rec_iput_d(int i);
int rec_iput_p(unsigned long int adr, char *bhex, int len);

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
			len = len + putvar(format[++i], cur_arg, ap);
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

size_t	putvar(const char format_i, const char *cur_arg, va_list ap)
{
	if (!format_i)
		return(-1);
	if (format_i == 's')
		return (iput_s(cur_arg, ap));
	if (format_i == 'c')
		return(iput_c(ap));
	if (format_i == 'p')
		return(iput_p(ap));
	if (format_i == '%')
		return(iputchar('%'));
	if (format_i == 'd')
		return(iput_d(ap));
	return (0);
}

size_t	iput_s(const char *s, va_list ap)
{
	int	i;

	if (!s)
		return (0);
	s = va_arg(ap, char*);
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
	i = (va_arg(ap, long int));
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
size_t iput_p(va_list ap)
{
	char *bhex;
	unsigned long int adr;
	int len;

	len = write(1, "0x", 2);
	bhex = "0123456789abcdef";
	adr = (va_arg(ap, unsigned long int));
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
	char *format = "123\n%%s1:\n%s\n%%s2:\n%s\nchar c:\n%c\nvoid p:\n%p\ndecimal d:\n%d\nreturn value:";
	char *s1 = "string1";
	char *s2 = "STRING2";
	char c = 'X';
	long int d = -10480;
	void *p = &d;

	printf("\n**ft_printf**\n");
	printf("\n%d\n", ft_printf(format, s1, s2, c, p, d));
	printf("\n**printf**\n");
	printf("\n%d\n", printf(format, s1, s2, c, p, d));
	//printf("fsde%hdfg");
	return 0;
}
