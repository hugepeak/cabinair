#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <boost/lexical_cast.hpp>
#include "network.h"

#define CAR_NUMBER   100
#define OUTPUT_FILE  "../data_pub/example.txt"

int main( int argc, char ** argv )
{

  if( argc != 2 ) {
    std::cout << "Usage: generate_car_data car_number" << std::endl;
    exit( EXIT_FAILURE );
  }

  int i_car_number = boost::lexical_cast<int>( argv[1] ); 

  std::ofstream myfile( OUTPUT_FILE );

  int i_x_range = int( I_X_SIZE * D_X_GRID_LENGTH );
  int i_y_range = int( I_Y_SIZE * D_Y_GRID_LENGTH );
  int i_x_min = int( D_X_MIN );
  int i_y_min = int( D_Y_MIN );

  if( myfile.is_open() ) {

    for( int i = 1; i <= i_car_number; i++ ) {
      myfile << i << " ";
      myfile << rand() % i_x_range + i_x_min << " ";
      myfile << rand() % i_y_range + i_y_min << " ";
      myfile << rand() % i_x_range + i_x_min << " ";
      myfile << rand() % i_y_range + i_x_min << std::endl;
    }

  } else {

    std::cout << "Unable to open file!" << std::endl;

  }

  return 0;

}
