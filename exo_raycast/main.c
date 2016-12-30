#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define WIDTH 800
#define HEIGHT 600
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


int     MAP[MAP_ROWS][MAP_COLS] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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

void raycast(sfUint8 *pixels, pdir camera, coo plan)
{
  pdir ray;
  coo  deltaDist;
  coo  steps;
  int  x = 0;
  
  while (x < WIDTH)
    {
      double camReduc = (double)((2 * x) / WIDTH - 1);
      ray.pos.x = camera.pos.x;
      ray.pos.y = camera.pos.y;
      int mapY = ray.pos.y;
      int mapX = ray.pos.x;
      ray.dir.x = camera.dir.x + plan.x * camReduc;
      ray.dir.y = camera.dir.y + plan.y * camReduc;

      deltaDist.x = sqrt (1 + ((ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x)));
      deltaDist.y = sqrt (1 + ((ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y)));
      int hit = 0;
      coo dist;
      int side;

      if (ray.dir.x >= 0)
        {
          dist.x = deltaDist.x;
          steps.x = 1;
        }
      else
        {
          dist.x = 0;
          steps.x = -1;
        }
      if (ray.dir.y >= 0)
        {
          dist.y = deltaDist.y;
          steps.y = 1;
        }
      else
        {
          dist.y = 0;
          steps.y = -1;
        }

      while (hit == 0)
        {
          if (dist.x < dist.y)
            {
              dist.x += deltaDist.x;
              mapX += steps.x;
              side = 0;
            }
          else
            {
              dist.y += deltaDist.y;
              mapY += steps.y;
              side = 1;
            }
          if (MAP[mapX][mapY] > 0)
            hit = 1;
        }
      int perpWallDist;

      if (side == 0)
	perpWallDist = (mapX - ray.pos.x + (1 - steps.x) / 2) / ray.dir.x;
      else
	perpWallDist = (mapY - ray.pos.y + (1 - steps.y) / 2) / ray.dir.y;
      int wall = HEIGHT / perpWallDist;
      int drawStart = HEIGHT / 2 - wall / 2;
      int drawEnd = HEIGHT / 2 + wall / 2;

      if (drawStart < 0)
        drawStart = 0;
      if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
      int y = 0;
      while (y < HEIGHT)
        {
          if (y < drawStart || y > drawEnd)
            {
              pixels[(WIDTH * y + x) * 4] = 0;
              pixels[(WIDTH * y + x) * 4 + 1] = 0;
              pixels[(WIDTH * y + x) * 4 + 2] = 0;
              pixels[(WIDTH * y + x) * 4 + 3] = 0;
            }
          else
            {
              pixels[(WIDTH * y + x) * 4] = sfRed.r;
              pixels[(WIDTH * y + x) * 4 + 1] = sfRed.g;
              pixels[(WIDTH * y + x) * 4 + 2] = sfRed.b;
              pixels[(WIDTH * y + x) * 4 + 3] = sfRed.a;
            }
          y++;
        }
      x++;
    }
}

int main()
{
  sfVideoMode mode = {WIDTH, HEIGHT, 32};
  sfRenderWindow* window;
  sfEvent event;
  sfSprite* sprite;
  sfTexture* texture;
  sfUint8* pixels;
  pdir camera;
  coo plan;

  sprite = sfSprite_create();
  pixels = create_pixel_buffer(WIDTH, HEIGHT);

  plan.x = 0;
  plan.y = 0.66;

  camera.pos.x = 20;
  camera.pos.y = 20;
  camera.dir.x = -1;
  camera.dir.y = 0;
  
  texture = sfTexture_create(WIDTH, HEIGHT);
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
              if (event.key.code == sfKeyDown)
		{
		  camera.pos.x += 0.2;
		  camera.pos.y += 0.2;
		}
              if (event.key.code == sfKeyUp)
		{
		  camera.pos.y -= 0.2;
		  camera.pos.x -= 0.2;
		}
            }
        }
      raycast(pixels, camera, plan);
      sfTexture_updateFromPixels(texture, pixels, WIDTH, HEIGHT, 0, 0);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
    }
}
