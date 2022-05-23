#define BOOST_TEST_MODULE test_filtration
#include <boost/test/included/unit_test.hpp>


#include "ip_pool.hpp"

const std::string input = 
R"(113.162.45.156	111	0
157.39.22.224	5	6
67.250.31.212	1	0
79.180.73.190	2	1
179.210.45.4	22	0
219.102.120.135	486	0
67.232.81.208	1	0
85.254.10.197	0	7
23.240.215.189	6	0
1.29.168.152	17	0
185.89.186.168	1	3
110.152.103.161	0	1
67.250.31.212	1	0
185.182.81.131	1	1
68.45.152.8	2	0
114.221.179.117	0	1
185.89.100.249	752	0
45.70.113.73	1	0
188.68.0.38	1	0
)";


std::istringstream iss(input);
const ip_pool pool(iss);

BOOST_AUTO_TEST_SUITE(test_filtration)
BOOST_AUTO_TEST_CASE( test_filter_first )
{
std::stringstream is( R"(67.250.31.212	1	0
67.232.81.208	1	0
67.250.31.212	1	0
)");
  ip_pool first(is);
  BOOST_CHECK_MESSAGE( pool.filter(67) == first.get(),
    "filter by first byte failed");
}

BOOST_AUTO_TEST_CASE( test_filter_first_second )
{
std::stringstream is( R"(185.89.186.168	1	3
185.89.100.249	752	0
)");
  ip_pool second(is);
  BOOST_CHECK_MESSAGE( pool.filter(185, 89) == second.get(),
    "filter by first and second byte failed");
}

BOOST_AUTO_TEST_CASE( test_filter_any )
{
std::stringstream is( R"(113.162.45.156	111	0
179.210.45.4	22	0
68.45.152.8	2	0
45.70.113.73	1	0
)");
  ip_pool third(is);
  BOOST_CHECK_MESSAGE( pool.filter_any(45) == third.get(),
    "filter by any byte failed");
}
BOOST_AUTO_TEST_SUITE_END()
