#include <boost/test/unit_test.hpp>
#include "../common/domain.hpp"
#include "../common/parse.hpp"

BOOST_AUTO_TEST_CASE(parse_correct_person_line)
{
  const std::string line = "100 Sneaky person";
  size_t id = 0;
  size_t position = 0;
  std::string description;

  BOOST_TEST(shaykhraziev::parseSizeTPrefix(line, id, position));
  BOOST_TEST(id == 100);
  BOOST_TEST(shaykhraziev::readRestDescription(line, position, description));
  BOOST_TEST(description == "Sneaky person");
}

BOOST_AUTO_TEST_CASE(reject_line_without_id)
{
  const std::string line = "abc Sneaky person";
  size_t id = 0;
  size_t position = 0;

  BOOST_TEST(!shaykhraziev::parseSizeTPrefix(line, id, position));
}

BOOST_AUTO_TEST_CASE(reject_empty_description)
{
  const std::string line = "100    ";
  size_t id = 0;
  size_t position = 0;
  std::string description;

  BOOST_TEST(shaykhraziev::parseSizeTPrefix(line, id, position));
  BOOST_TEST(!shaykhraziev::readRestDescription(line, position, description));
}

BOOST_AUTO_TEST_CASE(skip_many_spaces_after_id)
{
  const std::string line = "100 \t  Sneaky person";
  size_t id = 0;
  size_t position = 0;
  std::string description;

  BOOST_TEST(shaykhraziev::parseSizeTPrefix(line, id, position));
  BOOST_TEST(shaykhraziev::readRestDescription(line, position, description));
  BOOST_TEST(description == "Sneaky person");
}

BOOST_AUTO_TEST_CASE(quoted_description_is_plain_text)
{
  const std::string line = "56 \"Scarface\"";
  size_t id = 0;
  size_t position = 0;
  std::string description;

  BOOST_TEST(shaykhraziev::parseSizeTPrefix(line, id, position));
  BOOST_TEST(shaykhraziev::readRestDescription(line, position, description));
  BOOST_TEST(description == "\"Scarface\"");
}

BOOST_AUTO_TEST_CASE(parse_input_file_argument)
{
  std::string filename;

  BOOST_TEST(shaykhraziev::parseFileArg("in:input.txt", "in:", filename));
  BOOST_TEST(filename == "input.txt");
}

BOOST_AUTO_TEST_CASE(parse_output_file_argument)
{
  std::string filename;

  BOOST_TEST(shaykhraziev::parseFileArg("out:output.txt", "out:", filename));
  BOOST_TEST(filename == "output.txt");
}

BOOST_AUTO_TEST_CASE(reject_unknown_argument)
{
  std::string filename;

  BOOST_TEST(!shaykhraziev::parseFileArg("data:input.txt", "in:", filename));
  BOOST_TEST(!shaykhraziev::parseFileArg("data:input.txt", "out:", filename));
}

BOOST_AUTO_TEST_CASE(reject_empty_filename_argument)
{
  std::string filename;

  BOOST_TEST(!shaykhraziev::parseFileArg("in:", "in:", filename));
  BOOST_TEST(!shaykhraziev::parseFileArg("out:", "out:", filename));
}

BOOST_AUTO_TEST_CASE(parse_u1_arguments)
{
  char program[] = "lab";
  char inputArg[] = "in:input.txt";
  char outputArg[] = "out:output.txt";
  char* argv[] = { program, inputArg, outputArg };
  bool hasInput = false;
  bool hasOutput = false;
  std::string input;
  std::string output;

  BOOST_TEST(shaykhraziev::parseU1Args(3, argv, hasInput, input, hasOutput, output));
  BOOST_TEST(hasInput);
  BOOST_TEST(input == "input.txt");
  BOOST_TEST(hasOutput);
  BOOST_TEST(output == "output.txt");
}

BOOST_AUTO_TEST_CASE(reject_repeated_u1_arguments)
{
  char program[] = "lab";
  char firstInputArg[] = "in:first.txt";
  char secondInputArg[] = "in:second.txt";
  char* argv[] = { program, firstInputArg, secondInputArg };
  bool hasInput = false;
  bool hasOutput = false;
  std::string input;
  std::string output;

  BOOST_TEST(!shaykhraziev::parseU1Args(3, argv, hasInput, input, hasOutput, output));
}

BOOST_AUTO_TEST_CASE(reject_unknown_u1_argument)
{
  char program[] = "lab";
  char unknownArg[] = "data:input.txt";
  char* argv[] = { program, unknownArg };
  bool hasInput = false;
  bool hasOutput = false;
  std::string input;
  std::string output;

  BOOST_TEST(!shaykhraziev::parseU1Args(2, argv, hasInput, input, hasOutput, output));
}

BOOST_AUTO_TEST_CASE(person_has_required_fields)
{
  shaykhraziev::Person person = { 1, "info" };

  BOOST_TEST(person.id == 1);
  BOOST_TEST(person.info == "info");
}
