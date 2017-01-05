#include "my.h"

t_my_framebuffer *create_pixel_buffer(int width, int height)
{
  int i;
  sfUint8* pixels;
  t_my_framebuffer *pixelbuffer;

  pixels = malloc(width * height * 4 * sizeof(*pixels));
  pixelbuffer = malloc(width * height * 4 * sizeof(*pixelbuffer));
  if (pixels == NULL)
    exit(EXIT_FAILURE);
  i = 0;
  while (i < width * height * 4)
    {
      pixels[i] = 0;
      i = i + 1;
    }
  pixelbuffer->pixels = pixels;
  pixelbuffer->height = height;
  pixelbuffer->width = width;
  return (pixelbuffer);
}

void        loop_rc(t_my_framebuffer *framebuffer, t_pdir camera, sfVector2f plan)
{
  int       x;
  float     line_h;
  float     direction;
  double    camReduc;
  sfVector2i useless;
  t_pdir    ray;

  x = 0;
  while (x < SCREEN_WIDTH)
    {
      camReduc = ((2 * x) / (double)SCREEN_WIDTH - 1);
      ray.pos.x = camera.pos.x;
      ray.pos.y = camera.pos.y;
      ray.dir.x = camera.dir.x + plan.x * camReduc;
      ray.dir.y = camera.dir.y + plan.y * camReduc;
      //printf("ray.dir.x = %f; ray.dir.y = %f", ray.dir.x, ray.dir.y);
      //printf("\t%f", sqrt((ray.dir.x * ray.dir.x) + (ray.dir.y * ray.dir.y)));
      direction = atan2(ray.dir.y, ray.dir.x);
      G_MAP_COO.x = (int)ray.pos.x;
      G_MAP_COO.y = (int)ray.pos.y;
      G_LEN = sqrt(ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y);
      line_h = raycast(ray.pos, direction, useless);
      draw_vert(x, (int)line_h, framebuffer);
      x++;
    }
}

int     main()
{
  sfVideoMode mode = {SCREEN_WIDTH, SCREEN_HEIGHT, 32};
  sfRenderWindow* window;
  sfEvent event;
  sfSprite* sprite;
  sfTexture* texture;
  t_my_framebuffer *framebuffer;
  t_pdir camera;
  sfVector2f plan;
  double moveSpeed = 0.05;
  double rotSpeed = 0.03;
  
  sprite = sfSprite_create();
  framebuffer = create_pixel_buffer(SCREEN_WIDTH, SCREEN_HEIGHT);

  plan.x = 0;
  plan.y = 0.66;

  camera.pos.x = 2;
  camera.pos.y = 2;
  camera.dir.x = -1;
  camera.dir.y = 0;

  texture = sfTexture_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  sfSprite_setTexture(sprite, texture, sfTrue);
  window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
  if (!window)
    return EXIT_FAILURE;
  while (sfRenderWindow_isOpen(window))
    {
      if (sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(window);
      if (sfKeyboard_isKeyPressed(sfKeyDown))
        {
          double moveX = camera.dir.x * moveSpeed, moveY = camera.dir.y * moveSpeed;
          if (map[(int)(camera.pos.x - moveX)][(int)(camera.pos.y - moveY)] == 0)
            {
              camera.pos.x -= moveX;
              camera.pos.y -= moveY;
            }
        }
      if (sfKeyboard_isKeyPressed(sfKeyUp))
        {
          float moveX = camera.dir.x * moveSpeed, moveY = camera.dir.y * moveSpeed;
          if (map[(int)(camera.pos.x + moveX)][(int)(camera.pos.y + moveY)] == 0)
            camera.pos = move_forward(camera.pos, moveY, moveX);
        }
      if (sfKeyboard_isKeyPressed(sfKeyRight))
        {
          double oldDirX = camera.dir.x;
          camera.dir.x = camera.dir.x * cos(-rotSpeed) - camera.dir.y * sin(-rotSpeed);
          camera.dir.y = oldDirX * sin(-rotSpeed) + camera.dir.y * cos(-rotSpeed);
          double oldPlaneX = plan.x;
          plan.x = plan.x * cos(-rotSpeed) - plan.y * sin(-rotSpeed);
          plan.y = oldPlaneX * sin(-rotSpeed) + plan.y * cos(-rotSpeed);
        }
      //rotate to the left
      if (sfKeyboard_isKeyPressed(sfKeyLeft))
        {
          //both camera direction and camera plane must be rotated
          double oldDirX = camera.dir.x;
          camera.dir.x = camera.dir.x * cos(rotSpeed) - camera.dir.y * sin(rotSpeed);
          camera.dir.y = oldDirX * sin(rotSpeed) + camera.dir.y * cos(rotSpeed);
          double oldPlaneX = plan.x;
          plan.x = plan.x * cos(rotSpeed) - plan.y * sin(rotSpeed);
          plan.y = oldPlaneX * sin(rotSpeed) + plan.y * cos(rotSpeed);
        }
      loop_rc(framebuffer, camera, plan);
      sfTexture_updateFromPixels(texture, framebuffer->pixels, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
    }
}
