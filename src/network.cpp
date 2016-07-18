#include "network.h"

Network::Network() {

  x_size = I_X_SIZE;
  y_size = I_Y_SIZE;
  z_size = I_Z_SIZE;

  first_time = time(0);

  for( int t = 0; t < I_INITIAL_TIME_LENGTH; t++ ) {
    addEmptyCubeToNetwork();
  }

}

void Network::addEmptyCubeToNetwork() {

  cube_t my_cube;

  for( size_t i = 0; i < x_size; i++ ) {
    for( size_t j = 0; j < y_size; j++ ) {
      for( size_t k = 0; k < z_size; k++ ) {
        my_cube[i][j][k] = 0;
      }
    }
  }

  network.push_back( my_cube );

}

void Network::openOutputFile( std::string file ) {

  output_file.open( file );

  if( isOutputFileOpen() ) {

    output_file << x_size << " " << y_size << " " << z_size << std::endl;

  }

}

bool Network::isOutputFileOpen() {

  return output_file.is_open();

}

void Network::closeOutputFile() {

  output_file.close();

}

void Network::outputNetwork() {

  while( !network.empty() ) {

    outputNetworkFront();
    popNetworkFront();
    first_time++;

  }

}

void Network::outputNetworkFront() {

  output_file << "NewTime: " << getFirstTime() << std::endl;

  for( size_t i = 0; i < x_size; i++ ) {

    for( size_t j = 0; j < y_size; j++ ) {

      for( size_t k = 0; k < z_size; k++ ) {

        if( network.front()[i][j][k] != 0 ) {

          output_file << i << " " << j << " " << k << " " <<
            network.front()[i][j][k] << std::endl;

        }

      }

    }

  }

}
