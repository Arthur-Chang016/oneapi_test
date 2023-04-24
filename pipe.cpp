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

struct Struct {
  int a;
};

using ProducerToConsumerPipe = pipe<  // Defined in the SYCL headers.
  class ProducerConsumerPipe,         // An identifier for the pipe.
  Struct,                                // The type of data in the pipe.
  4>;                                 // The capacity of the pipe.


class ProducerTutorial;
class ConsumerTutorial;

class A {
  int *arg0, *arg1;
public:
  A(int *arg0_, int *arg1): arg0(arg0_), arg1(arg1) {}

  void operator ()() const {
    // the kernel
    for (size_t i = 0; i < 100; ++i) {  // affine.for %arg3 = 0 to 100 
      int tmp1 = arg0[i];  // %1 = affine.load %arg0[%arg3] : memref<100xi32>
      int tmp2 = arg1[i];  // %2 = affine.load %arg1[%arg3] : memref<100xi32>
      int tmp3 = tmp1 * tmp2;  // %3 = arith.muli %1, %2 {iso_root = "root"} : i32
      Struct tmp4{tmp3};  // %4 = hcl.struct_construct(%3) : i32 -> <i32>
      ProducerToConsumerPipe::write(tmp4);  // hcl.fifo_put %arg2, %4 : <16, <i32>>, <i32>
    }
  }
};

class Producer {
public:
  Producer() {}

  int *operator ()() const {
    int *tmp1 = (int *) malloc(sizeof(int) * 100);  // %res = memref.alloc() : memref<100xi32>
      
      for (size_t i = 0; i < 100; ++i) {  // affine.for %arg1 = 0 to 100
        Struct tmp2 = ProducerToConsumerPipe::read();  // %2 = hcl.fifo_pop %arg0 : <16, <i32>> -> <i32>
        int tmp3 = tmp2.a;  // %3 = hcl.struct_get %2[0] : <i32> -> i32
        tmp1[i] = tmp3;  // affine.store %3, %1[%arg1] : memref<100xi32>
      }
      return tmp1;
  }
};

void A_frame(int arg0[100], int arg1[100], queue &q) {
  auto e = q.submit([&](handler &h) {
    h.single_task<ProducerTutorial>(A(arg0, arg1));
  });
}


// no argument
void Producer_frame(queue &q) {
  auto e = q.submit([&](handler &h) {
    h.single_task<ConsumerTutorial>(Producer());
  });
}


int main(int argc, char *argv[]) {
    std::cout << "hi" << std::endl;
    
    
}