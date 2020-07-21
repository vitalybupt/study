#include <stddef.h>

extern double calc_sphere_area_volume(double ri, double *sa, double *vol);

/* void example_ch05_02() { */
void main(){
  double r[] = {0.0, 1.0, 2.0, 3.0, 5.0, 10.0, 20.0, 32.0};
  size_t num_r = sizeof(r)/sizeof(double);

  for(size_t i = 0; i < num_r; ++i) {
    double sa = -1; double vol = -1;

    calc_sphere_area_volume(r[i], &sa, &vol);
    
  }

  return;
}
