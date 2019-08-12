 /* 
 * File:   map_cpp_t
 * Author: max <mpano91@gmail.com>
 *
 * Created on Jun 1, 2018, 12:37:53 AM
 */

#include <cstring>
#include <iostream>
#include <CppUTest/TestHarness.h>

#include "teoccl/map.hpp"

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

  map.del(2);
  CHECK(map.size() == 3);

  int* getcheck = (int *)map.get("fdf", NULL);
  CHECK(*getcheck == 34);

  map.del("struct");
  CHECK(map.size() == 2);
}

TEST(MapSuite, mapInitExample) {
  teo::Map *m = new teo::Map();
  delete m;
}

TEST(MapSuite, mapForeachExample) {
  
  const std::string str[] = {
    "String 0",
    "String 1",
    "String 2",
    "String 3",
    "String 4",
    "String 5"
  };  
  const int str_length = (int)(sizeof(str) / sizeof(str[0]));
  
  for(int i =0; i < str_length; i++) {
    std::string key = std::to_string(i);
    map.add(key, str[i]);
  }  

  map.foreach([](teoMap *m, int idx, teoMapElementData *el, void* user_data) {
    auto str = (const std::string *)user_data;
    string key = (const char*)teoMapIteratorElementKey(el, NULL);
    STRCMP_EQUAL((const char*)teoMapIteratorElementData(el, NULL), str[std::stoi(key)].c_str());
    return 0;
  }, (void*)str);
}
