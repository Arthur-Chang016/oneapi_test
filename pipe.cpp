#include <sycl/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
// #include "pipe_utils.hpp"
// #include "unrolled_loop.hpp"

// #include "exception_handler.hpp"

using namespace sycl;

using ProducerToConsumerPipe = pipe<  // Defined in the SYCL headers.
  class ProducerConsumerPipe,         // An identifier for the pipe.
  int,                                // The type of data in the pipe.
  4>;                                 // The capacity of the pipe.

int main(int argc, char *argv[]) {
    std::cout << "hi" << std::endl;
    
    
}