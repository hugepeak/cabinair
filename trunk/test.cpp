#include<iostream>
#include<math.h>
#include<ctime>
#include<list>
#include<vector>

using namespace std;

class Car {

private:

  // time
  int date;
  time_t time_start;
  time_t time_end;
  time_t duration;
  
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
  Car( double, double, double, double );
  
  // time operations
  void setDate( int d ) { date = d; }
  int getDate() { return date; } 
  void setTimeStart( time_t t ) { time_start = t; }
  time_t getTimeStart() { return time_start; }
  void setTimeEnd( time_t t ) { time_end = t; }
  void computeTimeEnd() { 
    duration = 
      sqrt( pow( y_end - y_start, 2 ) + pow( x_end - x_start, 2 ) )
        / velocity;
    time_end = 
      time_start + duration;
  }
  time_t getTimeEnd() { return time_end; }
  time_t getDuration() { return duration; }

  // position operations
  void setLayer( int l ) { layer = l; }
  int getLayer() { return layer; }
  void setXStart( double x ) { x_start = x; } 
  void setYStart( double x ) { y_start = x; } 
  void setXEnd( double x ) { x_end = x; } 
  void setYEnd( double x ) { y_end = x; } 

  // velocity
  void setVelocity( double v ) { velocity = v; }
  double getVelocity() { return velocity; }
  void computeVXY();
  double getVX() { return vx; }
  double getVY() { return vy; }

};

Car::Car() {

  date = 0;
  time_start = 0.;
  layer = 0;
  x_start = 0.;
  x_end = 0.;
  y_start = 0.;
  y_end = 0.;
  velocity = 1.;

}

Car::Car(
  double x1, double y1, double x2, double y2
) {

  time_start = time(0);
  date = 0;
  layer = 0;
  x_start = x1;
  y_start = y1;
  x_end = x2;
  y_end = y2;
  velocity = 20;

}

void Car::computeVXY() {

  vx = 
    velocity *
    ( x_end - x_start ) /
    sqrt( pow( y_end - y_start, 2 ) + pow( x_end - x_start, 2 ) );

  vy = 
    velocity *
    ( y_end - y_start ) /
    sqrt( pow( y_end - y_start, 2 ) + pow( x_end - x_start, 2 ) );

}

char* printTime( time_t t ) {

  return ctime( &t );

}

int main()
{

  // Car info

  Car mycar( 0, 0, 300, 400 );
  mycar.computeTimeEnd();
  mycar.computeVXY();
  cout << printTime( mycar.getTimeStart() )<< endl;
  cout << printTime( mycar.getTimeEnd() )<< endl;
  cout << mycar.getDuration() << endl;
  cout << mycar.getVX() << endl;
  cout << mycar.getVY() << endl;

  // last time

  time_t prev_time = time(0);

  // Map

  const int x_size = 1000;
  const int y_size = 1000;
  vector<list<vector<vector<bool> > > > my_network;
  list<vector<vector<bool> > > my_layer;

  time_t cursor = mycar.getTimeStart();

  while( cursor < mycar.getTimeEnd() ) {

    vector<vector<bool> > my_map;
    for( int i = 0; i < x_size; i++ ) {
      vector<bool> v;
      for( int j = 0; j < y_size; j++ ) {
        v.push_back( 1 );
      }
      my_map.push_back( v );
    }
 
    my_layer.push_back( my_map );

    cursor++;

  }

  my_network.push_back( my_layer );
  cout << my_network[0].front()[0][0] << endl;
  
  return 1;

}
