#include "cgotorch.h"

#include <iostream>
#include <sstream>

#include "torch/script.h"

Tensor RandN(int rows, int cols, int require_grad) {
  at::Tensor t = torch::randn({rows,cols},
			      at::TensorOptions().requires_grad(require_grad));
  return new at::Tensor(std::move(t));
}

Tensor MM(Tensor a, Tensor b) {
  at::Tensor c = at::mm(*static_cast<at::Tensor*>(a),
			*static_cast<at::Tensor*>(b));
  return new at::Tensor(std::move(c));
}

Tensor Sum(Tensor a) {
  at::Tensor r = static_cast<at::Tensor*>(a)->sum();
  return new at::Tensor(std::move(r));
}

void Tensor_Backward(Tensor a) {
  static_cast<at::Tensor*>(a)->backward();
}

Tensor Tensor_Grad(Tensor a) {
  at::Tensor r = static_cast<at::Tensor*>(a)->grad();
  return new at::Tensor(std::move(r));
}

void Tensor_Print(Tensor a) {
  std::cout << *static_cast<at::Tensor*>(a) << std::endl;
}

// The caller must free the returned string by calling FreeString.
const char* Tensor_String(Tensor a) {
  std::stringstream ss;
  ss << *static_cast<at::Tensor*>(a);
  std::string s = ss.str();
  char* r = new char[s.size()];
  strcpy(r, s.c_str());
  return r;
}

void FreeString(const char* s) {
  delete[] s;
}
