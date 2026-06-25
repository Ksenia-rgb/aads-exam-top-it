#include "task.hpp"

int main()
{
  namespace per = permyakov;
  per::list< per::Person > * lst = new per::list< per::Person > ();
  std::pair< size_t, size_t > res = per::input(std::cin, lst);
  if (lst->next) {
    per::output(std::cout, lst->next);
  }
  per::clear(lst);
  std::cerr << res.first << ' ' << res.second << '\n';
}
