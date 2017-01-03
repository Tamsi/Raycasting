/*
** my_draw_line.c for   in /home/tbesson/raytest/raycasting
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Tue Jan  3 14:30:37 2017 Tamsi Besson
** Last update Tue Jan  3 15:12:42 2017 Tamsi Besson
*/

#include "my.h"

void	my_draw_line(t_my_framebuffer *framebuffer, sfVector2i from, sfVector2i to, sfColor color)
{
  while (from.y < to.y)
    {
      my_put_pixel(framebuffer, from.x, from.y, color);
      from.y++;
    }
}
