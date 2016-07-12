#include "car.h"
#include "network.h"

char* printTime( time_t t ) {

  return ctime( &t );

}

int main()
{

  // last time

  time_t first_time = time(0);

  // Initialize network

  std::list<std::vector<std::vector<std::vector<bool> > > > my_network;

  initialize_network( my_network );
  std::cout << "Initial time slices: " << my_network.size() << std::endl;

  while( true ) {

    std::string id;
    double x_start, x_end, y_start, y_end;

    std::cout << 
      "input car ID to start a new trip or type 'end' to exit program: ";
    std::cin >> id;
    if( id == "end" ) {
      std::cout << "last car finished." << std::endl;
      exit( EXIT_SUCCESS );
    } 
  
    std::cout << std::endl << "input x_start y_start x_end y_end: ";
    std::cin >> x_start >> y_start >> x_end >> y_end;

    // Car info

    Car mycar( 0, 0, 0, 300, 400 );

    std::list<std::vector<std::vector<std::vector<bool> > > >::iterator it = 
      my_network.begin();
  
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
          std::cout << "out of layers" << std::endl;
          exit( EXIT_FAILURE );
        }
  
        layer++;
        mycar.setLayer( layer );
        continue;
  
      }
  
      std::cout << "time: " << cursor << " x: " << xgrid << " y: " << ygrid;
      std::cout << std::endl;
  
      cursor++;
      it++;
  
    }
  
    // Check if the car's time is beyond the last time in network.
    // If so, initialize a new cubic into the network. 
  
    if( it == my_network.end() ) {
  
      // need implement
      std::cout << "end" << std::endl;
  
    }
  
    std::cout << "Current time slices: " << my_network.size() << std::endl;

  }

  return 1;

}
