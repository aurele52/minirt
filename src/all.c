#include "../include/rt.h"
char	*itoagnl(int n, char *str, char *str2);
int	strlengnl(char *str);
int	atoignl(const char *str);
t_pos		*setpos(t_pos *garbage);
void		lstdelone(t_list *lst, int garbage);
t_list		*lstnew(void *content, t_pos *pos, t_pos *garbage);
void		posclear(t_pos *pos, int garbage);
void		posprint(t_rt *rt, t_pos *pos, void (*fct)(t_rt *, void *, int), int fd);

/*cast*/

t_lycee	*listToLycee(t_list *liste);
// t_seg	*seg(t_list *liste);
// t_voxel	*voxel(t_list *liste);
int		type(t_list *liste);

/*droite*/

void	printsamey(t_rt *rt, t_coord one, t_coord two, t_color color);
void	printdiagonefour(t_rt *rt, t_coord one, t_coord two, t_color color);
void	printdiagtwothree(t_rt *rt, t_coord one, t_coord two, t_color color);
void	printdiag(t_rt *rt, t_coord one, t_coord two, t_color color);
void	printsamex(t_rt *rt, t_coord one, t_coord two, t_color color);
void	printdroite(t_rt *rt, t_coord one, t_coord two, t_color color);
void	bresenhamoneeight(t_rt *rt, t_coord one, t_coord two, t_color color);

/*utils*/

void	swapcoord(t_coord *a, t_coord *b);
void	swap(double *a, double *b);
void	printpixelimg(t_rt *rt, t_coord print, t_color color);
t_coord	makecoord(t_rt *rt, double x, double y);

/*Sphere*/

void	printLycee(t_rt *rt, t_lycee *sp);

/*libft*/

char		*get_next_line(int fd, t_pos *free);
int			ft_abs(int nbr);
void		ft_exit(t_rt *rt, char *str);
char		*strjoin(char *s1, char *s2, t_pos *garbage);
void		putnbrfd(int n, int fd);
char		*ft_strdup(const char *s, t_pos *garbage);
char		*substr(char const *s, int start, int len, t_pos *garb);
void		*ft_malloc(int size, t_pos *garbage);
char		**split(char const *s, char c, t_pos *garbage);
char		*itoa(int n, t_pos *garbage);
int			atoi(const char *str);
int			doublstrlen(char **str);
int			max(int nb1, int nb2);
int			min(int nb1, int nb2);


t_square	*square(t_list *liste)
{
	t_obj	*obj;
	t_square	*square;

	obj = (t_obj *)liste->content;
	square = (t_square *)obj->obj;
	return (square);
}

t_lycee	*listToLycee(t_list *liste)
{
	t_obj	*obj;
	t_lycee *lycee;

	obj = (t_obj *)liste->content;
	lycee = (t_lycee *)obj->obj;
	return (lycee);
}

int	type(t_list *liste)
{
	t_obj	*obj;

	obj = liste->content;
	return (obj->type);
}

void	ft_exit(t_rt *rt, char *str)
{
	if (str)
		write(2, str, strlen(str));
	posclear(&rt->scene.garbage, 0);
	posclear(&rt->garbage, 0);
	exit(0);
}


