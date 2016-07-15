#include "evolve.h"

int evolve_car( 
  std::list<std::vector<std::vector<std::vector<int> > > > &my_network,
  Car * mycar,
  time_t first_network_time
) {

  std::list<std::vector<std::vector<std::vector<int> > > >::iterator it = 
    my_network.begin();

  time_t t_start = mycar->getTimeStart();
  time_t t_cursor = t_start;
  time_t t_end = mycar->getTimeEnd();
  double x_start = mycar->getXStart();
  double y_start = mycar->getYStart();
  double vx = mycar->getVX();
  double vy = mycar->getVY();
  int layer = mycar->getLayer();
  int car_id = mycar->getCarID();

  while( t_cursor <= t_end && it != my_network.end() ) {

    //==========================================================================
    // Check if the car has a later time than the first time in network.
    // If so, pop out the past cubics and continue to next time step. 
    //==========================================================================

    if( t_start > first_network_time ) {

      first_network_time++;
      it++;
      my_network.pop_front();
      continue;

    } 

    //==========================================================================
    // Check if the car's position is already taken.
    // If so, change to the next layer with the same time and check.
    // If not, mark it with the car's ID.
    //==========================================================================

    int xgrid = 
      floor( ( x_start + vx * ( t_cursor - t_start ) ) / D_X_GRID_LENGTH );
    int ygrid = 
      floor( ( y_start + vy * ( t_cursor - t_start ) ) / D_Y_GRID_LENGTH );

    if( (*it)[layer][xgrid][ygrid] == 0 ) {

      (*it)[layer][xgrid][ygrid] = car_id;

    } else {

      if( layer == I_LAYER - 1 ) {
        std::cout << "Out of layers!" << std::endl;
        return 0;
      }

      layer++;
      mycar->setLayer( layer );
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

  if( it == my_network.end() ) {

    for( ; t_cursor <= t_end; t_cursor++ ) {

      add_empty_cubic_to_network( my_network );

      int xgrid = 
        floor( ( x_start + vx * ( t_cursor - t_start ) ) / D_X_GRID_LENGTH );
      int ygrid = 
        floor( ( y_start + vy * ( t_cursor - t_start ) ) / D_Y_GRID_LENGTH );
  
      my_network.back()[layer][xgrid][ygrid] = car_id;

      std::cout << "add cubic to network" << std::endl;
      std::cout << "time: " << t_cursor << " x: " << xgrid << " y: " << ygrid;
      std::cout << std::endl;

    }

  }

  return 1;

}
