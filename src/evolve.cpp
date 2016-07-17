#include "evolve.h"

int evolve_car( 
  Network * mynet,
  Car * mycar
) {

  network_it_t it = mynet->getNetworkBegin();

  time_t t_start = mycar->getTimeStart();
  time_t t_cursor = t_start;
  time_t t_end = mycar->getTimeEnd();
  double x_start = mycar->getXStart();
  double y_start = mycar->getYStart();
  double vx = mycar->getVX();
  double vy = mycar->getVY();
  size_t car_layer = mycar->getLayer();
  int car_id = mycar->getCarID();

  std::cout << std::endl;
  std::cout << "New car! ID: " << car_id << std::endl;
  std::cout << "x_start: " << x_start << " y_start: " << y_start << std::endl;
  std::cout << "x_end: " << mycar->getXEnd();
  std::cout << " y_end: " << mycar->getYEnd() << std::endl;
  std::cout << "Duration(s): " << mycar->getDuration() << std::endl;

  while( t_cursor <= t_end && it != mynet->getNetworkEnd() ) {

    //==========================================================================
    // Check if the car has a later time than the first time in network.
    // If so, pop out the past cubes and continue to next time step. 
    //==========================================================================

    if( t_start > mynet->getFirstTime() ) {

      it++;
      mynet->writeOutput();
      mynet->popFront();
      mynet->setFirstTime( mynet->getFirstTime() + 1 );
      continue;

    } 

    //==========================================================================
    // Check if the car's position is already taken.
    // If so, change to the next layer with the same time and check.
    // If not, mark it with the car's ID.
    //==========================================================================

    size_t xgrid = 
      size_t(
        ( x_start + vx * ( t_cursor - t_start ) ) / D_X_GRID_LENGTH
      );
    size_t ygrid = 
      size_t(
        ( y_start + vy * ( t_cursor - t_start ) ) / D_Y_GRID_LENGTH
    );

    if( mynet->getElement( it, car_layer, xgrid, ygrid ) == 0 ) {

      mynet->setElement( it, car_layer, xgrid, ygrid, car_id );

    } else {

      if( car_layer == mynet->getLayerNumber() - 1 ) {
        std::cout << "Out of layers!" << std::endl;
        return 0;
      }

      car_layer++;
      mycar->setLayer( car_layer );
      continue;

    }

    std::cout << "time: " << t_cursor << " x: " << std::setw(3) << xgrid;
    std::cout << " y: " << std::setw(3) << ygrid;
    std::cout << " z: " << car_layer << " carID: " << car_id;
    std::cout << std::endl;

    t_cursor++;
    it++;

  }

  //============================================================================
  // Check if the car's time is beyond the last time in network.
  // If so, initialize new cubes of the rest of car's times into the network.
  //============================================================================

  if( it == mynet->getNetworkEnd() ) {

    for( ; t_cursor <= t_end; t_cursor++ ) {

      mynet->add_empty_cube();

      size_t xgrid = 
        size_t(
        ( x_start + vx * ( t_cursor - t_start ) ) / D_X_GRID_LENGTH
      );
      size_t ygrid = 
        size_t(
        ( y_start + vy * ( t_cursor - t_start ) ) / D_Y_GRID_LENGTH
      );
  
      mynet->setLastElement( car_layer, xgrid, ygrid, car_id );

      std::cout << "Added cube to network!" << std::endl;
      std::cout << "time: " << t_cursor << " x: " << xgrid << " y: " << ygrid;
      std::cout << " z: " << car_layer << " carID: " << car_id;
      std::cout << std::endl;

    }

  }

  return 1;

}

Car * createCarFromInputLine( std::string line ) {

  std::istringstream iss( line );
  std::string s_sub;
  std::vector<std::string> vs_inputs;

  while( iss ) {
    iss >> s_sub;
    vs_inputs.push_back( s_sub );
  }
  // pop the "\n" at the end.
  vs_inputs.pop_back();

  if( vs_inputs.size() != 5 ) {
    std::cout << "Input format: carID xstart ystart xend yend";
    std::cout << std::endl;
    return NULL;
  }

  int i_id;

  try {
    i_id = boost::lexical_cast<int>( vs_inputs[0] );
  } 
  catch( boost::bad_lexical_cast& e ) {
    std::cout << "Car ID must be an integer!" << std::endl;
    return NULL;
  }
  if( i_id <= 0 ) {
    std::cout << "Car ID must be a positive integer!" << std::endl;
    return NULL;
  }

  double d_x_max = D_X_MIN + I_X_SIZE * D_X_GRID_LENGTH;
  double d_y_max = D_Y_MIN + I_Y_SIZE * D_Y_GRID_LENGTH;
  std::vector<double> vd_loc;
  double d_location;

  for( size_t i = 1; i < vs_inputs.size(); i++ ) {

    try {
      d_location = boost::lexical_cast<double>( vs_inputs[i] );
    } 
    catch( boost::bad_lexical_cast& e ) {
      std::cout << "Location must be a number!" << std::endl;
      continue;
    }

    double d_min = ( i % 2 == 0 ) ? D_Y_MIN : D_X_MIN;
    double d_max = ( i % 2 == 0 ) ? d_y_max : d_x_max;

    if( d_location < d_min || d_location > d_max ) {
      std::cout << "location out of range:" << d_location << std::endl;
      return NULL;
    }

    vd_loc.push_back( d_location );

  }

  Car * mycar = new Car( i_id, vd_loc[0], vd_loc[1], vd_loc[2], vd_loc[3] );

  return mycar;

}

