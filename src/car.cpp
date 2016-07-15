#include "car.h"

Car::Car(
  int _car_id, double _x_start, double _y_start, double _x_end, double _y_end
) {

  time_start = time(0);
  car_id = _car_id;
  car_index = time_t(car_id * 1e12) + time_start;
  date = 0;
  layer = 0;
  x_start = _x_start;
  y_start = _y_start;
  x_end = _x_end;
  y_end = _y_end;
  velocity = DEFAULT_VELOCITY;
  vx = computeVX( velocity, x_start, y_start, x_end, y_end );
  vy = computeVY( velocity, x_start, y_start, x_end, y_end );
  duration = 
    time_t(
      sqrt( pow( y_end - y_start, 2. ) + pow( x_end - x_start, 2. ) )
        / velocity
    );
  time_end = 
    time_start + duration;

}

Car::Car() {

  time_start = 0.;
  car_id = 0;
  car_index = 0;
  date = 0;
  layer = 0;
  x_start = 0.;
  x_end = 0.;
  y_start = 0.;
  y_end = 0.;
  velocity = 10.;
  vx = 0.;
  vy = 0.;
  duration = 0.;
  time_end = 0;

}

void Car::setVelocity( double _velocity ) { 

  velocity = _velocity;

  vx = computeVX( velocity, x_start, y_start, x_end, y_end );
  vy = computeVY( velocity, x_start, y_start, x_end, y_end );

}

double computeVX( 
  double velocity, double x_start, double y_start, double x_end, double y_end
) {

  return
    velocity *
    ( x_end - x_start ) /
    sqrt( pow( y_end - y_start, 2 ) + pow( x_end - x_start, 2 ) );

}

double computeVY( 
  double velocity, double x_start, double y_start, double x_end, double y_end
) {

  return
    velocity *
    ( y_end - y_start ) /
    sqrt( pow( y_end - y_start, 2 ) + pow( x_end - x_start, 2 ) );

}
