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

#define I_X_SIZE                100    // x grid number
#define I_Y_SIZE                100    // y grid number
#define I_DEFAULT_LAYER_NUMBER  10     // default layer number
#define I_INITIAL_TIME_LENGTH   100    // seconds
#define D_X_GRID_LENGTH         10.    // x grid length in meters
#define D_Y_GRID_LENGTH         10.    // y grid length in meters
#define D_X_MIN                 0.     // min x in meters
#define D_Y_MIN                 0.     // min y in meters

class Network {

private:

  int layer_number;
  time_t first_time;
  std::list<std::vector<std::vector<std::vector<int> > > > network;

public:

  Network();

  void setLayer( int _layer_number ) { layer_number = _layer_number; }
  int getLayerNumber() { return layer_number; }

  void setFirstTime( time_t _first_time ) { first_time = _first_time; }
  int getFirstTime() { return first_time; }

  std::list<std::vector<std::vector<std::vector<int> > > > getNetwork() {
    return network;
  }

  int getSize() { return network.size(); }
  int add_empty_cubic();
  void popFront() { network.pop_front(); }

  std::list<std::vector<std::vector<std::vector<int> > > >::iterator
    getNetworkBegin() { return network.begin(); }
  std::list<std::vector<std::vector<std::vector<int> > > >::iterator
    getNetworkEnd() { return network.end(); }
  std::vector<std::vector<std::vector<int> > > 
    getNetworkBack() { return network.back(); }
  int getElement( 
    std::list<std::vector<std::vector<std::vector<int> > > >::iterator it,
    int layer, 
    int xgrid, 
    int ygrid
  ) {
    return (*it)[layer][xgrid][ygrid]; 
  }
  void setElement( 
    std::list<std::vector<std::vector<std::vector<int> > > >::iterator it,
    int layer, 
    int xgrid, 
    int ygrid,
    int value
  ) {
    (*it)[layer][xgrid][ygrid] = value;
  }
  void setLastElement( 
    int layer, 
    int xgrid, 
    int ygrid,
    int value
  ) {
    network.back()[layer][xgrid][ygrid] = value;
  }

};

#endif // CIA_NETWORK_H