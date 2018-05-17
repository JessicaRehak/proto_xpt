#include "point.h"

namespace xpt {

namespace mesh {

Point::Point(const float x, const float y) {
  position = {x, y};
}

std::string Point::to_str(int precision) const {
  // Print position with given precision
  std::ostringstream output;
  output << std::fixed << std::setprecision(precision)
         << "(" << position.first << ", " << position.second << ")";
  return output.str();
}

// template <int dim>
// Point<dim>& Point<dim>::operator+=(const Coordinates &rhs) {
//   std::transform(position.begin(), position.end(), rhs.begin(), position.begin(),
//                  std::plus<float>());
// }

// template <int dim>
// std::string const& Point<dim>::to_str() const {
//   std::string output = "Point: (";
//   for (const auto value : position)
//     output += value + ", ";
//   output = output.substr(0, output.size() - 2);
//   output += ")";
//   return output;
// }

} // namespace mesh

} // namespace xpt
