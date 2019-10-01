#include <iostream>
#include <vector>
#include <bitis.hpp>

int main(int argc, char *argv[])
{

  Wire S, R, Q, _Q;
  std::vector<std::vector<BIT>> sequence({
    {H, L},
    {L, L},
    {L, H},
    {L, L},
    {H, L},
    {L, L},
  });
  SRLatch n(&S, &R, &Q, &_Q);
  std::cout <<
    "SR Latch" << std::endl <<
    "--------" << std::endl <<
    "S R Q ~Q" << std::endl <<
    "--------" << std::endl;
  for (auto &combination: sequence) {
    S.set(combination[0]);
    R.set(combination[1]);
    n();
    std::cout
      << n.s->get() << " "
      << n.r->get() << " "
      << n.q->get() << " "
      << n._q->get() << std::endl;
  }

  return 0;
}
