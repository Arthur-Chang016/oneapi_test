module {
  %0 = hcl.create_fifo : <16, <i32>>
  func.func @A(%arg0: memref<100xi32>, %arg1: memref<100xi32>, %arg2: !hcl.fifo<16, <i32>>) attributes {funcname = "A"} {
    affine.for %arg3 = 0 to 100 {
      %1 = affine.load %arg0[%arg3] : memref<100xi32>
      %2 = affine.load %arg1[%arg3] : memref<100xi32>
      %3 = arith.muli %1, %2 {iso_root = "root"} : i32
      %4 = hcl.struct_construct(%3) : i32 -> <i32>
      hcl.fifo_put %arg2, %4 : <16, <i32>>, <i32>
    }
    return
  }
  func.func @Producer(%arg0: !hcl.fifo<16, <i32>>) -> memref<100xi32> attributes {funcname = "A"} {
    %1 = memref.alloc() : memref<100xi32>
    affine.for %arg1 = 0 to 100 {
      %2 = hcl.fifo_pop %arg0 : <16, <i32>> -> <i32>
      %3 = hcl.struct_get %2[0] : <i32> -> i32
      affine.store %3, %1[%arg1] : memref<100xi32>
    }
    return %1 : memref<100xi32>
  }
}
