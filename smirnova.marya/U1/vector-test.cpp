#include <boost/test/unit_test.hpp>
#include "vector.hpp"
#include "person.hpp"

BOOST_AUTO_TEST_SUITE(VectorTests)

BOOST_AUTO_TEST_CASE(push_back_and_access)
{
  smirnova::Vector<int> v;

  v.push_back(10);
  v.push_back(20);
  v.push_back(30);

  BOOST_CHECK_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[0], 10);
  BOOST_CHECK_EQUAL(v[1], 20);
  BOOST_CHECK_EQUAL(v[2], 30);
}

BOOST_AUTO_TEST_CASE(copy_constructor_deep_copy)
{
  smirnova::Vector<int> a;

  a.push_back(1);
  a.push_back(2);

  smirnova::Vector<int> b = a;

  BOOST_CHECK_EQUAL(b.size(), 2);
  BOOST_CHECK_EQUAL(b[0], 1);
  BOOST_CHECK_EQUAL(b[1], 2);

  b[0] = 999;

  BOOST_CHECK_EQUAL(a[0], 1); // deep copy check
}

BOOST_AUTO_TEST_CASE(copy_assignment_operator)
{
  smirnova::Vector<int> a;
  a.push_back(5);
  a.push_back(6);

  smirnova::Vector<int> b;
  b.push_back(100);

  b = a;

  BOOST_CHECK_EQUAL(b.size(), 2);
  BOOST_CHECK_EQUAL(b[0], 5);
  BOOST_CHECK_EQUAL(b[1], 6);
}

BOOST_AUTO_TEST_CASE(self_assignment)
{
  smirnova::Vector<int> v;

  v.push_back(1);
  v.push_back(2);

  v = v;

  BOOST_CHECK_EQUAL(v.size(), 2);
  BOOST_CHECK_EQUAL(v[0], 1);
  BOOST_CHECK_EQUAL(v[1], 2);
}

BOOST_AUTO_TEST_CASE(push_back_growth)
{
  smirnova::Vector<int> v;

  for (int i = 0; i < 100; ++i)
  {
    v.push_back(i);
  }

  BOOST_CHECK_EQUAL(v.size(), 100);

  for (int i = 0; i < 100; ++i)
  {
    BOOST_CHECK_EQUAL(v[i], i);
  }
}

BOOST_AUTO_TEST_CASE(iteration_test)
{
  smirnova::Vector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  int sum = 0;

  for (auto it = v.begin(); it != v.end(); ++it)
  {
    sum += *it;
  }

  BOOST_CHECK_EQUAL(sum, 6);
}

BOOST_AUTO_TEST_CASE(empty_vector)
{
  smirnova::Vector<int> v;

  BOOST_CHECK_EQUAL(v.size(), 0);
  BOOST_CHECK(v.begin() == v.end());
}

BOOST_AUTO_TEST_CASE(vector_of_strings)
{
  smirnova::Vector<std::string> v;

  v.push_back("A");
  v.push_back("B");

  BOOST_CHECK_EQUAL(v[0], "A");
  BOOST_CHECK_EQUAL(v[1], "B");
}

BOOST_AUTO_TEST_CASE(vector_of_structs)
{
  smirnova::Vector<smirnova::Person> v;

  v.push_back({1, "Alice"});
  v.push_back({2, "Bob"});

  BOOST_CHECK_EQUAL(v[0].id, 1);
  BOOST_CHECK_EQUAL(v[0].info, "Alice");

  BOOST_CHECK_EQUAL(v[1].id, 2);
  BOOST_CHECK_EQUAL(v[1].info, "Bob");
}

BOOST_AUTO_TEST_SUITE_END()

