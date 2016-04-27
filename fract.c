#include <stdio.h>
#include <stdlib.h>

typedef struct fractal{
    int height;
    int width;
    double a;
    double b;
    double ** pixels;
} fractal;

void * fractal_new (int w, int h, double aa, double bb){
  fractal * fract = malloc(sizeof(fractal));
  fract->height=h;
  fract->width = w;
  fract->a = aa;
  fract->b = bb;
  fract->pixels = (double**)calloc(w, sizeof(double*));
  int i = 0;
  for (i; i < w; i++)
    fract->pixels[i] = (double*)calloc(h, sizeof(double));
  return fract;
}

void fractal_free(fractal * fract){
  int i = 0;
  for (i; i < fract->width; i++)
    free(fract->pixels[i]);
  free(fract->pixels);
  free(fract);
}

int fractal_get_height(fractal * fract){
  int rtn = fract->height;
  return rtn;
}

int fractal_get_width(fractal * fract){
  int rtn = fract->width;
  return rtn;
}

double fractal_get_a(fractal * fract){
  double rtn = fract->a;
  return rtn;
}

double fractal_get_b(fractal * fract){
  double rtn = fract->b;
  return rtn;
}

int set_value(fractal * fract, double value, int x, int y){
  if (x >= fractal_get_width(fract) || y >= fractal_get_height(fract) ||
        x<0 || y <0)
    return 1;
  fract->pixels[x][y] = value;
  return 0;
}

double get_value(fractal * fract, int x, int y){
  return (fract->pixels[x][y]);
}

void main(int argc, char *argv[]){
  void * fract = fractal_new(10, 10, -0.8, 0.4);
  int height = fractal_get_height(fract);
  int width = fractal_get_width(fract);
  double a = fractal_get_a(fract);
  double b = fractal_get_b(fract);
  printf("height: %d\nwidth: %d\na: %f\nb: %f\n", height, width, a, b);
  double x = 5.12345;
  if (set_value(fract, x, 4,4 ) == 1)
    printf("ben bravo\n");
  else {
    int i;
    int j;
    for(i=0; i<height; i++){
      for(j=0; j<width; j++){
        printf("%f  ", get_value(fract, j , i));
      }
      printf("\n");
    }
  }
  fractal_free(fract);
}
