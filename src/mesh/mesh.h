#ifndef PROTO_XPT_MESH_MESH_H_
#define PROTO_XPT_MESH_MESH_H_

#include <stdexcept>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

namespace xpt {

namespace mesh {

class Mesh {
 public:
  //Cartesian Mesh

  explicit Mesh() {};
  ~Mesh() = default;

  // Mesh nodes

  // Mesh Parameters
  float get_x_min() const {return x_min_;};
  float get_x_max() const {return x_max_;};
  float get_y_min() const {return y_min_;};
  float get_y_max() const {return y_max_;};
  Mesh &set_x_min(float x_min) { x_min_ = x_min; return *this;};
  Mesh &set_x_max(float x_max) { x_max_ = x_max; return *this;};
  Mesh &set_y_min(float y_min) { y_min_ = y_min; return *this;};
  Mesh &set_y_max(float y_max) { y_max_ = y_max; return *this;};
  
 private:
  float x_min_ = 0;
  float x_max_ = 0;
  float y_min_ = 0;
  float y_max_ = 0;
};

std::unique_ptr<Mesh> ImportMeshFromStream(std::istream &input_stream);
  
} //namespace mesh

} //namespace xpt

#endif
