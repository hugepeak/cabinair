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
#include <ctime>
#include <boost/array.hpp>

#define I_X_SIZE                200    // x grid number
#define I_Y_SIZE                200    // y grid number
#define I_LAYER                 10     // default layer number
#define I_INITIAL_TIME_LENGTH   100    // seconds
#define D_X_GRID_LENGTH         10.    // x grid length in meters
#define D_Y_GRID_LENGTH         10.    // y grid length in meters
#define D_X_MIN                 0.     // min x in meters, should be unsigned
#define D_Y_MIN                 0.     // min y in meters, should be unsigned

typedef
  std::list<
    boost::array<
      boost::array<
        boost::array<int,I_Y_SIZE>,I_X_SIZE
      >,I_LAYER
    >
  > network_t;
typedef
  std::list<
    boost::array<
      boost::array<
        boost::array<int,I_Y_SIZE>,I_X_SIZE
      >,I_LAYER
    >
  >::iterator network_it_t;
typedef
  boost::array<
    boost::array<
      boost::array<int,I_Y_SIZE>,I_X_SIZE
    >,I_LAYER
  > cube_t;

/*//////////////////////////////////////////////////////////////////////////////
* Class Network.
*///////////////////////////////////////////////////////////////////////////////

class Network {

private:

  size_t layer_number;
  time_t first_time;
  network_t network;

public:

  Network();

  void setLayer( size_t _layer_number ) { layer_number = _layer_number; }
  size_t getLayerNumber() { return layer_number; }

  void setFirstTime( time_t _first_time ) { first_time = _first_time; }
  time_t getFirstTime() { return first_time; }

  int add_empty_cube();
  size_t getSize() { return network.size(); }
  void popFront() { network.pop_front(); }

  network_it_t getNetworkBegin() { return network.begin(); }
  network_it_t getNetworkEnd() { return network.end(); }
  cube_t getNetworkBack() { return network.back(); }
  int getElement( 
    network_it_t it,
    size_t layer, 
    size_t xgrid, 
    size_t ygrid
  ) {
    return (*it)[layer][xgrid][ygrid]; 
  }
  void setElement( 
    network_it_t it,
    size_t layer, 
    size_t xgrid, 
    size_t ygrid,
    int value
  ) {
    (*it)[layer][xgrid][ygrid] = value;
  }
  void setLastElement( 
    size_t layer, 
    size_t xgrid, 
    size_t ygrid,
    int value
  ) {
    network.back()[layer][xgrid][ygrid] = value;
  }

  void writeOutput() {};

};

#endif // CIA_NETWORK_H
