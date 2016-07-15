#include <boost/lexical_cast.hpp>
#include "car.h"
#include "network.h"
#include "evolve.h"

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

    if( evolve_car( my_network, mycar, first_network_time ) == 0 ) {
      exit( EXIT_FAILURE );
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

  std::string sx_start, sx_end, sy_start, sy_end;
  double x_start, x_end, y_start, y_end;

  while( true ) {

    std::cout << std::endl << "input x_start y_start x_end y_end (in meters): ";
    std::cin >> sx_start >> sy_start >> sx_end >> sy_end;
  
    try {
      x_start = boost::lexical_cast<double>( sx_start );
    } 
    catch( boost::bad_lexical_cast& e ) {
      std::cout << "x_start must be a number!" << std::endl;
      continue;
    }

    try {
      y_start = boost::lexical_cast<double>( sy_start );
    } 
    catch( boost::bad_lexical_cast& e ) {
      std::cout << "y_start must be a number!" << std::endl;
      continue;
    }

    try {
      x_end = boost::lexical_cast<double>( sx_end );
    } 
    catch( boost::bad_lexical_cast& e ) {
      std::cout << "x_end must be a number!" << std::endl;
      continue;
    }

    try {
      y_end = boost::lexical_cast<double>( sy_end );
    } 
    catch( boost::bad_lexical_cast& e ) {
      std::cout << "y_end must be a number!" << std::endl;
      continue;
    }

    double x_max = D_X_MIN + I_X_SIZE * D_X_GRID_LENGTH;
    double y_max = D_Y_MIN + I_Y_SIZE * D_Y_GRID_LENGTH;

    if( 
      x_start < D_X_MIN || y_start < D_Y_MIN || x_end < D_X_MIN || 
      y_end < D_Y_MIN || x_start > x_max || y_start > y_max ||
      x_end > x_max || y_end > y_max
    ) {
      std::cout << "location out of range!" << std::endl;
      continue;
    }

    break;

  }

  //============================================================================
  // Intialize mycar.
  //============================================================================

  Car * mycar = new Car( i_id, x_start, y_start, x_end, y_end );

  return mycar;

}
