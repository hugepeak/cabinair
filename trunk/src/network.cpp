#include "network.h"

Network::Network() {

  layer_number = I_DEFAULT_LAYER_NUMBER;
  first_time = time(0);
  for( int t = 0; t < I_INITIAL_TIME_LENGTH; t++ ) {
    add_empty_cubic();
  }

}

int Network::add_empty_cubic() {

  std::vector<std::vector<std::vector<int> > > my_cubic;

  for( int l = 0; l < layer_number; l++ ) {

    std::vector<std::vector<int> > my_layer;

    for( int i = 0; i < I_X_SIZE; i++ ) {

      std::vector<int> my_row;

      for( int j = 0; j < I_Y_SIZE; j++ ) {

        my_row.push_back( 0 );

      }

      my_layer.push_back( my_row );

    }

    my_cubic.push_back( my_layer );

  }

  network.push_back( my_cubic );

  return 1;

}

