#include <iostream>
#include <vector>
#include <cassert>
#include <bitis.hpp>

int main(int argc, char *argv[])
{

  Wire a, b;
  Clock clk;
  DataFlipFlop n(&a, &b, &clk);
  std::vector<std::vector<BIT>> sequence({
      {H,H,H},
      {H,L,H},
      {H,H,H},
      {H,L,H},
      {L,H,L},
      {L,L,L},
      {L,H,L},
      {L,L,L},
  });

  std::cout << "in out clk" << std::endl;

  clk.fall();

  for (auto &seq: sequence) {
    a.set(seq[0]);
    n();
    clk.tick();
    assert(clk.get() == seq[1]);
    assert(n.out->get() == seq[2]);
    std::cout
      << n.in->get() << " "
      << n.out->get() << " "
      << n.clk->get() << std::endl;
  }

  return 0;
}

