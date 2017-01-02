/*
** raycast.c for   in /home/tbesson/raytest/raycasting
** 
** Made by Tamsi Besson
** Login   <tbesson@epitech.net>
** 
** Started on  Mon Jan  2 15:02:06 2017 Tamsi Besson
** Last update Mon Jan  2 23:35:38 2017 Tamsi Besson
*/

#include "my.h"

void raycast(t_my_framebuffer pixels, pdir camera, coo plan)
{
  int   x = 0;

  while (x < SCREEN_WIDTH)
    {
      int   hit = 0;
      int   stepX, stepY;
      int   side;
      pdir  ray;
      double perpWallDist;
      int   mapX, mapY;
      double camReduc;

      coo   sideDist;
      coo   deltaDist;

      //rays + reduction orthonormée
      camReduc = ((2 * x) / (double)SCREEN_WIDTH - 1);
      ray.pos.y = camera.pos.y;
      ray.pos.x = camera.pos.x;
      ray.dir.x = camera.dir.x + plan.x * camReduc;
      ray.dir.y = camera.dir.y + plan.y * camReduc;

      //DDA
      mapX = (int)ray.pos.x;
      mapY = (int)ray.pos.y;
      deltaDist.x = sqrt(1 + (ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x));
      deltaDist.y = sqrt(1 + (ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y));
      if (ray.dir.x < 0)
        {
          stepX = -1;
          sideDist.x = (ray.pos.x - mapX) * deltaDist.x;
        }
      else
        {
          stepX = 1;
          sideDist.x = (mapX + 1.0 - ray.pos.x) * deltaDist.x;
        }
      if (ray.dir.y < 0)
        {
          stepY = -1;
          sideDist.y = (ray.pos.y - mapY) * deltaDist.y;
        }
      else
        {
          stepY = 1;
          sideDist.y = (mapY + 1.0 - ray.pos.y) * deltaDist.y;
        }
      while (hit == 0)
        {
          if (sideDist.x < sideDist.y)
            {
              sideDist.x += deltaDist.x;
              mapX += stepX;
              side = 0;
            }
          else
            {
              sideDist.y += deltaDist.y;
              mapY += stepY;
              side = 1;
            }
          if (map[mapX][mapY] > 0)
            hit = 1;
        }
      if (side == 0)
        perpWallDist = (mapX - ray.pos.x + (1 - stepX) / 2) / ray.dir.x;
      else
        perpWallDist = (mapY - ray.pos.y + (1 - stepY) / 2) / ray.dir.y;

      int line_h;
      int draw_start, draw_end;

      line_h = (int)(SCREEN_HEIGHT / perpWallDist);

      draw_start = SCREEN_HEIGHT / 2 - line_h / 2;
      if (draw_start < 0)
        draw_start = 0;

      draw_end = SCREEN_HEIGHT / 2 + line_h / 2;
      if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;

      int y = 0;

      sfColor color;
      if (map[mapX][mapY] == 1)
        color = sfBlue;
      else if (map[mapX][mapY] == 2)
        color = sfRed;
      if (side == 1)
        {
          color.r = (int) color.r / 2;
          color.g = (int) color.g / 2;
          color.b = (int) color.b / 2;
        }
      while (y < SCREEN_HEIGHT)
        {
          if (y < draw_start || y > draw_end)
            {
              pixels.pixels[(SCREEN_WIDTH * y + x) * 4] = 0;
              pixels.pixels[(SCREEN_WIDTH * y + x) * 4 + 1] = 0;
              pixels.pixels[(SCREEN_WIDTH * y + x) * 4 + 2] = 0;
              pixels.pixels[(SCREEN_WIDTH * y + x) * 4 + 3] = 0;
            }
          else
            {
              pixels.pixels[(SCREEN_WIDTH * y + x) * 4] = color.r;
              pixels.pixels[(SCREEN_WIDTH * y + x) * 4 + 1] = color.g;
              pixels.pixels[(SCREEN_WIDTH * y + x) * 4 + 2] = color.b;
              pixels.pixels[(SCREEN_WIDTH * y + x) * 4 + 3] = color.a;
            }
          y++;
        }
      x++;
    }
}
