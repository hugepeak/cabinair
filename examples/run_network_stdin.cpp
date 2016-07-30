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

  std::cout << "Current network size: " << mynet->getNetworkSize() << std::endl;

  //============================================================================
  // Evolve.
  //============================================================================

  std::cout << std::endl << "Input format: carID xstart ystart xend yend.";
  std::cout << " Or type 'end' to exit program." << std::endl;

  std::string line;

  while( getline( std::cin, line ) ) {

    if( line == "end" ) {
      std::cout << "Last car finished!" << std::endl;
      exit( EXIT_SUCCESS );
    }

    Car * mycar = createCarFromInputLine( mynet, line );

    if( mycar == NULL ) {
      std::cout << "Exit." << std::endl;
      exit( EXIT_FAILURE );
    }

    if( evolve_car( mycar, mynet ) == 0 ) {
      exit( EXIT_FAILURE );
    }

    std::cout << "Current network size: ";
    std::cout << mynet->getNetworkSize() << std::endl;

    //mycar->writeOutput();
    delete mycar;

    std::cout << std::endl << "Input format: carID xstart ystart xend yend.";
    std::cout << " Or type 'end' to exit program." << std::endl;

  }

  delete mynet;

  return 0;

}
