#ifndef POLARIS_H
#define POLARIS_H

#include <vector>

class Polaris {

public:
  struct Coords
  {
    int x;
    int y;
  };
  
  vector<Coords> coordslist;
  
  Polaris()
  {
    // constructor
  }
}

#endif
