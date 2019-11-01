#pragma once

#include "tensors/tensor.h"

namespace marian {
namespace cpu {
namespace variant { // Variants of GEMM implementations

void PackInfoFp32(const marian::Shape& shape,
                  const bool transpose,
                  /*out*/uint64_t& packsize);

void PackInfoFp32(const marian::Shape& shape,
                  const bool transpose,
                  int& nrow,
                  int& ncol,
                  int& kernel_ncol_blocks,
                  int& brow,
                  int& bcol,
                  int& last_brow,
                  int& nbrow,
                  int& nbcol,
                  /*out*/uint64_t& packsize); // @TODO: change to size_t where appropriate

// Pack a matrix into cache utilization efficient way (block format)
// out: output tensor - packed format
// inData: input tensor data - pointer of float data
// transpose: the matrix is transposed
// nrow: the number of rows
// ncol: the number of columns
// kernel_ncol_blocks: the number of column blocks
// brow: the number of rows in a block
// bcol: the number of columns in a block
// last_brow: the number of rows in the last block
// nbrow: row index in a block
// nbcol: column index in a block
// packsize: the size of the packed matrix
//          (the number of fp16 elements + padding (1024) + extra temporary memory (256))
void PackFp32(marian::Tensor out,
              const float* inData,
              const bool transpose,
              const int nrow,
              const int ncol,
              const int kernel_ncol_blocks,
              const int brow,
              const int bcol,
              const int last_brow,
              const int nbrow,
              const int nbcol,
              const uint64_t packsize); // @TODO: change to size_t where appropriate

// GEMM operation on the packed B matrix
// C: output matrix
// A: A matrix
// B: B matrix (packed)
// m: the number of rows in A and C
// n: the number of columns in B and C
// transA: transpose of A matrix
// B is already packed. So, we don't need transB
void GemmPackFp32(marian::Tensor C,
                  const marian::Tensor A,
                  const marian::Tensor B,
                  const marian::Tensor bias,
                  const size_t m,
                  const size_t n,
                  const int transA = 0);

}  // namespace variant
}  // namespace cpu
}  // namespace marian
