#include <iostream>
#include <sycl/sycl.hpp>
using namespace sycl;

const std::string secret {
  "Ifmmp-!xpsme\"\012J(n!tpssz-!Ebwf/!"
  "J(n!bgsbje!J!dbo(u!ep!uibu/!.!IBM\01"};

const auto sz = secret.size();

int main() {
  queue q;

  char * result = malloc_shared<char>(sz, q);
  std::memcpy(result, secret.data(), sz);

  q.parallel_for(sz, [=](auto& i) {
    result[i] -= 1;
  }).wait();

  std::cout << result << "\n";
  free(result, q);
  return 0;
}
