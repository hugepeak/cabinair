#include<vector>
#include<list>

#define I_X_SIZE                100    // x grid number
#define I_Y_SIZE                100    // y grid number
#define I_LAYER                 10     // layer number
#define I_INITIAL_TIME_LENGTH   100    // seconds
#define I_GRID_LENGTH           10     // meters

void initialize_network(
  std::list<std::vector<std::vector<std::vector<int> > > > &
);

void add_empty_cubic_to_network(
  std::list<std::vector<std::vector<std::vector<int> > > > &
);
