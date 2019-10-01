#include <iostream>
#include <vector>
#include <bitis.hpp>
#include <cassert>

int main(int argc, char *argv[])
{

  Wire a, b, sel, o;
  std::vector<std::vector<BIT>> sequence({
      {H,H,H,H},
      {H,H,L,H},
      {H,L,H,L},
      {H,L,L,H},
      {L,H,H,H},
      {L,H,L,L},
      {L,L,H,L},
      {L,L,L,L},
  });
  Multiplexer n(&a, &b, &sel, &o);

  std::cout << "a b sel out" << std::endl;

  for (auto &combination: sequence) {
    a.set(combination[0]);
    b.set(combination[1]);
    sel.set(combination[2]);
    n();
    std::cout
      << n.a->get() << " "
      << n.b->get() << " "
      << n.sel->get() << "   "
      << n.out->get()
      << std::endl;
    assert(n.out->get() == combination[3]);
  }

  return 0;
}
