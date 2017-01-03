/*
** my_put_pixel.c for  in /home/tbesson/raytest/raycasting
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Tue Jan  3 14:42:33 2017 Tamsi Besson
** Last update Tue Jan  3 14:59:07 2017 Tamsi Besson
*/

#include "my.h"

void	my_put_pixel(t_my_framebuffer *framebuffer, int x, int y, sfColor color)
{
  framebuffer->pixels[(SCREEN_WIDTH * y + x) * 4] = color.r;
  framebuffer->pixels[(SCREEN_WIDTH * y + x) * 4 + 1] = color.g;
  framebuffer->pixels[(SCREEN_WIDTH * y + x) * 4 + 2] = color.b;
  framebuffer->pixels[(SCREEN_WIDTH * y + x) * 4 + 3] = color.a;
}
