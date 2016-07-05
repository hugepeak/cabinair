#include<iostream>
#include<math.h>
#include<ctime>
#include<list>
#include<vector>
#include<string>

#include"utilities.h"

using namespace std;

#define I_X_SIZE                100    // x grid number
#define I_Y_SIZE                100    // y grid number
#define I_LAYER                 10     // layer number
#define I_INITIAL_TIME_LENGTH   100    // seconds
#define I_GRID_LENGTH           100    // meters

class Car {

private:

  // id
  time_t car_index;
  time_t car_id;

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
  Car( time_t, double, double, double, double );

  // id
  void setCarIndex( int i ) { car_index = i; }
  int getCarIndex() { return car_index; }
  void setCarID( time_t i ) { car_id = i; }
  time_t getCarID() { return car_id; }
  
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
  double getXStart() { return x_start; }
  double getYStart() { return y_start; }
  double getXEnd() { return x_end; }
  double getYEnd() { return y_end; }

  // velocity
  void setVelocity( double v ) { velocity = v; }
  double getVelocity() { return velocity; }
  void computeVXY();
  double getVX() { return vx; }
  double getVY() { return vy; }

};

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

  // last time

  time_t first_time = time(0);

  // Initialize network

  list<vector<vector<vector<bool> > > > my_network;

  initialize_network( my_network );
  cout << "Initial time slices: " << my_network.size() << endl;

  while( true ) {

    string id;
    double x_start, x_end, y_start, y_end;

    cout << "input car ID to start a new trip or type 'end' to exit program: ";
    cin >> id;
    if( id == "end" ) {
      cout << "last car finished." << endl;
      exit( EXIT_SUCCESS );
    } 
  
    cout << endl << "input x_start y_start x_end y_end: ";
    cin >> x_start >> y_start >> x_end >> y_end;

    // Car info

    Car mycar( 0, 0, 0, 300, 400 );
    mycar.computeTimeEnd();
    mycar.computeVXY();

    list<vector<vector<vector<bool> > > >::iterator it = my_network.begin();
  
    time_t cursor = mycar.getTimeStart();
    int t0 = mycar.getTimeStart();
    double x0 = mycar.getXStart();
    double y0 = mycar.getYStart();
    double vx = mycar.getVX();
    double vy = mycar.getVY();
    int layer = mycar.getLayer();
  
    while( cursor <= mycar.getTimeEnd() && it != my_network.end() ) {
  
      // Check if the car has a later time than the first time in network.
      // If so, pop out the older cubics and continue to next time step. 
      // If not, continue.
  
      if( cursor > first_time ) {
  
        first_time++;
        it++;
        my_network.pop_front();
        continue;
  
      } 
  
      // Check if the car's position is already taken.
      // If so, change to the next layer with the same time and check.
      // If not, mark it as taken.
  
      int xgrid = ( x0 + vx * ( cursor - t0 ) ) / I_GRID_LENGTH;
      int ygrid = ( y0 + vy * ( cursor - t0 ) ) / I_GRID_LENGTH;
  
      if( (*it)[layer][xgrid][ygrid] == 0 ) {
  
        (*it)[layer][xgrid][ygrid] = 1;
  
      } else {
  
        if( layer == I_LAYER - 1 ) {
          cout << "out of layers" << endl;
          exit( EXIT_FAILURE );
        }
  
        layer++;
        mycar.setLayer( layer );
        continue;
  
      }
  
      cout << "time: " << cursor << " x: " << xgrid << " y: " << ygrid << endl;
  
      cursor++;
      it++;
  
    }
  
    // Check if the car's time is beyond the last time in network.
    // If so, initialize a new cubic into the network. 
  
    if( it == my_network.end() ) {
  
      // need implement
      cout << "end" << endl;
  
    }
  
    cout << "Current time slices: " << my_network.size() << endl;

  }

  return 1;

}

void initialize_network( 
  list<vector<vector<vector<bool> > > > &my_network
) {

  // Whole network

  for( int t = 0; t < I_INITIAL_TIME_LENGTH; t++ ) {

    // Each cubic at one time step
    vector<vector<vector<bool> > > my_cubic;

    for( int l = 0; l < I_LAYER; l++ ) {

      // Each layer
      vector<vector<bool> > my_layer;

      for( int i = 0; i < I_X_SIZE; i++ ) {

        // Each row
        vector<bool> my_row;

        for( int j = 0; j < I_Y_SIZE; j++ ) {

          // Initialize as empty
          my_row.push_back( 0 );

        }

        my_layer.push_back( my_row );

      }
 
      my_cubic.push_back( my_layer );

    }

    my_network.push_back( my_cubic );

  }

}
