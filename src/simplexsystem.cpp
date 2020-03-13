#include "simplexsystem.h"
#include <random>

SystemType SimplexSystem::sType = Madd::GetNewSystemType();

void SimplexSystem::Init(){
  source = nullptr;
}

double SimplexSystem::Noise(double xin, double yin) {
    if(source == nullptr){
      return NAN;
    }
    xin = xin/source->size.x;
    yin = yin/source->size.z;

    double n0, n1, n2; // Noise contributions from the three corners
    // Skew the input space to determine which simplex cell we're in
    double s = (xin+yin)*F2; // Hairy factor for 2D
    int i = fastfloor(xin+s);
    int j = fastfloor(yin+s);
    double t = (i+j)*G2;
    double X0 = i-t; // Unskew the cell origin back to (x,y) space
    double Y0 = j-t;
    double x0 = xin-X0; // The x,y distances from the cell origin
    double y0 = yin-Y0;
    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
    if(x0>y0) {i1=1; j1=0;} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    else {i1=0; j1=1;}      // upper triangle, YX order: (0,0)->(0,1)->(1,1)
    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6
    double x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
    double y1 = y0 - j1 + G2;
    double x2 = x0 - 1.0 + 2.0 * G2; // Offsets for last corner in (x,y) unskewed coords
    double y2 = y0 - 1.0 + 2.0 * G2;
    // Work out the hashed gradient indices of the three simplex corners
    int ii = i & 255;
    int jj = j & 255;
    int gi0 = source->permMod12[ii+source->perm[jj]];
    int gi1 = source->permMod12[ii+i1+source->perm[jj+j1]];
    int gi2 = source->permMod12[ii+1+source->perm[jj+1]];
    // Calculate the contribution from the three corners
    double t0 = 0.5 - x0*x0-y0*y0;
    if(t0<0) n0 = 0.0;
    else {
      t0 *= t0;
      n0 = t0 * t0 * glm::dot(grad2[gi0], glm::vec2(x0, y0));  // (x,y) of grad3 used for 2D gradient
    }
    double t1 = 0.5 - x1*x1-y1*y1;
    if(t1<0) n1 = 0.0;
    else {
      t1 *= t1;
      n1 = t1 * t1 * glm::dot(grad2[gi1],  glm::vec2(x1, y1));
    }
    double t2 = 0.5 - x2*x2-y2*y2;
    if(t2<0) n2 = 0.0;
    else {
      t2 *= t2;
      n2 = t2 * t2 * glm::dot(grad2[gi2],  glm::vec2(x2, y2));
    }
    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 70.0 * (n0 + n1 + n2) * source->size.y;
  }

int SimplexSystem::fastfloor(double x) {
  int xi = (int)x;
  return x<xi ? xi-1 : xi;
}

bool SimplexSystem::Register(Component* component){
  SimplexComponent* sc = dynamic_cast<SimplexComponent*>(component);
  simplexInstances.push_back(sc);
  simplexData[sc->cID] = SeedData{};
  source = &simplexData[sc->cID];
  source->size = sc->size;
  initSimplexInst(hashSeed(sc->seed),*source);
  return true;
}

void SimplexSystem::Enable(SimplexComponent* sc){
  if(simplexData.contains(sc->cID)){
    source = &simplexData[sc->cID];
  }
}

void SimplexSystem::initSimplexInst(uint seed, SeedData& sc){
  std::mt19937 mt(seed);
  std::uniform_int_distribution<> dist(0,255);
  for(int i = 0; i < 255; i++){
    short n = dist(mt);
    sc.perm[i] = n;
    sc.perm[i+256] = n;
  }
  for(int i=0; i<512; i++){
    sc.permMod12[i] = (short)(sc.perm[i] % 12);
  }
  grad2 = {glm::vec2(1,1),glm::vec2(-1,1),glm::vec2(1,-1),glm::vec2(-1,-1),
           glm::vec2(1,0),glm::vec2(-1,0),glm::vec2(1,0),glm::vec2(-1,0),
           glm::vec2(0,1),glm::vec2(0,-1),glm::vec2(0,1),glm::vec2(0,-1)};
}

uint SimplexSystem::hashSeed(std::string seed){
  //crc hash
  uint h = 0;
  for(const auto& ki : seed){
    uint highorder = h & 0xf8000000;
    h = h << 5;
    h = h ^ (highorder >> 27);
    h = h ^ ki;
  }
  return h % m;
}


bool SimplexSystem::Unregister(Component* component){
  for(auto i = begin(simplexInstances); i != end(simplexInstances); i++){
    if((*i)->cID == component->cID){
      simplexInstances.erase(i);
      simplexData.erase(component->cID);
      source = nullptr;
      return true;
    }
  }
  return false;
}
