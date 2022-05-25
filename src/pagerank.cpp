#include "pagerank.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

PageRank::PageRank(vector<vector<int>>& adj_matrix) : PageRank(adj_matrix, 0.85) {}

PageRank::PageRank(vector<vector<int>>& adj_matrix, double damping_factor) {
  /* Current adjacencyMatrix has weights and use ints, but we don't need them, so set it all to 1
     and normalize each column of the matrix to create a Markov matrix. This is only possible w/ decimal types.
  */ 

  /// XXX: In graph.cpp, M[i][j] represents a route from i to j.
  /* We will tranpose the matrix (flip 'i' and 'j') so that M[i][j] represents a route from 'j' to 'i',
    for the sake of consistency and easy implementation with the referenced resources. */
  damping_factor_ = damping_factor;
  num_airports_ = adj_matrix.size();
  matrix_ = vector<vector<double>>(num_airports_, vector<double> (num_airports_, 0.0)); // Initialize an empty matrix of zeroes.
  vector<double> colSum(num_airports_); // Sum of each column, used for normalization

  for (size_t src_idx = 0; src_idx < num_airports_; src_idx++) {
    for (size_t dest_idx = 0; dest_idx < num_airports_; dest_idx++) {
      // Transpose the matrix and set value to 1 if there exists a route from src to dest, 0 otherwise
      if (adj_matrix[src_idx][dest_idx] != -1) {
        matrix_[dest_idx][src_idx] = 1;
        colSum[src_idx] += 1;
      }
    }
  }

  /* Normalize each column, deal with sinks, and add damping factor */
  for (size_t col_idx = 0; col_idx < num_airports_; col_idx++) {
    for (size_t row_idx = 0; row_idx < num_airports_; row_idx++) {
      if (colSum[col_idx] != 0) {
        // Normalize each column so sum adds up to 1
        matrix_[row_idx][col_idx] /= colSum[col_idx];
      } else {
        // Airport w/ no outgoing routes: set probability to go to all other airports as 1 / N
        matrix_[row_idx][col_idx] = 1.0 / num_airports_;
      }
      // Add damping factor
      matrix_[row_idx][col_idx] = damping_factor_ * matrix_[row_idx][col_idx]
                                          + (1 - damping_factor_) / num_airports_;
    }
  }
}

vector<double> PageRank::powerIteration(const vector<vector<double>>& matrix,
                                        vector<double> curr_state,
                                        unsigned int max_iterations) {
  // Need two vectors otherwise we can't update and calculate the state vector at the same time
  size_t n = matrix.size();
  vector<double> new_state(n);

  // Perform power iteration until max_iterations reached or values converged
  for (size_t t = 0; t < max_iterations; t++) {
    // Multiply the matrix by the state vector
    for (size_t i = 0; i < n; i++) {
      // The product obtained by multiplying term-by-term the entries of the
      // ith row of A and the jth column of B, and summing these n products
      double dot_product = 0.0; 
      for (size_t j = 0; j < n; j++)
        dot_product += matrix[i][j] * curr_state[j];

      new_state[i] = dot_product;
    }
    curr_state = new_state;
  }
  return curr_state;
}

vector<double> PageRank::computePageRank(unsigned int max_iterations) const {
    // (Second argument passed in): All airports have same rank of 1/N initially 
  return powerIteration(matrix_, vector<double>(num_airports_, 1.0 / num_airports_), max_iterations);
}

vector<vector<double>> PageRank::getMatrix() const{
  return matrix_;
}

void PageRank::printMatrix() const {
  for (size_t i = 0; i < num_airports_; i++) {
    cout << "[";
    for (size_t j = 0; j < num_airports_; j++) {
      cout << " " << std::to_string(matrix_[i][j]);
    }
    cout << " ]" << endl;
  }
}