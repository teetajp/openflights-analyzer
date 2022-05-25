/**
 * @file pagerank.h
 * @brief Implements PageRank algorithm to determine the "importance" of each airport
 */
#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

/* Idea: Model travellers flying to different destinations by taking random flights,
        - Airports with more incoming flights are presumed to be more important, so they get a higher PageRank value
        - The probability of a traveller flying to one airport to another is (number of routes from src to dest / total routes going out from src)
*/

class PageRank {
public:
  /**
   * @brief Construct a new Page Rank object w/ damping factor defaulting to 0.85
   * 
   * @param adj_matrix graph.h's implementation of the adjacency matrix
   */
  PageRank(vector<vector<int>>& adj_matrix);

  /**
   * @brief Construct a new Page Rank object w/ specified damping factor
   * 
   * @param adj_matrix graph.h's implementation of the adjacency matrix
   * @param damping_factor probability of traveller continuing (helps prevent sinks)
   */
  PageRank(vector<vector<int>>& adj_matrix, double damping_factor);

  /**
   * @brief Computes the steady-state eigenvector of a Markov matrix
   * 
   * @param matrix n x n matrix
   * @param curr_state normalized guess, size must be n x 1
   * @param max_iterations max number of iterations, actual number may be lower if vector converges
   * @return vector<double> steady-state vector
   */
  static vector<double> powerIteration(const vector<vector<double>>& matrix, const vector<double> curr_state, unsigned int max_iterations);

  /**
   * @brief Computes the PageRank vector (unsorted)
   * 
   * @param max_iterations max number of iterations for the powerIteration function
   * @return vector<double> PageRank vector where each index corresponds to the same entry as in
   *                        the adjacency matrix passed in the constructor
   */
  vector<double> computePageRank(unsigned int max_iterations) const;

  /** Returns the Markov matrix with the damping factor applied */
  vector<vector<double>> getMatrix() const;

  /** Prints out the Markov matrix with the damping factor applied */
  void printMatrix() const;

private:
  vector<vector<double>> matrix_; // n by n matrix where each column adds up to 1 and [i][j] != 0 means there is a route from j to i
  size_t num_airports_; // total number of airports
  double damping_factor_; // probability of traveller continuing (helps prevent sinks)
};