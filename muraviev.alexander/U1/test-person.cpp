#include "person.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(parse_valid_line)
{
  muraviev::Person person;
  const bool result = muraviev::parsePersonLine("42\t  person info", person);

  BOOST_TEST(result);
  BOOST_TEST(person.id == 42U);
  BOOST_TEST(person.info == "person info");
}

BOOST_AUTO_TEST_CASE(reject_invalid_id)
{
  muraviev::Person person;

  BOOST_TEST(!muraviev::parsePersonLine("x42 person", person));
}

BOOST_AUTO_TEST_CASE(reject_empty_description)
{
  muraviev::Person person;

  BOOST_TEST(!muraviev::parsePersonLine("42 \t ", person));
}
