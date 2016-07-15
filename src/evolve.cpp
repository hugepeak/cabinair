#include "evolve.h"

int evolve_car( 
  Network * mynet,
  Car * mycar
) {

  std::list<std::vector<std::vector<std::vector<int> > > >::iterator it = 
    mynet->getNetworkBegin();

  time_t t_start = mycar->getTimeStart();
  time_t t_cursor = t_start;
  time_t t_end = mycar->getTimeEnd();
  double x_start = mycar->getXStart();
  double y_start = mycar->getYStart();
  double vx = mycar->getVX();
  double vy = mycar->getVY();
  size_t car_layer = mycar->getLayer();
  int car_id = mycar->getCarID();

  while( t_cursor <= t_end && it != mynet->getNetworkEnd() ) {

    //==========================================================================
    // Check if the car has a later time than the first time in network.
    // If so, pop out the past cubics and continue to next time step. 
    //==========================================================================

    if( t_start > mynet->getFirstTime() ) {

      it++;
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

    std::cout << "time: " << t_cursor << " x: " << xgrid << " y: " << ygrid;
    std::cout << std::endl;

    t_cursor++;
    it++;

  }

  //============================================================================
  // Check if the car's time is beyond the last time in network.
  // If so, initialize new cubics of the rest of car's times into the network.
  //============================================================================

  if( it == mynet->getNetworkEnd() ) {

    for( ; t_cursor <= t_end; t_cursor++ ) {

      mynet->add_empty_cubic();

      size_t xgrid = 
        size_t(
        ( x_start + vx * ( t_cursor - t_start ) ) / D_X_GRID_LENGTH
      );
      size_t ygrid = 
        size_t(
        ( y_start + vy * ( t_cursor - t_start ) ) / D_Y_GRID_LENGTH
      );
  
      mynet->setLastElement( car_layer, xgrid, ygrid, car_id );

      std::cout << "added cubic to network: " << t_cursor << " ";
      std::cout << mynet->getNetworkBack()[car_layer][xgrid][ygrid] << " ";
      std::cout << std::endl;
      std::cout << "time: " << t_cursor << " x: " << xgrid << " y: " << ygrid;
      std::cout << std::endl;

    }

  }

  return 1;

}
