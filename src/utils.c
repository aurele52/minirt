#include "../include/rt.h"

int	min(int nb1, int nb2)
{
	if (nb1 > nb2)
		return (nb2);
	return (nb1);
}

int	max(int nb1, int nb2)
{
	if (nb1 < nb2)
		return (nb2);
	return (nb1);
}

static void	ouijesais(char c, int fd)
{
	write(fd, &c, 1);
}

void	putnbrfd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	if (n > 9)
	{
		putnbrfd(n / 10, fd);
		n = n % 10;
	}
	ouijesais(n + '0', fd);
}

int	ft_abs(int a)
{
	if (a < 0)
		a = -a;
	return (a);
}

void	lstdelone(t_list *list, int garbage)
{
	if (garbage != 0)
		free(list->content);
	list->pos->size = list->pos->size - 1;
	if (list->pos->start->back == list->pos->start)
		list->pos->start = 0;
	else
	{
		if (list->pos->start == list)
			list->pos->start = list->next;
		list->back->next = list->next;
		list->next->back = list->back;
	}
	if (garbage != 0)
		free(list);
}

t_pos	*setpos(t_pos *garbage)
{
	t_pos	*pos;
	int		size;

	if (size == 0)
		return (0);
	pos = ft_malloc(sizeof(*pos), garbage);
	if (pos == 0)
	{
		return (0);
	}
	pos->size = 0;
	pos->start = 0;
	return (pos);
}

static int	wcount(char const *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
			wcount++;
		i++;
	}
	return (wcount);
}

static int	wlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != 0)
		i++;
	return (i);
}

char	**split(char const *s, char c, t_pos *free)
{
	int		a;
	char	**str;

	a = 0;
	if (s == 0)
		return (0);
	str = ft_malloc(sizeof(char *) * (wcount(s, c) + 1), free);
	if (!str)
		return (0);
	str[wcount(s, c)] = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			str[a] = substr(s, 0, (wlen(s, c)), free);
			if (!str[a])
				return (0);
			a++;
		}
		s = s + wlen(s, c);
	}
	return (str);
}


char	*ft_strdup(const char *s, t_pos *garbage)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_malloc((sizeof(char) * strlen((char *)s) + 1), garbage);
	if (!(str))
		return (0);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}


char	*strjoin(char *s1, char *s2, t_pos *garb)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	str = ft_malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1), garb);
	if (!(str))
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	*substr(char const *s, int start, int len, t_pos *garb)
{
	char	*str;

	if (start > strlen(s) || len <= 0)
		return (ft_strdup("", garb));
	while (start + len > strlen(s))
		len--;
	str = ft_malloc(sizeof(char) * (len + 1), garb);
	if (!(str))
		return (0);
	s = start + s;
	str[len] = 0;
	while (len > 0)
	{
		str[len - 1] = s[len - 1];
		len--;
	}
	return (str);
}

char	*itoagnl(int n, char *str, char *str2)
{
	int	nb;
	int	i;

	if (n == 0)
	{
		str[0] = '0';
		return (str2);
	}
	i = 0;
	nb = n;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	str[i--] = 0;
	while (n > 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (str2);
}

char	*ft_return(char *str, char *buffer)
{	
	buffer[0] = -1;
	if (str[0] == 0)
		return (0);
	return (str);
}

void	ft_read(char *buffer, int fd)
{
	int	ret;

	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret == BUFFER_SIZE)
		buffer[BUFFER_SIZE] = -1;
	if (ret < BUFFER_SIZE)
		buffer[ret] = 0;
}

int	strlengnl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != -1)
		i++;
	return (i);
}

int	atoignl(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str[0] == '0')
		return (0);
	while (str[i] <= '9' && str[i] >= '0' && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

char	*gnl2(char *str, char *buffer, int fd, t_pos *free)
{
	int	mem;
	int	i;

	i = 0;
	while (1)
	{
		i = atoignl(buffer) + 1;
		if (buffer[0] == 0 || buffer[i] == 0)
		{
			i = 0;
			ft_read(buffer, fd);
		}
		mem = i;
		while (buffer[i] != '}' && buffer[i] != 0 && buffer[i] != -1)
			i++;
		str = strjoin(str, substr(&buffer[mem],
					0, i - mem + 1, free), free);
		if (buffer[i] == '}')
			return (itoagnl(i, buffer, str));
		if (buffer[i] == 0)
			return (ft_return(str, buffer));
		if (buffer[i] == -1)
			buffer[0] = 0;
	}
	return (0);
}

char	*get_next_line(int fd, t_pos *free)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;

	if (fd < 0 || fd > 2000 || buffer[0] == -1 || BUFFER_SIZE <= 0) {
		close(fd);
		buffer[0] = 0;
		return (0);
	}
	str = ft_malloc(sizeof(char), free);
	str[0] = 0;
	return (gnl2(str, buffer, fd, free));
}
void	posclear(t_pos *pos, int freee)
{
	if (pos != NULL)
	{
		while (pos->size != 0)
			lstdelone(pos->start, freee);
		if (freee == 2)
		{
			free(pos);
		}
	}
}

void	ft_exit(t_rt *rt, char *str)
{
	if (str)
		write(2, str, strlen(str));
	if (rt->scene.garbage.size != 0)
		posclear(&rt->scene.garbage, 1);
	if (rt->garbage.size != 0)
		posclear(&rt->garbage, 1);
	exit(0);
}

t_list	*lstnew(void *content, t_pos *pos, t_pos *garbage)
{
	t_list	*liste;

	liste = ft_malloc(sizeof(*liste), garbage);
	if (liste == 0)
		return (0);
	liste->content = content;
	liste->pos = pos;
	liste->pos->size = liste->pos->size + 1;
	if (pos->start == 0)
	{
		liste->next = liste;
		liste->back = liste;
		pos->start = liste;
	}
	else
	{
		liste->back = pos->start->back;
		liste->next = pos->start;
		if (pos->size == 1)
			pos->start->next = liste;
		else
			pos->start->back->next = liste;
		pos->start->back = liste;
	}
	return (liste);
}

void	*ft_malloc(int size, t_pos *garbage)
{
	void	*new;

	new = malloc(size);
	if (new == 0)
		return (0);
	if (garbage != 0)
	{
		lstnew(new, garbage, 0);
		if (garbage->start->back == 0)
		{
			free(new);
			return (0);
		}
	}
	return (new);
}


t_coord	makecoord(t_rt *rt, double x, double y)
{
	static t_coord	coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}
