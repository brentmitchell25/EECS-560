/*
 * Set.h
 *
 *  Created on: May 2, 2015
 *      Author: brentmitchell
 */

#ifndef SET_H_
#define SET_H_
#include <vector>

class Set {
public:
  explicit Set( int numElements );

  int find( int x ) const;
  int find( int x );
  void unionSets( int root1, int root2 );

private:
  std::vector<int> s;
};

#endif /* SET_H_ */
