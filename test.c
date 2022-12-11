#include <stdio.h>
#include <unistd.h>

void affichebin(unsigned n)
{
	unsigned bit = 0 ;
	unsigned mask = 1 ;
	for (int i = 0 ; i < 32 ; ++i)
	{
		bit = (n & mask) >> i;
		printf("%d", bit);
		if ((i % 8) - 7 == 0 && i != 0)
			printf(" ");
		mask <<= 1;
	}
}

int main()
{
	unsigned mask1 = 255 << 16 | 255 << 8 | 255;
	unsigned mask2 = 255 << 24 | 255 << 8 | 255;
	unsigned mask3 = 255 << 24 | 255 << 16 | 255;
	unsigned mask4 = 255 << 24 | 255 << 16 | 255 << 8;

	unsigned int	c;
	unsigned color;
	unsigned change;

	color = mask2 | 128 << 16;
	c = 255 << 24 | 255 << 16 | 255 << 8 | 255;
	c = color & c;
	affichebin(c);
}
