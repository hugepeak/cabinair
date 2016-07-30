#include <iomanip>
#include <boost/lexical_cast.hpp>
#include "car.h"
#include "network.h"

Car * createCarFromInputLine(
  Network *,
  std::string
);
int evolve_car( 
  Car *, Network *
); 
void add_car_into_network( 
  Car *, Network *
); 
void remove_car_from_network( 
  Car *, Network *
); 
int move_car(
  Car *, Network *
);
