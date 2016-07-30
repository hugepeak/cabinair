#include <fstream>
#include <sstream>
#include <boost/foreach.hpp>
#include "car.h"
#include "network.h"
#include "evolve.h"

#define F_INPUT  "../data_pub/example.txt"
#define F_OUTPUT "../data_pub/output.txt" 

int main()
{

  //============================================================================
  // Initialize network.
  //============================================================================

  Network * mynet = new Network();

  mynet->openOutputFile( F_OUTPUT );

  if( !mynet->isOutputFileOpen() ) {
    std::cout << "Unable to open output file!" << std::endl;
    exit( EXIT_FAILURE );
  }

  std::cout << "Current network size: " << mynet->getNetworkSize() << std::endl;

  //============================================================================
  // Evolve.
  //============================================================================

  std::ifstream myfile( F_INPUT );

  if( myfile.is_open() ) {

    std::string line;

    while( getline( myfile, line ) ) {

      if( line == "end" ) {
        std::cout << "Last car finished! Exit." << std::endl;
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

      my_wait();

    }

  }
  else {

    std::cout << "Cannot open data!" << std::endl;
    exit( EXIT_FAILURE );

  }

  mynet->outputNetwork();
  mynet->closeOutputFile();
  delete mynet;

  return 0;

}
