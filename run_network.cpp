#include <boost/lexical_cast.hpp>
#include "car.h"
#include "network.h"

char* printTime( time_t t ) {

  return ctime( &t );

}

int main()
{

  //============================================================================
  // Save first time.
  //============================================================================

  time_t first_time = time(0);

  //============================================================================
  // Initialize network.
  //============================================================================

  std::list<std::vector<std::vector<std::vector<int> > > > my_network;

  initialize_network( my_network );

  //============================================================================
  // Get new coming cars until break.
  //============================================================================

  while( true ) {

    //==========================================================================
    // Get car ID.
    //==========================================================================
    
    std::string s_id;
    int i_id;

    while( true ) {

      std::cout << 
        "input car ID to start a new trip or type 'end' to exit program: ";
      std::cin >> s_id;

      if( s_id == "end" ) {
        std::cout << "last car finished." << std::endl;
        exit( EXIT_SUCCESS );
      } 

      try {
        i_id = boost::lexical_cast<int>( s_id );
      } 
      catch( boost::bad_lexical_cast& e ) {
        std::cout << "Car ID must be an integer!" << std::endl;
        continue;
      }

      break;

    }
  
    //==========================================================================
    // Get start and end locations.
    //==========================================================================

    double x_start, x_end, y_start, y_end;

    std::cout << std::endl << "input x_start y_start x_end y_end: ";
    std::cin >> x_start >> y_start >> x_end >> y_end;

           // Check input here. Need to be implemented.

    //==========================================================================
    // Intialize mycar.
    //==========================================================================

    //Car mycar( 0, 0, 0, 300, 400 );
    Car mycar( i_id, x_start, y_start, x_end, y_end );

    std::list<std::vector<std::vector<std::vector<int> > > >::iterator it = 
      my_network.begin();
  
    time_t cursor = mycar.getTimeStart();
    time_t t0 = mycar.getTimeStart();
    double x0 = mycar.getXStart();
    double y0 = mycar.getYStart();
    double vx = mycar.getVX();
    double vy = mycar.getVY();
    int layer = mycar.getLayer();
    int car_id = mycar.getCarID();
  
    while( cursor <= mycar.getTimeEnd() && it != my_network.end() ) {
  
      //========================================================================
      // Check if the car has a later time than the first time in network.
      // If so, pop out the past cubics and continue to next time step. 
      //========================================================================
  
      if( cursor > first_time ) {
  
        first_time++;
        it++;
        my_network.pop_front();
        continue;
  
      } 
  
      //========================================================================
      // Check if the car's position is already taken.
      // If so, change to the next layer with the same time and check.
      // If not, mark it with the car's ID.
      //========================================================================
  
      int xgrid = floor( ( x0 + vx * ( cursor - t0 ) ) / I_GRID_LENGTH );
      int ygrid = floor( ( y0 + vy * ( cursor - t0 ) ) / I_GRID_LENGTH );
  
      if( (*it)[layer][xgrid][ygrid] == 0 ) {
  
        (*it)[layer][xgrid][ygrid] = car_id;
  
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
  
    //==========================================================================
    // Check if the car's time is beyond the last time in network.
    // If so, initialize a new cubic into the network. 
    //==========================================================================
  
    if( it == my_network.end() ) {
  
          // need implement

      std::cout << "end" << std::endl;
  
    }
  
    std::cout << "Current time slices: " << my_network.size() << std::endl;

  }

  return 1;

}
