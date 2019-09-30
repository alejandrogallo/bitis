#include <iostream>
#include <vector>
#include <bitis.hpp>

int main(int argc, char *argv[])
{
  Wire a, b, o;
  Clock c;
  std::vector<std::vector<BIT>>
    combinations({ {H, H}, {H, L}, {L, H}, {L, L}, });

  {
    AndGate n(&a, &b, &o);
    std::cout << "--And-" << std::endl;
    std::cout << "a" << " " << "b" << " " << "out" << std::endl;
    std::cout << "-------" << std::endl;
    for (auto &combination: combinations) {
      a.set(combination[0]);
      b.set(combination[1]);
      n();
      std::cout << a.get() << " " << b.get() << " " <<
        n.outputs[0]->get() << std::endl;
    }
  }

  {
    NandGate n(&a, &b, &o);
    std::cout << "--Nand-" << std::endl;
    std::cout << "a" << " " << "b" << " " << "out" << std::endl;
    std::cout << "-------" << std::endl;
    for (auto &combination: combinations) {
      a.set(combination[0]);
      b.set(combination[1]);
      n();
      std::cout << a.get() << " " << b.get() << " " <<
        n.outputs[0]->get() << std::endl;
    }
  }

  {
    OrGate n(&a, &b, &o);
    std::cout << "--Or--" << std::endl;
    std::cout << "a" << " " << "b" << " " << "out" << std::endl;
    std::cout << "-------" << std::endl;
    for (auto &combination: combinations) {
      a.set(combination[0]);
      b.set(combination[1]);
      n();
      std::cout << a.get() << " " << b.get() << " " <<
        n.outputs[0]->get() << std::endl;
    }
  }

  {
    NorGate n(&a, &b, &o);
    std::cout << "--Nor--" << std::endl;
    std::cout << "a" << " " << "b" << " " << "out" << std::endl;
    std::cout << "-------" << std::endl;
    for (auto &combination: combinations) {
      a.set(combination[0]);
      b.set(combination[1]);
      n();
      std::cout << a.get() << " " << b.get() << " " <<
        n.outputs[0]->get() << std::endl;
    }
  }

  {
    XorGate n(&a, &b, &o);
    std::cout << "--Xor--" << std::endl;
    std::cout << "a" << " " << "b" << " " << "out" << std::endl;
    std::cout << "-------" << std::endl;
    for (auto &combination: combinations) {
      a.set(combination[0]);
      b.set(combination[1]);
      n();
      std::cout << a.get() << " " << b.get() << " " <<
        n.outputs[0]->get() << std::endl;
    }
  }
  return 0;
}


