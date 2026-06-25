#include "options.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(parse_input_option)
{
  char program[] = "lab";
  char argument[] = "in:data.txt";
  char* argv[] = {program, argument};
  muraviev::ProgramOptions options;

  BOOST_TEST(muraviev::parseProgramOptions(2, argv, options));
  BOOST_TEST(options.hasInput);
  BOOST_TEST(options.inputName == "data.txt");
}

BOOST_AUTO_TEST_CASE(parse_output_option)
{
  char program[] = "lab";
  char argument[] = "out:result.txt";
  char* argv[] = {program, argument};
  muraviev::ProgramOptions options;

  BOOST_TEST(muraviev::parseProgramOptions(2, argv, options));
  BOOST_TEST(options.hasOutput);
  BOOST_TEST(options.outputName == "result.txt");
}

BOOST_AUTO_TEST_CASE(reject_repeated_input)
{
  char program[] = "lab";
  char first[] = "in:a.txt";
  char second[] = "in:b.txt";
  char* argv[] = {program, first, second};
  muraviev::ProgramOptions options;

  BOOST_TEST(!muraviev::parseProgramOptions(3, argv, options));
}
