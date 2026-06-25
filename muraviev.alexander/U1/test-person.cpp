#include "person.hpp"

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <string>

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

BOOST_AUTO_TEST_CASE(read_unique_people_in_order)
{
  std::istringstream input("2 second\n1 first\n2 duplicate\nbad\n");
  muraviev::PersonList persons;
  muraviev::initList(persons);
  size_t accepted = 0;
  size_t ignored = 0;

  muraviev::readPersons(input, persons, accepted, ignored);

  BOOST_TEST(accepted == 2U);
  BOOST_TEST(ignored == 2U);
  BOOST_REQUIRE(persons.head != nullptr);
  BOOST_TEST(persons.head->person.id == 2U);
  BOOST_REQUIRE(persons.head->next != nullptr);
  BOOST_TEST(persons.head->next->person.id == 1U);
  BOOST_TEST(persons.head->next->next == nullptr);
  muraviev::clearList(persons);
}

BOOST_AUTO_TEST_CASE(print_people)
{
  muraviev::PersonList persons;
  muraviev::initList(persons);
  muraviev::appendPerson(persons, muraviev::Person{5, "five"});
  muraviev::appendPerson(persons, muraviev::Person{8, "eight"});
  std::ostringstream output;

  muraviev::printPersons(output, persons);

  BOOST_TEST(output.str() == "5 five\n8 eight\n");
  muraviev::clearList(persons);
}
