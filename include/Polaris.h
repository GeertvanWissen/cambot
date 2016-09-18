#ifndef POLARIS_H
#define POLARIS_H

class Polaris {

public:
  CoordsList getAllCoords // get a list of all coordinates
  bool save(string name) // save the current position as 'name' to compare to later
  Diff compare(string savedcoords) // compare current position to saved coordinated
  
}

class Coords {
public:
  int x;
  int y;
  string name;
}

class SavedCoords:Coords {

}

class CoordsList {

}

class Diff {

}
