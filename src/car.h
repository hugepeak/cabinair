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
//! \brief A header file for class Car.
//!
////////////////////////////////////////////////////////////////////////////////

#ifndef CIA_CAR_H
#define CIA_CAR_H

#include <iostream>
#include <math.h>
#include <ctime>
#include <list>
#include <vector>
#include <string>

#define DEFAULT_VELOCITY 10       // default velocity (m/s)

//##############################################################################
// Typedefs.
//##############################################################################

class Car {

private:

  // id
  time_t car_index;
  int car_id;

  // time
  int date;
  time_t time_start;
  time_t time_end;
  time_t duration;
  
  // position(meter)
  int layer;      // layer index 
  double x_start;
  double y_start;
  double x_end;
  double y_end;

  // velocities(m/s)
  double velocity;
  double vx;
  double vy;

public:

  // constructor
  Car();
  Car( int, double, double, double, double );

  // id
  int getCarIndex() { return car_index; }
  int getCarID() { return car_id; }
  
  // time operations
  int getDate() { return date; } 
  time_t getTimeStart() { return time_start; }
  time_t getTimeEnd() { return time_end; }
  time_t getDuration() { return duration; }

  // position operations
  void setLayer( int l ) { layer = l; }
  int getLayer() { return layer; }
  double getXStart() { return x_start; }
  double getYStart() { return y_start; }
  double getXEnd() { return x_end; }
  double getYEnd() { return y_end; }

  // velocity
  void setVelocity( double );
  double getVelocity() { return velocity; }
  double getVX() { return vx; }
  double getVY() { return vy; }

};

double computeVX( 
  double, double, double, double, double
);

double computeVY( 
  double, double, double, double, double
);

#endif // CIA_CAR_H
