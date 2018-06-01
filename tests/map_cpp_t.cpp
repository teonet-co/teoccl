 /* 
 * File:   map_cpp_t
 * Author: max <mpano91@gmail.com>
 *
 * Created on Jun 1, 2018, 12:37:53 AM
 */

#include <iostream>
#include <CppUTest/TestHarness.h>
#include "../src/map.hpp"
#include <cstring>
using namespace std;
TEST_GROUP(MapSuite) {
  teo::Map map;
};

TEST(MapSuite, mapAddSizeMapClearExample) {
  struct example_s{
    unsigned x;
    double y;
  };
  struct example_s *my_struct = (struct example_s *)malloc(sizeof(struct example_s));
  my_struct->x = 100;
  my_struct->y = 34.6;
  map.add("qwer", "qrt");
  map.add(2, 5);
  map.add("fdf", 34);
  map.add("struct", my_struct);
  free(my_struct);
  CHECK(map.size() == 4);
  map.mapClear();
  CHECK(map.size() == 0);
  map.add(2, 5);
  map.add("fdf", 34);
  CHECK(map.size() == 2);
}

TEST(MapSuite, mapDeleteExample) {
  struct example_s{
    int x;
  };
  struct example_s *my_struct = (struct example_s *)malloc(sizeof(struct example_s));
  my_struct->x = 14;
//  my_struct->y = 34.6;
  map.add("qwer", "qrt");
  map.add(2, 5);
  map.add("fdf", 34);
  map.add("struct", my_struct);

  map.deleteByKey(2);
  CHECK(map.size() == 3);

  int* getcheck = (int *)map.get("fdf", NULL);
  CHECK(*getcheck == 34);

  map.deleteByKey("struct");
  CHECK(map.size() == 2);
}

TEST(MapSuite, mapInitExample) {
  teo::Map *m = new teo::Map();
  delete m;
}
