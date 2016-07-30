////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Tianhong Yu.
//
// This file is originally written by Tianhong Yu.
//
// This is a private software. Copyright reserved.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \file
//! \brief A header file for class Network.
//!
////////////////////////////////////////////////////////////////////////////////

#ifndef CIA_NETWORK_H
#define CIA_NETWORK_H

#include <vector>
#include <list>
#include <queue>
#include <ctime>
#include <fstream>
#include <boost/array.hpp>

#define I_X_SIZE                200    // default x grid number
#define I_Y_SIZE                200    // default y grid number
#define I_Z_SIZE                10     // default z grid number
#define I_INITIAL_TIME_LENGTH   100    // initial time in network in seconds
#define D_X_GRID_LENGTH         10.    // x grid length in meters
#define D_Y_GRID_LENGTH         10.    // y grid length in meters
#define D_X_MIN                 0.     // min x in meters, should be unsigned
#define D_Y_MIN                 0.     // min y in meters, should be unsigned

typedef
  std::list<
    boost::array<
      boost::array<
        boost::array<int,I_Z_SIZE>,I_Y_SIZE
      >,I_X_SIZE
    >
  > network_t;
typedef
  std::list<
    boost::array<
      boost::array<
        boost::array<int,I_Z_SIZE>,I_Y_SIZE
      >,I_X_SIZE
    >
  >::iterator network_it_t;
typedef
  boost::array<
    boost::array<
      boost::array<int,I_Z_SIZE>,I_Y_SIZE
    >,I_X_SIZE
  > cube_t;

/*//////////////////////////////////////////////////////////////////////////////
* Class Network.
*///////////////////////////////////////////////////////////////////////////////

class Network {

private:

  size_t x_size;
  size_t y_size;
  size_t z_size;

  double x_grid_length;
  double y_grid_length;
  double x_min;
  double y_min;

  time_t first_time;

  std::vector<int> car_numbers;
  std::queue<size_t> min_car_queue;
  int min_car_number;
  size_t min_car_z;
  int z_changing_number;

  network_t network;
  std::ofstream output_file;

public:

  Network();

  void setXSize( size_t _x_size ) { x_size = _x_size; }
  size_t getXSize() { return x_size; }
  void setYSize( size_t _y_size ) { y_size = _y_size; }
  size_t getYSize() { return y_size; }
  void setZSize( size_t _z_size ) { z_size = _z_size; }
  size_t getZSize() { return z_size; }

  void setXGridLength( double value ) { x_grid_length = value; }
  double getXGridLength() { return x_grid_length; }
  void setYGridLength( double value ) { y_grid_length = value; }
  double getYGridLength() { return y_grid_length; }
  void setXMin( double _x_min ) { x_min = _x_min; }
  double getXMin() { return x_min; }
  void setYMin( double _y_min ) { y_min = _y_min; }
  double getYMin() { return y_min; }

  void setFirstTime( time_t _first_time ) { first_time = _first_time; }
  time_t getFirstTime() { return first_time; }

  int getCarNumberInZ( size_t z ) { return car_numbers[z]; }
  size_t getMinCarZ() { return min_car_z; }
  void updateMinCarQueue();
  void updateMinCarQueue( size_t );
  void addCarInZ( size_t );
  void deleteCarInZ();
  void addZChangingNumber() { z_changing_number++; }

  void addEmptyCubeToNetwork();

  size_t getNetworkSize() { return network.size(); }

  network_it_t getNetworkBegin() { return network.begin(); }
  network_it_t getNetworkEnd() { return network.end(); }
  cube_t getNetworkBack() { return network.back(); }
  int getNetworkElement( 
    network_it_t it,
    size_t x_coord, 
    size_t y_coord,
    size_t z_coord 
  ) {
    return (*it)[x_coord][y_coord][z_coord]; 
  }
  void setNetworkElement( 
    network_it_t it,
    size_t x_coord, 
    size_t y_coord,
    size_t z_coord, 
    int value
  ) {
    (*it)[x_coord][y_coord][z_coord] = value;
  }
  void setNetworkLastTimeElement( 
    size_t x_coord, 
    size_t y_coord,
    size_t z_coord, 
    int value
  ) {
    network.back()[x_coord][y_coord][z_coord] = value;
  }

  void popNetworkFront() { network.pop_front(); }
  void openOutputFile( std::string );
  bool isOutputFileOpen();
  void closeOutputFile();
  void outputNetwork();
  void outputNetworkFront();

};

#endif // CIA_NETWORK_H
