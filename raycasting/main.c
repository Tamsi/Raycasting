#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MAP_COLS 24
#define MAP_ROWS 24

typedef struct
{
  double   x;
  double   y;
}coo;

typedef struct
{
  coo dir;
  coo pos;
}pdir;

int     WORLD_MAP[MAP_ROWS][MAP_COLS] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 1, 1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void raycast(sfUint8* pixels, pdir camera, coo plan)
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
          if (WORLD_MAP[mapX][mapY] > 0)
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
      if (WORLD_MAP[mapX][mapY] == 1)
	color = sfBlue;
      else if (WORLD_MAP[mapX][mapY] == 2)
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
              pixels[(SCREEN_WIDTH * y + x) * 4] = 0;
              pixels[(SCREEN_WIDTH * y + x) * 4 + 1] = 0;
              pixels[(SCREEN_WIDTH * y + x) * 4 + 2] = 0;
              pixels[(SCREEN_WIDTH * y + x) * 4 + 3] = 0;
            }
          else
            {
              pixels[(SCREEN_WIDTH * y + x) * 4] = color.r;
              pixels[(SCREEN_WIDTH * y + x) * 4 + 1] = color.g;
              pixels[(SCREEN_WIDTH * y + x) * 4 + 2] = color.b;
              pixels[(SCREEN_WIDTH * y + x) * 4 + 3] = color.a;
            }
          y++;
        }
      x++;
    }
}

sfUint8* create_pixel_buffer(int width, int height)
{
  int i;
  sfUint8* pixels;

  pixels = malloc(width * height * 4 * sizeof(*pixels));
  if (pixels == NULL)
    {
      exit(EXIT_FAILURE);
    }
  i = 0;
  while (i < width * height * 4)
    {
      pixels[i] = 0;
      i = i + 1;
    }
  return pixels;
}

int     main()
{
  sfVideoMode mode = {SCREEN_WIDTH, SCREEN_HEIGHT, 32};
  sfRenderWindow* window;
  sfEvent event;
  sfSprite* sprite;
  sfTexture* texture;
  sfUint8* pixels;
  pdir camera;
  coo plan;
  double moveSpeed = 0.2;
  double rotSpeed = 0.3;
  
  sprite = sfSprite_create();
  pixels = create_pixel_buffer(SCREEN_WIDTH, SCREEN_HEIGHT);

  plan.x = 0;
  plan.y = 0.66;

  camera.pos.x = 12;
  camera.pos.y = 12;
  camera.dir.x = -1;
  camera.dir.y = 0;

  texture = sfTexture_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  sfSprite_setTexture(sprite, texture, sfTrue);
  window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
  if (!window)
    return EXIT_FAILURE;
  while (sfRenderWindow_isOpen(window))
    {
      while (sfRenderWindow_pollEvent(window, &event))
        {
          if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
	  if (event.type == sfEvtKeyPressed)
	    {
	      if (event.key.code == sfKeyEscape)
		sfRenderWindow_close(window);
	      if (event.key.code == sfKeyDown)
		{
		  double moveX = camera.dir.x * moveSpeed, moveY = camera.dir.y * moveSpeed;
		  if (WORLD_MAP[(int)(camera.pos.x - moveX)][(int)(camera.pos.y - moveY)] == 0)
		    {
		      camera.pos.x -= moveX;
		      camera.pos.y -= moveY;
		    }
		}
	      if (event.key.code == sfKeyUp)
		{
		  double moveX = camera.dir.x * moveSpeed, moveY = camera.dir.y * moveSpeed;
		  if (WORLD_MAP[(int)(camera.pos.x + moveX)][(int)(camera.pos.y + moveY)] == 0)
		    {
		      camera.pos.x += moveX;
		      camera.pos.y += moveY;
		    }
		}
	      if (event.key.code == sfKeyRight)
		{
		  double oldDirX = camera.dir.x;
		  camera.dir.x = camera.dir.x * cos(-rotSpeed) - camera.dir.y * sin(-rotSpeed);
		  camera.dir.y = oldDirX * sin(-rotSpeed) + camera.dir.y * cos(-rotSpeed);
		  double oldPlaneX = plan.x;
		  plan.x = plan.x * cos(-rotSpeed) - plan.y * sin(-rotSpeed);
		  plan.y = oldPlaneX * sin(-rotSpeed) + plan.y * cos(-rotSpeed);
		}
	      //rotate to the left
	      if (event.key.code == sfKeyLeft)
		{
		  //both camera direction and camera plane must be rotated
		  double oldDirX = camera.dir.x;
		  camera.dir.x = camera.dir.x * cos(rotSpeed) - camera.dir.y * sin(rotSpeed);
		  camera.dir.y = oldDirX * sin(rotSpeed) + camera.dir.y * cos(rotSpeed);
		  double oldPlaneX = plan.x;
		  plan.x = plan.x * cos(rotSpeed) - plan.y * sin(rotSpeed);
		  plan.y = oldPlaneX * sin(rotSpeed) + plan.y * cos(rotSpeed);
		}
	    }
        }
      raycast(pixels, camera, plan);
      sfTexture_updateFromPixels(texture, pixels, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
    }
}
