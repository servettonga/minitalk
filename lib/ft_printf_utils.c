#include "ft_printf.h"

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size <= 0 || count <= 0)
	{
		size = 1;
		count = 1;
	}
	if (count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
