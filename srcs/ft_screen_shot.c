/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen_shot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:26:56 by flavon            #+#    #+#             */
/*   Updated: 2020/09/17 11:22:04 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static int		make_header(unsigned char *bmp_fheader, unsigned char *bmpinfheader, t_data *img)
{
	int file_size;

	file_size = 14 + 40 + img->win.width * img->win.height
		* img->win.bit_pix / 8;
	bmp_fheader[0] = 'B';
	bmp_fheader[1] = 'M';
	bmp_fheader[2] = (unsigned char)(file_size);
	bmp_fheader[3] = (unsigned char)(file_size >> 8);
	bmp_fheader[4] = (unsigned char)(file_size >> 16);
	bmp_fheader[5] = (unsigned char)(file_size >> 24);
	bmp_fheader[10] = (unsigned char)(14 + 40);
	bmpinfheader[0] = (unsigned char)(40);
	bmpinfheader[4] = (unsigned char)(img->win.width);
	bmpinfheader[5] = (unsigned char)(img->win.width >> 8);
	bmpinfheader[6] = (unsigned char)(img->win.width >> 16);
	bmpinfheader[7] = (unsigned char)(img->win.width >> 24);
	bmpinfheader[8] = (unsigned char)(-img->win.height);
	bmpinfheader[9] = (unsigned char)(-img->win.height >> 8);
	bmpinfheader[10] = (unsigned char)(-img->win.height >> 16);
	bmpinfheader[11] = (unsigned char)(-img->win.height >> 24);
	bmpinfheader[12] = (unsigned char)(1);
	bmpinfheader[14] = (unsigned char)(img->win.bit_pix);
	return (1);
}

static int		write_in_header(unsigned char *bmp_fheader,
				unsigned char *bmpinfheader, t_data *img)
{
	int		fd;
	char	*filename;
	int		len;
	int		i;

	i = 0;
	filename = "screenshot.bmp";
	if ((fd = open(filename, O_RDWR | O_CREAT, 0755)) < 0)
		return (0);
	write(fd, bmp_fheader, 14);
	write(fd, bmpinfheader, 40);
	len = img->win.bit_pix / 8 * img->win.width;
	while (i < img->win.height)
	{
		write(fd, img->win.addr + i * img->win.length, len);
		i++;
	}
	if (close(fd < 0))
	{
		ft_putstr_fd("Close file error!\n");
		return (0);
	}
	return (1);
}

int				ft_screen_shot(t_data *img)
{
	unsigned char	bmp_fheader[14];
	unsigned char	bmpinfheader[40];


	ft_putstr_fd("Saving screenshot...\n");
	ft_bzero(bmp_fheader, 14);
	ft_bzero(bmpinfheader, 40);
	make_header(bmp_fheader, bmpinfheader, img);
	if (!write_in_header(bmp_fheader, bmpinfheader, img))
		ft_putstr_fd("Saving screenshot failed!\n");
	exit(0);
	return (0);
}