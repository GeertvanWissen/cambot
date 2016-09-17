class Move
{
 public:
  static bool init();
  static bool direction(int dir);
  static bool stop();

 private:
  // Disallow creating an instance of this object
  Move() {}
};