static char	*remp(char *str, int n, int i)
{
	str[i + 1] = 0;
	while (n > 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (str);
}

static char	*zero(int i, t_pos *garbage)
{
	char	*str;

	str = ft_malloc(sizeof(char) * 2, garbage);
	str[0] = '0';
	str[1] = 0;
	return (str);
}

static char	*crea(int n, int i, int moin, t_pos *garbage)
{
	char	*str;

	if (n == 0)
		return (zero(1, garbage));
	str = ft_malloc(sizeof(char) * (i + moin + 1), garbage);
	if (!(str))
		return (0);
	if (moin == 1)
		str[0] = '-';
	return (remp(str, n, i + moin - 1));
}

static char	*retintmin(int i, t_pos *garbage)
{
	char	*str;

	(void)i;
	str = ft_malloc(sizeof(char) * 12, garbage);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = 0;
	return (str);
}

char	*itoa(int n, t_pos *garbage)
{
	int	nb;
	int	i;
	int	moin;

	i = 0;
	moin = 0;
	if (n == -2147483648)
		return (retintmin(1, garbage));
	if (n < 0)
	{
		n = -n;
		moin = 1;
	}
	nb = n;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (crea(n, i, moin, garbage));
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
int	ft_abs(int a)
{
	if (a < 0)
		a = -a;
	return (a);
}

int	atoi(const char *str)
{
	int	i;
	int	moin;
	int	res;

	i = 0;
	res = 0;
	moin = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			moin = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0' && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * moin);
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

int	max(int nb1, int nb2)
{
	if (nb1 < nb2)
		return (nb2);
	return (nb1);
}

int	min(int nb1, int nb2)
{
	if (nb1 > nb2)
		return (nb2);
	return (nb1);
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

void	swapcoord(t_coord *a, t_coord *b)
{
	t_coord	mem;

	mem = *a;
	*a = *b;
	*b = mem;
}

void	swap(double *a, double *b)
{
	int	mem;

	mem = *a;
	*a = *b;
	*b = mem;
}

void	bresenhamoneeight(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	int	e;
	int	dy;
	int	dx;

	dx = two.x - one.x;
	dy = two.y - one.y;
	e = dy;
	dy = e * 2;
	dx = dx * 2;
	while (1)
	{
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
		one.y++;
		if (one.y == two.y)
			break ;
		e = e - dx;
		if (e < 0)
		{
			one.x++;
			e = e + dy;
		}
	}
}
void	bresenhamthreesix(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	int	e;
	int	dy;
	int	dx;

	dx = two.x - one.x;
	dy = two.y - one.y;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (1)
	{
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
		one.x++;
		if (one.x == two.x)
			break ;
		e = e + dy;
		if (e < 0)
		{
			one.y--;
			e = e + dx;
		}
	}
}

void	bresenhamfourfive(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	int	e;
	int	dy;
	int	dx;

	dx = two.x - one.x;
	dy = two.y - one.y;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (1)
	{
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
		one.x++;
		if (one.x == two.x)
			break ;
		e = e - dy;
		if (e < 0)
		{
			one.y++;
			e = e + dx;
		}
	}
}

void	bresenhamtwoseven(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	int	e;
	int	dy;
	int	dx;

	dx = two.x - one.x;
	dy = two.y - one.y;
	e = dy;
	dy = e * 2;
	dx = dx * 2;
	while (1)
	{
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
		one.y--;
		if (one.y == two.y)
			break ;
		e = e + dx;
		if (e > 0)
		{
			one.x++;
			e = e + dy;
		}
	}
}

void	bresenham(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	int	dx;
	int	dy;

	if (two.x - one.x < 0)
		swapcoord(&one, &two);
	dx = two.x - one.x;
	dy = two.y - one.y;
	if (dy != 0)
	{
		if (dy > 0)
		{
			if (dx >= dy)
				bresenhamfourfive(rt, one, two, color);
			else
				bresenhamoneeight(rt, one, two, color);
		}
		else
		{
			if (dx >= -dy)
				bresenhamthreesix(rt, one, two, color);
			else
				bresenhamtwoseven(rt, one, two, color);
		}
	}
	printpixelimg(rt, makecoord(rt, two.x, two.y), color);
}

void	printdroite(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	if (one.x == two .x)
		printsamex(rt, one, two, color);
	else if (one.y == two.y)
		printsamey(rt, one, two, color);
	else if (ft_abs(one.x - two.x) == ft_abs(one.y - two.y))
		printdiag(rt, one, two, color);
	else
		bresenham(rt, one, two, color);
}

void	swapy(t_coord *one, t_coord *two)
{
	float	mem;

	mem = one->y;
	one->y = two->y;
	two->y = mem;
}

void	swapx(t_coord *one, t_coord *two)
{
	float	mem;

	mem = one->x;
	one->x = two->x;
	two->x = mem;
}

void	printsamey(t_rt *rt, t_coord one, t_coord two, t_color color)
{	
	if (two.x > one.x)
		swapx(&one, &two);
	while (one.x >= two.x)
	{
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
		one.x--;
	}
}

void	printdiagonefour(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	while (one.x != two.x)
	{
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
		one.x++;
		one.y++;
	}
	printpixelimg(rt, makecoord(rt, one.x, one.y), color);
}

void	printdiagtwothree(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	while (one.x != two.x)
	{
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
		one.x++;
		one.y--;
	}
	printpixelimg(rt, makecoord(rt, one.x, one.y), color);
}

void	printdiag(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	if (one.x - two.x == one.y - two.y)
	{
		if (two.x < one.x && two.y < one.y)
			swapcoord(&one, &two);
		printdiagonefour(rt, one, two, color);
	}
	else
	{
		if (one.x > two.x)
			swapcoord(&one, &two);
		printdiagtwothree(rt, one, two, color);
	}
}

void	printsamex(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	if (one.x == two.x)
	{
		if (two.y > one.y)
			swapy(&one, &two);
		while (one.y >= two.y)
		{
			printpixelimg(rt, makecoord(rt, one.x, one.y), color);
			one.y--;
		}
	}
}

void drawCircle(t_rt *rt, double x0, double y0, double radius, t_color color) {
	if (TEST == 1) {
		x0 = (((x0 + 5.14) / (9.56 + 5.14)) * 800) + 100;
		y0 = ((1 - ((y0 - 41.32) / (51.09 - 41.32))) * 800) + 100;
	}
	if (TEST == 3) {
		x0 = (((x0 - 1.3) / (3.7 - 1.3)) * 800) + 100;
		radius = radius * 400;
		y0 = ((1 - ((y0 - 47.9) / (49.3 - 47.9))) * 800) + 100;
	}
	int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x;

    while (y <= x) {
        printpixelimg(rt, makecoord(rt, x + x0, y + y0), color);  // Octant 1
        printpixelimg(rt, makecoord(rt, y + x0, x + y0), color);  // Octant 2
        printpixelimg(rt, makecoord(rt, -x + x0, y + y0), color); // Octant 4
        printpixelimg(rt, makecoord(rt, -y + x0, x + y0), color); // Octant 3
        printpixelimg(rt, makecoord(rt, -x + x0, -y + y0), color); // Octant 5
        printpixelimg(rt, makecoord(rt, -y + x0, -x + y0), color); // Octant 6
        printpixelimg(rt, makecoord(rt, x + x0, -y + y0), color);  // Octant 7
        printpixelimg(rt, makecoord(rt, y + x0, -x + y0), color);  // Octant 8
        y++;

        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;
        } else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}

void	printLycee(t_rt *rt, t_lycee *sp)
{
	if (sp->coord.x != 0 && sp->coord.y != 0)
	drawCircle(rt, sp->coord.x, sp->coord.y, sp->rayon, sp->color);
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

	if (fd < 0 || fd > 2000 || buffer[0] == -1 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_malloc(sizeof(char), free);
	str[0] = 0;
	return (gnl2(str, buffer, fd, free));
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

t_coord	makecoord(t_rt *rt, double x, double y)
{
	static t_coord	coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}

int	getred(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int	getgreen(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int	getblue(int rgb)
{
	return (rgb & 0xFF);
}

int	regetcolorint(t_color *color)
{
	return (color->red << 16 | color->green << 8 | color->blue);
}

t_color	getfromint(t_rt *rt, int color)
{
	t_color	*new;

	new = ft_malloc(sizeof(t_color), &rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	new->red = getred(color);
	new->blue = getblue(color);
	new->green = getgreen(color);
	return (*new);
}

int	quit(t_rt *rt)
{
	if (rt->image.origin != 0)
		mlx_destroy_image(rt->mlx_ptr, rt->image.origin);
	if (rt->win_ptr != 0)
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	if (rt->mlx_ptr != 0)
		mlx_destroy_display(rt->mlx_ptr);
	free(rt->mlx_ptr);
	ft_exit(rt, 0);
	return (0);
}

void	printpixelimg(t_rt *rt, t_coord print, t_color color)
{
	int		pos;
	int		colorint;
	char	*pixel;

	if (print.x < 0 || print.y < 0
		|| print.y > rt->ysize || print.x > rt->xsize)
		return ;
	pos = ((int)print.y * rt->image.size_line
			+ (int)print.x * (rt->image.bits_per_pixel / 8));
	pixel = rt->image.imgaddress + pos;
	colorint = regetcolorint(&color);
	*(int *)pixel = colorint;
}

void	printseg(t_rt *rt, t_seg *seg)
{
	printdroite(rt, (*seg).first, (*seg).second, (*seg).color);
}

void	printSquare(t_rt *rt, t_square *square)
{
	t_coord	third;
	t_coord	fourth;

	if (TEST == 1) {
		square->first.x = (((square->first.x + 5.14) / (9.56 + 5.14)) * 800) + 100;
		square->first.y = ((1 - ((square->first.y - 41.32) / (51.09 - 41.32))) * 800) + 100;
		square->second.x = (((square->second.x + 5.14) / (9.56 + 5.14)) * 800) + 100;
		square->second.y = ((1 - ((square->second.y - 41.32) / (51.09 - 41.32))) * 800) + 100;
	}
	if (TEST == 3) {
		square->first.x = (((square->first.x - 1.3) / (3.7 - 1.3)) * 800) + 100;
		square->first.y = ((1 - ((square->first.y - 47.9) / (49.3 - 47.9))) * 800) + 100;
		square->second.x = (((square->second.x - 1.3) / (3.7 + 1.3)) * 800) + 100;
		square->second.y = ((1 - ((square->second.y - 47.9) / (49.3 - 47.9))) * 800) + 100;
	}
	third = makecoord(rt, square->first.x, square->second.y);
	fourth = makecoord(rt, square->second.x, square->first.y);
	printdroite(rt, square->first, third, square->color);
	printdroite(rt, third, square->second, square->color);
	printdroite(rt, square->second, fourth, square->color);
	printdroite(rt, fourth, square->first, square->color);
}


t_square	*makenewsquare(t_rt *rt, t_coord coord1, t_coord coord2, t_color color)
{
	t_square	*square;

	square = ft_malloc(sizeof(t_square), &rt->garbage);
	if (!square)
		ft_exit(rt, "malloc error\n");
	square->first = coord1;
	square->second = coord2;
	square->color = color;
	return (square);
}

t_square *makefirstsquare(t_rt *rt)
{
	t_coord	*coord1;
	t_coord	*coord2;

	t_square	*square;

	square = ft_malloc(sizeof(t_square), &rt->garbage);
	if (!square)
		ft_exit(rt, "malloc error\n");
	square->first = makecoord(rt, rt->scene.objxmax, rt->scene.objymax);
	square->second = makecoord(rt, rt->scene.objxmin, rt->scene.objymin);
	square->color = getfromint(rt, 900);
;
	return (square);
}

t_coord	squaresplit(t_rt *rt, t_square *square)
{
	double	x;
	double	y;

	x = (-square->second.x + square->first.x) / 2 + square->second.x;
	y = (-square->second.y + square->first.y) / 2 + square->second.y;
	return (makecoord(rt, x, y));
}

t_line	*findsplitsquare(t_rt *rt, t_pos *obj, t_square *square, int depth)
{
	t_line	*line;

	line = ft_malloc(sizeof(t_line), &rt->garbage);
	if (!line)
		ft_exit(rt, "malloc error\n");
	if (depth == 0)
	{
		line->coord = squaresplit(rt, square);
		line->ori = makecoord(rt, 0, 1);
		line->color = getfromint(rt, 900);
	}
	if (depth == 1)
	{
		line->coord = squaresplit(rt, square);
		line->ori = makecoord(rt, 1, 0);
		line->color = getfromint(rt, 900);
	}
	return (line);
}

void	printobj(t_rt *rt, t_obj *obj)
{
	if (obj->type == SEG)
		printseg(rt, (t_seg *)obj->obj);
	if (obj->type == SQUARE)
		printSquare(rt, (t_square *)obj->obj);
	if (obj->type == LYCEE)
		printLycee(rt, (t_lycee *)obj->obj);
}

void	printObjListName(t_rt *rt, t_pos *print)
{
	t_list	*liste;
	int		mem;
	static int lol = 0;

	if (!print || print->size == 0) {
		return;
	}
	mem = 0;
	liste = print->start;
	while (liste != print->start || mem++ == 0)
	{
		// if (listToLycee(liste)->value > lol) {
			printf("%s ", listToLycee(liste)->name);
			// printf("%d ", print->size);
			// lol = test;
		// }
		liste = liste->next;
	}
	// printf("\nsize max: %d\n", lol);
	// printf("\nnode number: %d\n", lol2);
	// printf("\n: %d\n", lol3);
	printf("\n");
}

void	printobjlist(t_rt *rt, t_pos *print)
{
	t_list	*liste;
	int		mem;

	if (!print || print->size == 0)
		return;
	mem = 0;
	liste = print->start;
	while (liste != print->start || mem++ == 0)
	{
		printobj(rt, (t_obj *)liste->content);
		liste = liste->next;
	}
}

t_square	*splitsquaregauche(t_rt *rt, t_square *square, t_line *line, int depth)
{
	t_coord	coord1;
	t_coord	coord2;

	if (depth == 0)
	{
		coord1 = makecoord(rt, square->first.x, square->first.y);
		coord2 = makecoord(rt, line->coord.x, square->second.y);
	}
	if (depth == 1)
	{
		coord1 = makecoord(rt, square->first.x, square->first.y);
		coord2 = makecoord(rt, square->second.x, line->coord.y);
	}
	return (makenewsquare(rt, coord1, coord2, getfromint(rt, 900)));
}

t_square	*splitsquaredroite(t_rt *rt, t_square *square, t_line *line, int depth)
{
	t_coord	coord1;
	t_coord	coord2;

	if (depth == 0)
	{
		coord1 = makecoord(rt, line->coord.x, square->first.y);
		coord2 = makecoord(rt, square->second.x, square->second.y);
	}
	if (depth == 1)
	{
		coord1 = makecoord(rt, square->first.x, line->coord.y);
		coord2 = makecoord(rt, square->second.x, square->second.y);
	}
	return (makenewsquare(rt, coord1, coord2, getfromint(rt, 900)));
}

t_pos	*objRight(t_rt *rt, t_line *line, t_pos *obj, int depth)
{
	t_pos	*new;
	t_list	*mem;
	int		lol;

	lol = 0;
	new = setpos(&rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	mem = obj->start;
	if (!mem)
		return (new);
	while (mem != obj->start || !lol++)
	{
		if (((t_obj *)mem->content)->xmin < line->coord.x && depth == 0)
		{
			listToLycee(mem)->color.red += 50;
			mem = mem->next;
			lstnew(mem->back->content ,new, &rt->garbage);
		}
		else if (((t_obj *)mem->content)->ymin < line->coord.y && depth == 1)
		{
			listToLycee(mem)->color.red += 50;
			mem = mem->next;
			lstnew(mem->back->content ,new, &rt->garbage);
		}
		else
			mem = mem->next;
	}
	return (new);
}


t_pos	*objLeft(t_rt *rt, t_line *line, t_pos *obj, int depth)
{
	t_pos	*new;
	t_list	*mem;
	int		lol;

	lol = 0;
	new = setpos(&rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	mem = obj->start;
	if (!mem)
		return (new);
	while (mem != obj->start || !lol++)
	{
		if (((t_obj *)mem->content)->xmax > line->coord.x && depth == 0)
		{
			listToLycee(mem)->color.blue += 50;
			mem = mem->next;
			lstnew(mem->back->content ,new, &rt->garbage);
		}
		else if (((t_obj *)mem->content)->ymax > line->coord.y && depth == 1)
		{
			listToLycee(mem)->color.blue += 50;
			mem = mem->next;
			lstnew(mem->back->content ,new, &rt->garbage);
		}
		else
			mem = mem->next;
	}
	return (new);
}

// // void	clearobjlist(t_pl *pl, t_pos *obj, int depth)
// // {
// // 	t_list	*mem;
// // 	int		lol;
// //
// // 	lol = 0;
// // 	mem = obj->start;
// // 	if (!mem)
// // 		return ;
// // 	while (*mem->pos->size != 0 && (mem != obj->start || !lol++))
// // 	{
// // 		if ((((t_obj *)mem->content)->xmax != pl->coord->x || ((t_obj *)mem->content)->xmin != pl->coord->x) && depth == 0)
// // 		{
// // 			lol--;
// // 			mem = mem->next;
// // 			lstdelone(mem->back ,0);
// // 		}
// // 		else if ((((t_obj *)mem->content)->ymax != pl->coord->y || ((t_obj *)mem->content)->ymin != pl->coord->y) && depth == 1)
// // 		{
// // 			lol--;
// // 			mem = mem->next;
// // 			lstdelone(mem->back ,0);
// // 		}
// // 		else if ((((t_obj *)mem->content)->zmax != pl->coord->z || ((t_obj *)mem->content)->zmin != pl->coord->z) && depth == 2)
// // 		{
// // 			lol--;
// // 			mem = mem->next;
// // 			lstdelone(mem->back ,0);
// // 		}
// // 		else
// // 			mem = mem->next;
// // 	}
// // }
//
// t_pos	*lstdup(t_pos *pos, t_pos *garbage)
// {
// 	t_pos	*new;
// 	t_list	*liste;
// 	int	i;
//
// 	i = 0;
// 	liste = pos->start;
// 	new = setpos(garbage);
// 	while (i < pos->size)
// 	{
// 		lstnew(liste->content, new, garbage);
// 		liste = liste->next;
// 		i++;
// 	}
// 	return (new);
// }
//

t_bt	*newleaf(t_rt *rt, t_pos *obj)
{
	t_bt *new;

	new = ft_malloc(sizeof(t_bt), &rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	new->obj = obj;
	new->right = 0;
	new->racine = 0;
	new->left = 0;
	new->split = 0;
	return (new);
}

t_bt	*newnoeu(t_rt *rt, t_bt *right, t_bt *left, t_line *split)
{
	t_bt	*new;

	new = newleaf(rt, 0);
	if (right)
		right->racine = new;
	if (left)
		left->racine = new;
	new->left = left;
	new->right = right;
	new->racine = 0;
	new->split = split;
	return (new);
}

void	printLineInSquare(t_rt *rt, t_line *line, t_square *square)
{
	t_coord	first;
	t_coord	second;

	first = makecoord(rt, line->coord.x + rt->xsize * line->ori.x, line->coord.y + rt->ysize * line->ori.y);
	if (first.x > square->first.x)
		first.x = square->first.x;
	if (first.y > square->first.y)
		first.y = square->first.y;
	second = makecoord(rt, line->coord.x + -(rt->xsize * line->ori.x), line->coord.y + -(rt->ysize * line->ori.y));
	if (second.x < square->second.x)
		second.x = square->second.x;
	if (second.y < square->second.y)
		second.y = square->second.y;
	printdroite(rt, second, first, line->color);
	line->color.red = line->color.red + 30;
	line->color.green = line->color.green + 30;
	first = makecoord(rt, line->coord.x + 10 * line->ori.y, line->coord.y + 10 * line->ori.x);
	printdroite(rt, line->coord, first, line->color);
}

t_bt	*treeConstruct(t_rt *rt, t_pos *obj, t_square *square, int depth, int history[3])
{
	t_line	*line;
	t_square	*squareRight;
	t_square	*squareLeft;
	t_pos	*objListRight;
	t_pos	*objListLeft;

	// printf("asdf\n");
	if (obj->size == 0)
		return 0;
	if (depth >= 30 || (obj->size == history[0] && obj->size == history[1] && obj->size == history[2]))
		return (newleaf(rt, obj));
	line = findsplitsquare(rt, obj, square, depth % 2);
	printLineInSquare(rt, line, square);
	squareRight = splitsquaredroite(rt, square, line, depth % 2);
	squareLeft = splitsquaregauche(rt, square, line, depth % 2);
	history[0] = history[1];
	history[1] = history[2];
	history[2] = obj->size;
	objListLeft = objLeft(rt, line, obj, depth % 2);
	objListRight = objRight(rt, line, obj, depth % 2);
	return (newnoeu(rt, treeConstruct(rt, objListRight, squareRight, depth + 1, history), treeConstruct(rt, objListLeft, squareLeft, depth + 1, history), line));
}

// void	printList(t_rt *rt, t_pos *pos) {
// 	t_list	*liste;
// 	int		mem;
// 	static int		lol = 0;
//
// 	if (!pos || pos->size == 0) {
// 		return;
// 	}
// 	mem = 0;
// 	liste = pos->start;
// 	while (liste != pos->start || mem++ == 0)
// 	{
// 			// printf("%s\n", listToLycee(liste)->name);
// 		if (listToLycee(liste)->value >= lol) {
// 			lol = listToLycee(liste)->value;
// 			printf("act: %s\n", listToLycee(liste)->name);
// 			printf("value: %f\n", listToLycee(liste)->value);
// 		}
//
// 		liste = liste->next;
// 	}
// }
double maxToParse = 0;

void	addValueOne(t_rt *rt, t_pos *obj, t_lycee *add) {
	// t_list	*liste;
	// int		mem;
	// int	toAdd = 0;
	//
	if (!obj || obj->size == 0) {
		return;
	}
	static int lol = 0;
	// mem = 0;
	// liste = obj->start;
	// while (liste != obj->start || mem++ == 0)
	// {
	// 	if (add->name != listToLycee(liste)->name) {
	// 		toAdd++;
	// 	// printf("yessssssss %s %f\n",add->name, add->value);
	// 	}
	// 	liste = liste->next;
	// }
	// if (toAdd != obj->size - 1)
		// printf("%d %d\n", toAdd, obj->size - 1);
	if (obj->size - 1 > add->value)
		add->value = obj->size - 1;
	if (add->value > maxToParse) {
		maxToParse = add->value;
		// printf("%f %s\n", add->value, add->name);
	}

	// if (add->value == 41) {
		// printLycee(rt, add);
	// }
	// printList(rt, obj);
}

void	addValueAll(t_rt *rt, t_pos *obj) {
	t_list	*liste;
	int		mem;

	if (!obj || obj->size == 0) {
		return;
	}
	mem = 0;
	liste = obj->start;
	while (liste != obj->start || mem++ == 0)
	{
		addValueOne(rt, obj, listToLycee(liste));
		liste = liste->next;
	}
}


void	exploreTree(t_rt *rt, t_bt *tree) {
	static int lol = 0;
	if (tree->left) {
		exploreTree(rt, tree->left);
	// printObjListName(rt, tree->obj);
	}
	if (tree->right) {
		exploreTree(rt, tree->right);
	// printObjListName(rt, tree->obj);
	}
	if (tree->obj && tree->obj->size != 0) {
		addValueAll(rt, tree->obj);
	// printf("node: %i\n", lol);
	// lol++;
	// printObjListName(rt, tree->obj);
	}


}

void	exploreTree2(t_rt *rt, t_bt *tree) {
	if (tree->left)
		exploreTree2(rt, tree->left);
	if (tree->right)
		exploreTree2(rt, tree->right);
	// printList(rt, tree->obj);
	printObjListName(rt, tree->obj);
	// printobjlist(rt, tree->obj);
	// if (tree->obj && tree->obj->size != 0) {
	// }


}

t_bt *searchCoordInTree(t_rt *rt, t_bt *tree, t_coord coord) {
	if (tree->obj && tree->obj->size != 0) {
		return (tree);
	}
	if (tree->split->ori.x == 0) {
		if (tree->split->coord.x <= coord.x) {
			return (searchCoordInTree(rt, tree->left, coord));
		}
		else {
			return (searchCoordInTree(rt, tree->right, coord));
		}
	}
	else {
		if (tree->split->coord.y <= coord.y) {
			return (searchCoordInTree(rt, tree->left, coord));
		}
		else {
			return (searchCoordInTree(rt, tree->right, coord));
		}
	}
	return 0;
}

void	construcbtree(t_rt *rt)
{
	t_square	*square;
	t_pos	*start;
	t_bt	*tree;
	t_bt	*in;
	int	history[3];

	square = makefirstsquare(rt);
	history[0] = -1;
	history[1] = -1;
	history[2] = -1;
	rt->scene.tree = treeConstruct(rt, &rt->scene.obj, square, 0, history);
	exploreTree(rt, rt->scene.tree);
	// exploreTree2(rt, tree);
	// printList(rt, &rt->obj);
	// printf("%d\n", rt->obj.size);
	// in = searchCoordInTree(rt, tree, makecoord(rt, 200, 800));
	// printf("alors: %p\n", in);
	// printObjListName(rt, in->obj);

}

void	clearImg(t_rt *rt)
{


	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < rt->ysize)
	{
		while (x < rt->xsize)
		{
				int pos = ((int)y * rt->image.size_line
					+ (int)x * (rt->image.bits_per_pixel / 8));
				char *pixel = rt->image.imgaddress + pos;
				*(int *)pixel = 0;
			x++;
		}
		y++;
		x = 0;
	}
}

void	initMinilibx(t_rt *rt)
{
	rt->mlx_ptr = mlx_init();
	if (rt->mlx_ptr == 0)
		ft_exit(rt, "Error");
	rt->win_ptr = mlx_new_window(rt->mlx_ptr, rt->xsize, rt->ysize, "rt");
	if (rt->win_ptr == 0)
		quit(rt);
	rt->image.origin = mlx_new_image(rt->mlx_ptr, rt->xsize, rt->ysize);
	if (rt->image.origin == 0)
		quit(rt);
	rt->image.imgaddress = mlx_get_data_addr(rt->image.origin,
			&rt->image.bits_per_pixel,
			&rt->image.size_line, &rt->image.endian);
}

t_coord	atoicoord(t_rt *rt, char *str)
{
	t_coord	coord;
	int		i;

	i = 0;
	coord.x = atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	coord.y = atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	return (coord);
}

void	calcLycee(t_obj *objet)
{
	t_lycee	*lycee;

	lycee = (t_lycee *)objet->obj;
	objet->xmin = lycee->coord.x - lycee->rayon;
	objet->xmax = lycee->coord.x + lycee->rayon;
	objet->ymin = lycee->coord.y - lycee->rayon;
	objet->ymax = lycee->coord.y + lycee->rayon;
}

void	calcsquare(t_obj *objet)
{
	t_square	*square;

	square = (t_square *)objet->obj;
	objet->xmin = min(square->first.x, square->second.x);
	objet->ymin = min(square->first.y, square->second.y);
	objet->xmax = max(square->first.x, square->second.x);
	objet->ymax = max(square->first.y, square->second.y);
}


void	calccoordobjrt(t_scene *scene, t_obj *obj)
{
	if (obj->xmin < scene->objxmin)
		scene->objxmin = obj->xmin;
	if (obj->ymin < scene->objymin)
		scene->objymin = obj->ymin;
	if (obj->ymax > scene->objymax)
		scene->objymax = obj->ymax;
	if (obj->xmax > scene->objxmax)
		scene->objxmax = obj->xmax;
}

void	calcobj(t_rt *rt, t_obj *objet)
{
	if (objet->type == LYCEE)
		calcLycee(objet);
	else if (objet->type == SQUARE)
		calcsquare(objet);
	calccoordobjrt(&rt->scene, objet);
}

int	coordInCircle(t_coord coord, t_lycee *lycee) {
	double distance = sqrt(pow(coord.x - lycee->coord.x, 2) + pow(coord.y - lycee->coord.y, 2));
	if (distance <= lycee->rayon) {
		return 1;
	}
	return 0;
}

void	calcInside(t_rt *rt, t_lycee *lyc, t_pos *obj) {
	t_list	*liste;
	t_bt	*find;
	int		mem;
	int add =0;
	static int lol = 0;

	if (!obj || obj->size == 0) {
		return;
	}
	mem = 0;
	liste = obj->start;
	while (liste != obj->start || mem++ == 0)
	{
		if (listToLycee(liste)->name != lyc->name) {
			if (coordInCircle(lyc->coord, listToLycee(liste)))
				add++;

		}
		liste = liste->next;
	}
	if (add >= lol) {
		lol = add;
		printf("lol%d\n", add);
		printf("name: %s\n", lyc->name);

	}

}

void	printListMax(t_rt *rt, t_pos *pos) {
	t_list	*liste;
	t_bt	*find;
	int		mem;

	if (!pos || pos->size == 0) {
		return;
	}
	mem = 0;
	liste = pos->start;
	while (liste != pos->start || mem++ == 0)
	{
			// printf("%s\n", listToLycee(liste)->name);
		if (listToLycee(liste)->value >= maxToParse) {
			find = searchCoordInTree(rt, rt->scene.tree, listToLycee(liste)->coord);
			if (find) {
				calcInside(rt, listToLycee(liste), find->obj);
			}
		}
		liste = liste->next;
	}
}

void	findCoordMax(t_rt *rt) {
	printListMax(rt, &rt->scene.obj);
}

void	printScene(t_rt *rt)
{
	clearImg(rt);
	construcbtree(rt);
	printf("%f %f %f %f\n", rt->scene.objxmin, rt->scene.objxmax,rt->scene.objymin,rt->scene.objymax);
	findCoordMax(rt);
	printobjlist(rt, &rt->scene.obj);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
}

int	keyHook(int keycode, t_rt *rt)
{
	if (keycode == 65307)
		quit(rt);
	clearImg(rt);
	printScene(rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
	return (keycode);
}

void	*makeobj(t_rt *rt, void *obj, int type)
{
	t_obj	*objet;

	objet = ft_malloc(sizeof(t_obj), &rt->garbage);
	if (!obj)
		ft_exit(rt, "malloc error\n");
	objet->type = type;
	objet->obj = obj;
	calcobj(rt, objet);
	return (objet);
}


int	ft_strstr(const char *big, const char *libtle) {
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;

	int bigLen = strlen(big);
	int libtleLen = strlen(libtle);
	if (libtle == 0 || big == 0) {
		return (-1);
	}
	while (big[i]) {
		j = 0;
		while (libtle[j] == big[i + j])
		{
			if (libtle[j + 1] == 0)
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

char *searchJsonValue(t_rt *rt, char *str, char *toSearch) {
	int	start;
	int end;


	start = ft_strstr(str, toSearch);
	start = start + strlen(toSearch) + 2;
	if (str[start] == '"')
		start++;
	end = ft_strstr(&str[start], "\"");
	if (end == -1) {
		end = strlen(str) - 1;
	}
	end += start;
	return (substr(str, start, end - start, &rt->garbage));
}


void	*makeLycee(t_rt *rt, char *str)
{
	t_lycee	*new;
	int		i;
	char *end;

	new = ft_malloc(sizeof(t_lycee), &rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	new->coord.x = strtod(searchJsonValue(rt, str, "Longitude"), &end);
	new->coord.y = strtod(searchJsonValue(rt, str, "Latitude"), &end);

	if (TEST == 3) {
		if (new->coord.x < 1.3 || new->coord.x > 3.7 || new->coord.y < 47.9 || new->coord.y > 49.3)
			return 0;
	}
	else if (TEST != 2) {
		if (new->coord.x < -5.15 || new->coord.x > 9.56 || new->coord.y < 41.31 || new->coord.y > 51.1)
			return 0;
	}
	new->name = searchJsonValue(rt, str, "Nom_etablissement");
	if (TEST == 0)
		new->rayon = 0.1;
	if (TEST == 1)
		new->rayon = 0.01;
	if (TEST == 2)
		new->rayon = 20;
	if (TEST == 3)
		new->rayon = 0.01;
	new->color = getfromint(rt, 900);
	new->value = 0;
	t_obj *ret = makeobj(rt, new, LYCEE);
	return (ret);
}

void	parse(t_rt *rt, char	*in)
{
	int	i = 0;
	t_obj *new;
	i = ft_strstr(in, "Nom_etablissement");
	if (i != -1) {
		new = makeLycee(rt, in);
		if (new)
		lstnew(new, &rt->scene.obj, &rt->garbage);
	}
}

void	ft_open(t_rt *rt)
{
	char	*temp;
	char	*ret;
	int		fd;

	ret = ft_strdup("", &rt->garbage);
	if (ret == 0)
		ft_exit(rt, "ERROR");
	if (TEST == 0)
		fd = open("lycee.json", O_RDONLY);
	if (TEST == 1)
		fd = open("lycee.json", O_RDONLY);
	if (TEST == 2)
		fd = open("test2.json", O_RDONLY);
	if (TEST == 3)
		fd = open("lycee.json", O_RDONLY);
	if (fd == -1)
		ft_exit(rt, "Error");
	int i = 0;
	while (1)
	{
		temp = get_next_line(fd, &rt->garbage);
		if (temp == 0)
		{
			close(fd);
			return ;
		}
		parse(rt, temp);
	}
}

void	resetScene(t_rt *rt) {
	if (rt->scene.garbage.size != 0)
		posclear(&rt->scene.garbage, 1);
	if (rt->scene.obj.size != 0)
		posclear(&rt->scene.obj, 1);
	rt->scene.obj.start = 0;
	rt->scene.obj.end = 0;
	rt->scene.obj.size = 0;
	rt->scene.tree = 0;
	rt->scene.objxmin = -2000;
	rt->scene.objymin = -2000;
	rt->scene.objxmax = 2000;
	rt->scene.objymax = 2000;
}

void	initrt(t_rt *rt)
{
	t_pos	*garbage;

	rt->garbage.start = 0;
	rt->garbage.end = 0;
	rt->garbage.size = 0;
	rt->scene.garbage.size = 0;
	rt->scene.garbage.end = 0;
	rt->scene.garbage.start = 0;
	rt->scene.obj.start = 0;
	rt->scene.obj.end = 0;
	rt->scene.obj.size = 0;
	rt->scene.tree = 0;
	rt->scene.objxmin = 2000;
	rt->scene.objymin = 2000;
	rt->scene.objxmax = -2000;
	rt->scene.objymax = -2000;
	rt->win_ptr = 0;
	rt->mlx_ptr = 0;
	rt->xsize = 1000;
	rt->ysize = 1000;
	rt->origin = makecoord(rt, 0, 0);
	rt->image.origin = 0;
}

int	main() {
	t_rt	rt;

	initrt(&rt);
	initMinilibx(&rt);
	ft_open(&rt);
	printScene(&rt);
	mlx_hook(rt.win_ptr, 17, 0, quit, &rt);
	mlx_key_hook(rt.win_ptr, &keyHook, &rt);
	mlx_loop(rt.mlx_ptr);
}
