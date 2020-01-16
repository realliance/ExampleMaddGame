/*
 * A speed-improved simplex noise algorithm for 2D, 3D and 4D in Java.
 *
 * Based on example code by Stefan Gustavson (stegu@itn.liu.se).
 * Optimisations by Peter Eastman (peastman@drizzle.stanford.edu).
 * Better rank ordering method for 4D by Stefan Gustavson in 2012.
 *
 * This could be speeded up even further, but it's useful as it is.
 *
 * Version 2012-03-09
 *
 * This code was placed in the public domain by its original author,
 * Stefan Gustavson. You may use it as you see fit, but
 * attribution is appreciated.
 *
 * 2D Simplex adapted to C++ by Alice Hartley
 * 
 */
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include "simplexcomponent.h"
#include <system.h>
#include <unordered_map>

struct SeedData{
  short perm[512];
  short permMod12[512];
}

class SimplexSystem : public System {
  public:
    double Noise(double xin, double yin);
    ~SimplexSystem();
    void Init();
    void Deinit();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();
    std::string Name() { return "SimplexSystem"; }
    std::vector<std::string> Requires() {return {};};
  private: 
    std::vector<SimplexComponent*> simplexInstances;
    std::unordered_map<ComponentID, SeedData> simplexData;
    std::vector<glm::vec2> grad2;
    int fastfloor(double x);
    static const constexpr double sqrt3 = 1.7320508075688772; //3**0.5 in python3.8
    static const constexpr double F2 = 0.5*(sqrt3-1.0);
    static const constexpr double G2 = (3.0-sqrt3)/6.0;
};
