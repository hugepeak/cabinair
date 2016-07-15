#include <boost/lexical_cast.hpp>
#include "car.h"
#include "network.h"

char* printTime( time_t t ) {

  return ctime( &t );

}

Car * readinput(void);

int main()
{

  //============================================================================
  // Save first time in the current network.
  //============================================================================

  time_t first_network_time = time(0);

  //============================================================================
  // Initialize network.
  //============================================================================

  std::list<std::vector<std::vector<std::vector<int> > > > my_network;

  initialize_network( my_network );

  std::cout << "Current network size: " << my_network.size() << std::endl;

  //============================================================================
  // Evolve.
  //============================================================================

  while( true ) {

    //==========================================================================
    // Get new coming cars until break.
    //==========================================================================

    Car * mycar = readinput();

    if( mycar == NULL ) {
      std::cout << "last car finished." << std::endl;
      exit( EXIT_SUCCESS );
    }

    std::list<std::vector<std::vector<std::vector<int> > > >::iterator it = 
      my_network.begin();
  
    time_t t_start = mycar->getTimeStart();
    time_t t_cursor = t_start;
    time_t t_end = mycar->getTimeEnd();
    double x_start = mycar->getXStart();
    double y_start = mycar->getYStart();
    double vx = mycar->getVX();
    double vy = mycar->getVY();
    int layer = mycar->getLayer();
    int car_id = mycar->getCarID();
  
    while( t_cursor <= t_end && it != my_network.end() ) {
  
      //========================================================================
      // Check if the car has a later time than the first time in network.
      // If so, pop out the past cubics and continue to next time step. 
      //========================================================================
  
      if( t_start > first_network_time ) {
  
        first_network_time++;
        it++;
        my_network.pop_front();
        continue;
  
      } 
  
      //========================================================================
      // Check if the car's position is already taken.
      // If so, change to the next layer with the same time and check.
      // If not, mark it with the car's ID.
      //========================================================================
  
      int xgrid = 
        floor( ( x_start + vx * ( t_cursor - t_start ) ) / I_GRID_LENGTH );
      int ygrid = 
        floor( ( y_start + vy * ( t_cursor - t_start ) ) / I_GRID_LENGTH );
  
      if( (*it)[layer][xgrid][ygrid] == 0 ) {
  
        (*it)[layer][xgrid][ygrid] = car_id;
  
      } else {
  
        if( layer == I_LAYER - 1 ) {
          std::cout << "out of layers" << std::endl;
          exit( EXIT_FAILURE );
        }
  
        layer++;
        mycar->setLayer( layer );
        continue;
  
      }
  
      std::cout << "time: " << t_cursor << " x: " << xgrid << " y: " << ygrid;
      std::cout << std::endl;
  
      t_cursor++;
      it++;
  
    }
  
    //==========================================================================
    // Check if the car's time is beyond the last time in network.
    // If so, initialize new cubics of the rest of car's times into the network.
    //==========================================================================
  
    if( it == my_network.end() ) {

      for( ; t_cursor <= t_end; t_cursor++ ) {
 
        add_empty_cubic_to_network( my_network );

        int xgrid = 
          floor( ( x_start + vx * ( t_cursor - t_start ) ) / I_GRID_LENGTH );
        int ygrid = 
          floor( ( y_start + vy * ( t_cursor - t_start ) ) / I_GRID_LENGTH );
    
        my_network.back()[layer][xgrid][ygrid] = car_id;

        std::cout << "add cubic to network" << std::endl;
        std::cout << "time: " << t_cursor << " x: " << xgrid << " y: " << ygrid;
        std::cout << std::endl;
  
      }
  
    }
  
    std::cout << "Current network size: " << my_network.size() << std::endl;

    delete mycar;

  }

  return 0;

}

Car * readinput(void) { 

  //============================================================================
  // Get car ID.
  //============================================================================
  
  std::string s_id;
  int i_id;

  while( true ) {

    std::cout << 
      "input car ID to start a new trip or type 'end' to exit program: ";
    std::cin >> s_id;

    if( s_id == "end" ) {
      return NULL;
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

  //============================================================================
  // Get start and end locations.
  //============================================================================

  double x_start, x_end, y_start, y_end;

  std::cout << std::endl << "input x_start y_start x_end y_end: ";
  std::cin >> x_start >> y_start >> x_end >> y_end;

         // Check input here. Need to be implemented.

  //============================================================================
  // Intialize mycar.
  //============================================================================

  Car * mycar = new Car( i_id, x_start, y_start, x_end, y_end );

  return mycar;

}
