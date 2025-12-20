#include "mio.h"

int main() {
  defer {
    println(
        "\nThis print are defined below, but are being called in the end of "
        "function");
  };

  for (int i = 0; i < 100000; i++) {
    println("[01] for_loop batch 100K %i", i);
  }
  return 0;
}
