#include "network.h"

Network::Network() {

  layer_number = I_LAYER;

  first_time = time(0);

  for( int t = 0; t < I_INITIAL_TIME_LENGTH; t++ ) {
    add_empty_cube();
  }

}

int Network::add_empty_cube() {

  cube_t my_cube;

  for( size_t l = 0; l < layer_number; l++ ) {
    for( size_t i = 0; i < I_X_SIZE; i++ ) {
      for( size_t j = 0; j < I_Y_SIZE; j++ ) {
        my_cube[l][i][j] = 0;
      }
    }
  }

  network.push_back( my_cube );

  return 1;

}

void Network::outputFront() {

}
