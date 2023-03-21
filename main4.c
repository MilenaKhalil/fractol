#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <complex.h>
#include <math.h>
#define WIDTH 1024
#define HEIGHT 512

static mlx_image_t	*g_img;

double complex count(double complex z1, double complex z2)
{
    return (z1 * z1 + z2);
}

bool check(double complex z1)
{
    if (sqrt(pow(creal(z1), 2) + pow(cimag(z1), 2)) > 2)
        return (0);
    return (1);
}

void	hook(void* param)
{
	mlx_t* mlx;
    double complex z1;
    double complex z2;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, g_img);
	for (double x = 0; x < g_img->width; x++)
    {
		for(double y = 0; y < g_img->height; y++)
        {
            z1 = x / 256 - 2.5 + (y / 256 - 1) * I;
            z2 = z1;
            for (int k = 0; k < 180; k++)
            {
                z1 = count(z1, z2);                            // можно поменять z2 на z1 и чёткость по-меньше и тогда... 
                if (!check(z1))
                    break;
            }
            //printf("z1 * z1 = %.2f %+.2fi\n", creal(z1 * z1), cimag(z1 * z1));
            //
            if (check(z1))
            //if (sqrt(pow(x - 256, 2) + pow(y - 256, 2)) > 200)
			    mlx_put_pixel(g_img, x, y, 700 % RAND_MAX); // x * y // x * y * y // афигеть, какой приколдес
            else
                mlx_put_pixel(g_img, x, y, 0);
        }
    }
}

int32_t	main(void)
{
	mlx_t*    mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 1024, 1024);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

