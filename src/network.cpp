#include "network.h"

void initialize_network( 
  std::list<std::vector<std::vector<std::vector<int> > > > &my_network
) {

  for( int t = 0; t < I_INITIAL_TIME_LENGTH; t++ ) {

    add_empty_cubic_to_network( my_network );

  }

  return;

}

void add_empty_cubic_to_network(
  std::list<std::vector<std::vector<std::vector<int> > > > &my_network
) {

  std::vector<std::vector<std::vector<int> > > my_cubic;

  for( int l = 0; l < I_LAYER; l++ ) {

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

  my_network.push_back( my_cubic );

}

