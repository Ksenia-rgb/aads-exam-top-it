#include "parsing.hpp"

#include <boost/test/unit_test.hpp>
#include <limits>
#include <string>

BOOST_AUTO_TEST_CASE(parse_valid_size)
{
  size_t value = 0;

  BOOST_TEST(muraviev::parseSizeValue("123", value));
  BOOST_TEST(value == 123U);
}

BOOST_AUTO_TEST_CASE(reject_negative_size)
{
  size_t value = 0;

  BOOST_TEST(!muraviev::parseSizeValue("-1", value));
}

BOOST_AUTO_TEST_CASE(reject_overflow_size)
{
  const std::string value =
      std::to_string(std::numeric_limits< size_t >::max()) + "0";
  size_t result = 0;

  BOOST_TEST(!muraviev::parseSizeValue(value, result));
}

BOOST_AUTO_TEST_CASE(parse_meeting_line)
{
  muraviev::Meeting meeting;

  BOOST_TEST(muraviev::parseMeetingLine("33 32 11", meeting));
  BOOST_TEST(meeting.first == 33U);
  BOOST_TEST(meeting.second == 32U);
  BOOST_TEST(meeting.time == 11U);
}

BOOST_AUTO_TEST_CASE(require_data_option)
{
  char program[] = "lab";
  char input[] = "in:persons.txt";
  char* argv[] = {program, input};
  muraviev::ProgramOptions options;

  BOOST_TEST(!muraviev::parseOptions(2, argv, options));
}

BOOST_AUTO_TEST_CASE(parse_data_option)
{
  char program[] = "lab";
  char data[] = "data:meetings.txt";
  char* argv[] = {program, data};
  muraviev::ProgramOptions options;

  BOOST_TEST(muraviev::parseOptions(2, argv, options));
  BOOST_TEST(options.dataFile == "meetings.txt");
}

BOOST_AUTO_TEST_CASE(reject_repeated_data_option)
{
  char program[] = "lab";
  char first[] = "data:first.txt";
  char second[] = "data:second.txt";
  char* argv[] = {program, first, second};
  muraviev::ProgramOptions options;

  BOOST_TEST(!muraviev::parseOptions(3, argv, options));
}

BOOST_AUTO_TEST_CASE(reject_empty_data_name)
{
  char program[] = "lab";
  char data[] = "data:";
  char* argv[] = {program, data};
  muraviev::ProgramOptions options;

  BOOST_TEST(!muraviev::parseOptions(2, argv, options));
}
