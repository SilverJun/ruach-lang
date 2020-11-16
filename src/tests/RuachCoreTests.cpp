//
// Created by SilverJun on 2020-11-16.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "core/Token.hpp"

TEST_CASE("Literal integer token", "[Token]") {
    using namespace ruach::core;
    auto token = new Token{TokenID::Literal_Integer, 1, "test.ruach", 10};
    REQUIRE(token->Is(TokenID::Literal_Integer));
    REQUIRE(token->GetLine() == 1);
    REQUIRE(token->GetSourceName() == std::string("test.ruach"));
    REQUIRE(token->GetValue<int>().value() == 10);
}

TEST_CASE("Literal letter token", "[Token]") {
    using namespace ruach::core;
    auto token = new Token{TokenID::Literal_Letter, 1, "test.ruach", 's'};
    REQUIRE(token->Is(TokenID::Literal_Letter));
    REQUIRE(token->GetLine() == 1);
    REQUIRE(token->GetSourceName() == std::string("test.ruach"));
    REQUIRE(token->GetValue<char>().value() == 's');
}

TEST_CASE("Literal string token", "[Token]") {
    using namespace ruach::core;
    auto token = new Token(TokenID::Literal_String, 1, "test.ruach", std::string("test"));
    REQUIRE(token->Is(TokenID::Literal_String));
    REQUIRE(token->GetLine() == 1);
    REQUIRE(token->GetSourceName() == std::string("test.ruach"));
    REQUIRE(token->GetValue<std::string>().value() == std::string("test"));
}

TEST_CASE("No value token", "[Token]") {
    using namespace ruach::core;
    auto token = new Token{TokenID::Eof, 1, "test.ruach"};
    REQUIRE(token->Is(TokenID::Eof));
    REQUIRE(token->GetLine() == 1);
    REQUIRE(token->GetSourceName() == std::string("test.ruach"));
    REQUIRE(token->CheckValueType<int>() == false);
}

TEST_CASE("Variant Test", "[Token]") {
    using namespace std::string_literals;
    std::variant<std::string, bool> testVar("test");
    REQUIRE(testVar.index() == 0); // why this is not 0 ????????
}