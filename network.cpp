#include "network.h"

void initialize_network( 
  std::list<std::vector<std::vector<std::vector<bool> > > > &my_network
) {

  // Whole network

  for( int t = 0; t < I_INITIAL_TIME_LENGTH; t++ ) {

    // Each cubic at one time step
    std::vector<std::vector<std::vector<bool> > > my_cubic;

    for( int l = 0; l < I_LAYER; l++ ) {

      // Each layer
      std::vector<std::vector<bool> > my_layer;

      for( int i = 0; i < I_X_SIZE; i++ ) {

        // Each row
        std::vector<bool> my_row;

        for( int j = 0; j < I_Y_SIZE; j++ ) {

          // Initialize as empty
          my_row.push_back( 0 );

        }

        my_layer.push_back( my_row );

      }
 
      my_cubic.push_back( my_layer );

    }

    my_network.push_back( my_cubic );

  }

}
