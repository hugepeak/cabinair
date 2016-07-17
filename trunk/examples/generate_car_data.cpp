#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "network.h"

#define CAR_NUMBER   10000

int main()
{

  std::ofstream myfile( "../data_pub/example.txt" ); 

  int i_x_range = int( I_X_SIZE * D_X_GRID_LENGTH );
  int i_y_range = int( I_Y_SIZE * D_Y_GRID_LENGTH );
  int i_x_min = int( D_X_MIN );
  int i_y_min = int( D_Y_MIN );

  if( myfile.is_open() ) {

    for( int i = 1; i <= CAR_NUMBER; i++ ) {
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
