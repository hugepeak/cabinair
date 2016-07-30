#include "evolve.h"

int evolve_car( 
  Car * mycar,
  Network * mynet
) {

  add_car_into_network( mycar, mynet );

  time_t t_start = mycar->getTimeStart();
  time_t t_cursor = t_start;
  time_t t_end = mycar->getTimeEnd();
  double x_start = mycar->getXStart();
  double y_start = mycar->getYStart();
  double vx = mycar->getVX();
  double vy = mycar->getVY();
  size_t z_coord = mycar->getZ();
  int car_id = mycar->getCarID();

  network_it_t it = mynet->getNetworkBegin();
  double x_grid_length = mynet->getXGridLength(); 
  double y_grid_length = mynet->getYGridLength(); 

  std::cout << std::endl;
  std::cout << "New car! ID: " << car_id << std::endl;
  std::cout << "x_start: " << x_start << " y_start: " << y_start << std::endl;
  std::cout << "x_end: " << mycar->getXEnd();
  std::cout << " y_end: " << mycar->getYEnd() << std::endl;
  std::cout << "Duration(s): " << mycar->getDuration() << std::endl;

  //============================================================================
  // Check if the car has a later time than the first time in network.
  // If so, pop out the past cubes and continue to next time step. 
  //============================================================================

  while( t_start > mynet->getFirstTime() && it != mynet->getNetworkEnd() ) {

    it++;
    mynet->outputNetworkFront();
    mynet->popNetworkFront();
    mynet->setFirstTime( mynet->getFirstTime() + 1 );

  } 

  //============================================================================
  // Evolve until the car finishes the trip or hits the network end.
  //============================================================================

  while( t_cursor <= t_end && it != mynet->getNetworkEnd() ) {

    //==========================================================================
    // Check if the car's position is already taken.
    // If so, change to the next layer with the same time and check.
    // If not, mark it with the car's ID.
    //==========================================================================

    size_t x_coord = 
      size_t(
        ( x_start + vx * ( t_cursor - t_start ) ) / x_grid_length
      );
    size_t y_coord = 
      size_t(
        ( y_start + vy * ( t_cursor - t_start ) ) / y_grid_length
    );

    while( mynet->getNetworkElement( it, x_coord, y_coord, z_coord ) != 0 ) {

      if( move_car( mycar, mynet ) == 0 ) {

        std::cout << "Failed to move car" << std::endl;
        return 0;

      }

      z_coord = mycar->getZ();

    }

    mynet->setNetworkElement( it, x_coord, y_coord, z_coord, car_id );

    std::cout << "time: " << t_cursor << " x: " << std::setw(3) << x_coord;
    std::cout << " y: " << std::setw(3) << y_coord;
    std::cout << " z: " << z_coord << " carID: " << car_id;
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

      mynet->addEmptyCubeToNetwork();

      size_t x_coord = 
        size_t(
        ( x_start + vx * ( t_cursor - t_start ) ) / x_grid_length
      );
      size_t y_coord = 
        size_t(
        ( y_start + vy * ( t_cursor - t_start ) ) / y_grid_length
      );
  
      mynet->setNetworkLastTimeElement( x_coord, y_coord, z_coord, car_id );

      std::cout << "Added cube to network!" << std::endl;
      std::cout << "time: " << t_cursor;
      std::cout << " x: " << x_coord << " y: " << y_coord;
      std::cout << " z: " << z_coord << " carID: " << car_id;
      std::cout << std::endl;

    }

  }

  return 1;

}

Car * createCarFromInputLine( 
  Network * mynet,
  std::string line 
) {

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

  double d_x_min = mynet->getXMin();
  double d_y_min = mynet->getYMin();
  double x_grid_length = mynet->getXGridLength(); 
  double y_grid_length = mynet->getYGridLength(); 
  size_t x_size = mynet->getXSize();
  size_t y_size = mynet->getYSize();

  double d_x_max = d_x_min + x_size * x_grid_length;
  double d_y_max = d_y_min + y_size * y_grid_length;

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

    double d_min = ( i % 2 == 0 ) ? d_y_min : d_x_min;
    double d_max = ( i % 2 == 0 ) ? d_y_max : d_x_max;

    if( d_location < d_min || d_location > d_max ) {
      std::cout << "location out of range:" << d_location << std::endl;
      std::cout << "xmax " << d_x_max << std::endl;
      std::cout << "ymax " << d_y_max << std::endl;
      return NULL;
    }

    vd_loc.push_back( d_location );

  }

  Car * mycar = new Car( i_id, vd_loc[0], vd_loc[1], vd_loc[2], vd_loc[3] );

  return mycar;

}

void add_car_into_network(
  Car * mycar, Network * mynet
) {

  mycar->setZ( mynet->getMinCarZ() );
  mycar->setLastZ( mynet->getMinCarZ() );

  mynet->updateMinCarQueue();

}

void remove_car_from_network(
  Car * mycar, Network * mynet
) {

  mynet->updateMinCarQueue( mycar->getZ() );

}

int move_car(
  Car * mycar, Network * mynet
) {

  size_t z = mycar->getZ();

  if( z != mycar->getLastZ() ) {

    mycar->setZ( mycar->getZ() * 2 - mycar->getLastZ() );
    mycar->setLastZ( z );
    std::cout << "Keep moving." << std::endl;

  } else {

    if( z >= mynet->getZSize() / 2 ) {

      mycar->setZ( z - 1 );
      std::cout << "Move car downward to " << z - 1 << std::endl;

    } else {

      mycar->setZ( z + 1 );
      std::cout << "Move car upward to " << z - 1 << std::endl;

    }

  }

  if( mycar->getZ() == mynet->getZSize() || mycar->getZ() == 0 ) {

    std::cout << "Out of layers! " << mycar->getZ() << std::endl;

    return 0; 

  }

  return 1;

}

inline void my_wait( clock_t milisec ) {

  clock_t start_time = clock();
  clock_t end_time = milisec * 1000 + start_time;
  while( clock() < end_time );

}

void my_wait() {

  my_wait( DEFAULT_WAIT_TIME );

}
