#include "person.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(parse_valid_line)
{
  muraviev::Person person;
  const bool result = muraviev::parsePersonLine("42 person info", person);

  BOOST_TEST(result);
  BOOST_TEST(person.id == 42U);
  BOOST_TEST(person.info == " person info");
}
