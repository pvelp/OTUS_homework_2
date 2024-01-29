 #include <gtest/gtest.h>
 #include <algorithm>

 #include "lib.hpp"

 TEST(VersionTest, BasicAssertions) {
   // Expect equality.
   EXPECT_NE(version(), 100);
 }


 TEST(FilterFirstByteTest, BasicAssertions){
     std::vector<std::array<uint8_t, 4>> excepted_pool = {{1, 231, 69, 33},
                                                          {1,87, 203, 225},
                                                          {1, 70, 44, 170},
                                                          {1, 29, 168, 152},
                                                          {1, 1, 234, 8}};

     std::vector<std::array<uint8_t, 4>> input_pool = {{1, 231, 69, 33},
                                            {22, 134, 11, 1},
                                            { 242,132,99,14 },
                                            { 1,87,203,225 },
                                            { 21,133,121,11 },
                                            { 24,132,99,143 },
                                            { 1,70,44,170 },
                                            { 1,29,168,152 },
                                            { 24,132,99,145 },
                                            { 1,1,234,8 }};
     std::sort(input_pool.rbegin(), input_pool.rend());
     IpFilter ipFilter = IpFilter(input_pool);

     std::vector<std::array<uint8_t, 4>> res;
     res = ipFilter.filter(1);

     EXPECT_EQ(res, excepted_pool);
     EXPECT_NE(res, input_pool);
 }


 TEST(FilterTwoByteTest, BasicAssertions){
     std::vector<std::array<uint8_t, 4>> excepted_pool = {{46, 70, 225, 39},
                                                          {46, 70, 147, 26},
                                                          {46, 70, 113, 73},
                                                          {46, 70, 29, 76} };

     std::vector<std::array<uint8_t, 4>> input_pool = {{1, 231, 69, 33},
                                            {46, 70, 29, 76},
                                            {242, 132, 99, 14},
                                            {1, 87, 203, 225},
                                            {46, 70, 147, 26},
                                            {24, 132, 99, 143},
                                            {1, 70, 44, 170},
                                            {46, 70, 113, 73},
                                            {24, 132, 99, 145},
                                            {1, 1, 234, 8},
                                            {46, 70, 225, 39}};

     std::sort(input_pool.rbegin(), input_pool.rend());
     IpFilter ipFilter = IpFilter(input_pool);

     std::vector<std::array<uint8_t, 4>> res;
     res = ipFilter.filter(46, 70);

     EXPECT_EQ(res, excepted_pool);
     EXPECT_NE(res, input_pool);
 }


 TEST(FilterAnyByteTest, BasicAssertions){
     std::vector<std::array<uint8_t, 4>> excepted_pool = {
                                            {185, 46, 86, 131},
                                            {185, 46, 85, 204},
                                            {46, 70, 225, 39},
                                            {46, 70, 147, 26},
                                            {46, 70, 113, 73},
                                            {46, 70, 29, 76},
                                            { 5, 189, 203, 46 }};

     std::vector<std::array<uint8_t, 4>> input_pool = {
                                            {1, 231, 69, 33},
                                            {5, 189, 203, 46},
                                            {185, 46, 86, 131},
                                            {46, 70, 29, 76},
                                            {242, 132, 99, 14},
                                            {185, 46, 85, 204},
                                            {1, 87, 203, 225},
                                            {46, 70, 147, 26},
                                            {24, 132, 99, 143},
                                            {1, 70, 44, 170},
                                            {46, 70, 113, 73},
                                            {24, 132, 99, 145},
                                            {1, 1, 234, 8},
                                            {46, 70, 225, 39}};
     std::sort(input_pool.rbegin(), input_pool.rend());
     IpFilter ipFilter = IpFilter(input_pool);

     std::vector<std::array<uint8_t, 4>> res;
     res = ipFilter.filter_any(46);

     EXPECT_EQ(res, excepted_pool);
     EXPECT_NE(res, input_pool);
 }
