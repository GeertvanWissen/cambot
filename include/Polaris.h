#ifndef POLARIS_H
#define POLARIS_H

#include <vector>

class Polaris {
private:
  vector<Coords> coordslist;

public:
  struct Coords
  {
    int x;
    int y;
  };
  
  Polaris()
  {
    // constructor
  }
  
  getCoordslist();

}

#endif
