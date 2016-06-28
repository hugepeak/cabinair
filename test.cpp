#include<iostream>
#include<math.h>
#include<ctime>

using namespace std;

class Car {

private:

  // time
  int date;
  double time_start;
  double time_end;
  
  // position(meter)
  int layer;      // layer index 
  double x_start;
  double y_start;
  double x_end;
  double y_end;

  // velocities(m/s)
  double velocity;
  double vx;
  double vy;

public:

  // constructor
  Car();
  Car( int, double, double, double, double, double, double );
  
  // time
  void setDate( int d ) { date = d; }
  int getDate() { return date; } 
  void setTimeStart( double t ) { time_start = t; }
  double getTimeStart() { return time_start; }
  void setTimeEnd( double t ) { time_end = t; }
  void setTimeEnd() { 
    time_end = 
      sqrt( pow( y_end - y_start, 2 ) + pow( x_end - x_start, 2 ) ) /
      velocity;
  }
  double getTimeEnd() { return time_end; }

  // position
  void setLayer( int l ) { layer = l; }
  int getLayer() { return layer; }
  void setXStart( double x ) { x_start = x; } 
  void setYStart( double x ) { y_start = x; } 
  void setXEnd( double x ) { x_end = x; } 
  void setYEnd( double x ) { y_end = x; } 

  // velocity
  void setVelocity( double v ) { velocity = v; }
  void computeVXY();

};

Car::Car() {
  date = 0;
  time_start = 0.;
  time_end = 0.;
  x_start = 0.;
  x_end = 0.;
  y_start = 0.;
  y_end = 0.;
  velocity = 1.;
}

Car::Car(
  int d, double t,
  double x1, double y1, double x2, double y2, double v
) {
  date = d;
  time_start = t;
  x_start = x1;
  y_start = y1;
  x_end = x2;
  y_end = y2;
  velocity = v;
}

int main()
{
  Car mycar( 20160628, 100., 1, 2, 3, 4, 5 );
  mycar.setTimeEnd();
  std::cout << mycar.getTimeEnd() << std::endl;
  time_t now = time(0);
  char* dt = ctime(&now);
  cout << now << endl;
  cout << dt << endl;
  return 1;
}
