#include <fstream>
#include <sstream>
#include <boost/foreach.hpp>
#include "car.h"
#include "network.h"
#include "evolve.h"

int main()
{

  //============================================================================
  // Initialize network.
  //============================================================================

  Network * mynet = new Network();

  std::cout << "Current network size: " << mynet->getSize() << std::endl;

  //============================================================================
  // Evolve.
  //============================================================================

  std::ifstream myfile( "../data_pub/example.txt" );

  if( myfile.is_open() ) {

    std::string line;

    while( getline( myfile, line ) ) {

      if( line == "end" ) {
        std::cout << "Last car finished! Exit." << std::endl;
        exit( EXIT_SUCCESS );
      }

      Car * mycar = createCarFromInputLine( line );

      if( mycar == NULL ) {
        std::cout << "Exit." << std::endl;
        exit( EXIT_FAILURE );
      }
  
      if( evolve_car( mynet, mycar ) == 0 ) {
        exit( EXIT_FAILURE );
      }
  
      std::cout << "Current network size: " << mynet->getSize() << std::endl;
  
      //mycar->writeOutput();
      delete mycar;

    }

  }
  else {

    std::cout << "Cannot open data!" << std::endl;
    exit( EXIT_FAILURE );

  }

  delete mynet;

  return 0;

}
