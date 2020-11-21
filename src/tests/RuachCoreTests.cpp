//
// Created by SilverJun on 2020-11-16.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "core/Token.hpp"

TEST_CASE("Token class test", "[Token]") {
    using namespace ruach::core;

    SECTION("Literal integer token") {
        auto* token = new Token{TokenID::Literal_Integer, 1, "test.ruach", 10};
        REQUIRE(token->Is(TokenID::Literal_Integer));
        REQUIRE(token->GetLine() == 1);
        REQUIRE(token->GetSourceName() == std::string("test.ruach"));
        REQUIRE(token->GetValue<int>() != std::nullopt);
        REQUIRE(token->GetValue<int>().value() == 10);
        delete token;
    }

    SECTION("Literal bool token") {
        auto* trueToken = new Token{TokenID::Literal_Boolean, 1, "test.ruach", true};
        auto* falseToken = new Token{TokenID::Literal_Boolean, 1, "test.ruach", false};
        REQUIRE(trueToken->Is(TokenID::Literal_Boolean));
        REQUIRE(trueToken->GetValue<bool>() != std::nullopt);
        REQUIRE(trueToken->GetValue<bool>().value() == true);
        REQUIRE(falseToken->Is(TokenID::Literal_Boolean));
        REQUIRE(falseToken->GetValue<bool>() != std::nullopt);
        REQUIRE(falseToken->GetValue<bool>().value() == false);
        delete trueToken;
        delete falseToken;
    }

    SECTION("Literal float token") {
        auto* token = new Token{TokenID::Literal_Float, 1, "test.ruach", 3.14f};
        REQUIRE(token->Is(TokenID::Literal_Float));
        REQUIRE(token->GetValue<float>() != std::nullopt);
        REQUIRE(token->GetValue<float>().value() == 3.14f);
        delete token;
    }

    SECTION("Literal letter token") {
        auto* token = new Token{TokenID::Literal_Letter, 1, "test.ruach", 's'};
        REQUIRE(token->Is(TokenID::Literal_Letter));
        REQUIRE(token->GetValue<char>().value() == 's');
        delete token;
    }

    SECTION("Literal string token") {
        auto* token = new Token(TokenID::Literal_String, 1, "test.ruach", std::string("test"));
        REQUIRE(token->Is(TokenID::Literal_String));
        REQUIRE(token->GetValue<std::string>().value() == std::string("test"));
        delete token;
    }
}

TEST_CASE("Token use-case test", "[Token]") {
    SECTION("No value token") {
        using namespace ruach::core;
        auto* token = new Token{TokenID::Eof, 1, "test.ruach"};
        REQUIRE(token->Is(TokenID::Eof));
        REQUIRE(token->GetLine() == 1);
        REQUIRE(token->GetSourceName() == std::string("test.ruach"));
        REQUIRE(token->GetValue<int>() == std::nullopt);
        REQUIRE(token->CheckValueType<int>() == false);
        delete token;
    }

//    SECTION("Variant Test") {
//        using namespace std::string_literals;
//        std::variant<std::string, bool> testVar("test");
//        REQUIRE(testVar.index() == 1); // why this is not 0 ????????
//
//        std::variant<std::string, bool> testVar2(std::string("test"));
//        REQUIRE(testVar.index() == 0);
//    }
}

#include "core/Object.h"

TEST_CASE("Variable test", "[Object]") {
    using namespace ruach::core;
    SECTION("check variable") {
        auto* variable = new Object("test", Object::Type::Variable, {Lifecycle::Block, AccessRange::Local, Constancy::Mutable});

        REQUIRE(variable->GetName() == "test");
        REQUIRE(variable->GetType() == Object::Type::Variable);
        REQUIRE(variable->GetLifecycle() == Lifecycle::Block);
        REQUIRE(variable->GetAccessRange() == AccessRange::Local);
        REQUIRE(variable->GetConstancy() == Constancy::Mutable);

        auto cloneVariable = variable->Clone();
        REQUIRE(cloneVariable.get() != variable);
        REQUIRE(cloneVariable->GetName() == variable->GetName());
        REQUIRE(cloneVariable->GetType() == variable->GetType());
        REQUIRE(cloneVariable->GetLifecycle() == variable->GetLifecycle());
        REQUIRE(cloneVariable->GetAccessRange() == variable->GetAccessRange());
        REQUIRE(cloneVariable->GetConstancy() == variable->GetConstancy());

        delete variable;
    }
}
