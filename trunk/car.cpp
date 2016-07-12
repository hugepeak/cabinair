#include "car.h"

Car::Car() {

  car_index = 0;
  car_id = 0;
  date = 0;
  time_start = 0.;
  layer = 0;
  x_start = 0.;
  x_end = 0.;
  y_start = 0.;
  y_end = 0.;
  velocity = 10.;

}

Car::Car(
  time_t index, double x1, double y1, double x2, double y2
) {

  time_start = time(0);
  car_index = index;
  car_id = index * 1e12 + time_start;
  date = 0;
  layer = 0;
  x_start = x1;
  y_start = y1;
  x_end = x2;
  y_end = y2;
  velocity = 20;
  duration = 
    sqrt( pow( y_end - y_start, 2 ) + pow( x_end - x_start, 2 ) )
      / velocity;
  time_end = 
    time_start + duration;

}

void Car::setVelocity( double _velocity ) { 

  velocity = _velocity;

  vx = 
    velocity *
    ( x_end - x_start ) /
    sqrt( pow( y_end - y_start, 2 ) + pow( x_end - x_start, 2 ) );

  vy = 
    velocity *
    ( y_end - y_start ) /
    sqrt( pow( y_end - y_start, 2 ) + pow( x_end - x_start, 2 ) );

}
