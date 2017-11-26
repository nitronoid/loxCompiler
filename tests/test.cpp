#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "lexer.h"
#include <tuple>
#include <typeinfo>

template<typename T, size_t size>
::testing::AssertionResult ArraysMatch(const T (&expected)[size],
                                       const T (&actual)[size]){
  for (size_t i(0); i < size; ++i){
    if (expected[i] != actual[i]){
      return ::testing::AssertionFailure() << "array[" << i
                                           << "] (" << actual[i] << ") != expected[" << i
                                           << "] (" << expected[i] << ")";
    }
  }

  return ::testing::AssertionSuccess();
}

namespace
{
ErrorReporter testErrorReporter;
std::pair<std::vector<Token>,std::vector<Token>> testSingleString(const std::string &_str)
{
  Lexer lexer(testErrorReporter);
  std::vector<Token> expected {Token(TokenType::STRING, _str, 1), Token(TokenType::END,"",1)};
  std::vector<Token> result = lexer.lex('"'+_str+'"');
  return {result, expected};
}

TEST(Lexer_test_Strings, basic)
{
  auto [result, expected] = testSingleString("hi");
  EXPECT_THAT(result, ::testing::ElementsAreArray(expected));
}

TEST(Lexer_test_Strings, spaces)
{
  Lexer lexer(testErrorReporter);
  std::vector<Token> expected {Token(TokenType::STRING,"hi there",1), Token(TokenType::END,"",1)};
  std::vector<Token> result = lexer.lex("\"hi there\"");
  EXPECT_THAT(result, ::testing::ElementsAreArray(expected));
}

TEST(Lexer_test_Strings, operators)
{
  Lexer lexer(testErrorReporter);
  std::vector<Token> expected {Token(TokenType::STRING,"&*+-h_=<ello;",1), Token(TokenType::END,"",1)};
  std::vector<Token> result = lexer.lex("\"&*+-h_=<ello;\"");
  EXPECT_THAT(result, ::testing::ElementsAreArray(expected));
}

//TEST(Lexer_test_Strings, operators)
//{
//  Lexer lexer(testErrorReporter);
//  std::vector<Token> expected {Token(TokenType::STRING,"&*+-h_=<ello;",1), Token(TokenType::END,"",1)};
//  std::vector<Token> result = lexer.lex("\"&*+-h_=<ello;\"");
//  EXPECT_THAT(result, ::testing::ElementsAreArray(expected));
//}

//TEST(Lexer_test_Strings, operators)
//{
//  Lexer lexer(testErrorReporter);
//  std::vector<Token> expected {Token(TokenType::STRING,"&*+-h_=<ello;",1), Token(TokenType::END,"",1)};
//  std::vector<Token> result = lexer.lex("\"&*+-h_=<ello;\"");
//  EXPECT_THAT(result, ::testing::ElementsAreArray(expected));
//}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
