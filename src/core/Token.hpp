//
// Created by SilverJun on 2020-11-15.
//

#ifndef RUACH_LANG_TOKEN_HPP
#define RUACH_LANG_TOKEN_HPP

#include <string>
#include <string_view>
#include <vector>
#include <variant>
#include <optional>

namespace ruach::core
{
    enum class TokenID
    {
        Eof = 0,

        Comma = ',',
        Equal = '=',
        Quotation = '"',
        Cross = '+',
        Hyphen = '-',
        Asterisk = '*',
        ForwardSlash = '/',
        Percent = '%',
        Ampersand = '&',
        Bar = '|',
        Circumflex = '^',
        Less = '<',
        Great = '>',
        Exclamation = '!',
        OpenSmall = '(',
        CloseSmall = ')',
        OpenMedium = '{',
        CloseMedium = '}',
        OpenBig = '[',
        CloseBig = ']',
        Colon = ':',
        SemiColon = ';',
        Dot = '.',
        Wave = '~',
        Question = '?',

        Type_Var = 256,
        Type_Let,
        Type_Null,

        Type_Void,
        Type_Bool,
        Type_Char,
        Type_Int,
        Type_Float,
        Type_Double,
        Type_String,
        Type_Array,
        Type_Dictionary,
        Type_Tuple,
        Type_Ref,

        Type_UserDefined,

        Stmt_If,
        Stmt_Else,
        Stmt_Switch,
        Stmt_Case,
        Stmt_Default,
        Stmt_Guard,
        Stmt_While,
        Stmt_For,
        Stmt_In,
        Stmt_Break,
        Stmt_Return,

        Stmt_Public,
        Stmt_Private,
        Stmt_Inherit,	//protected

        Func_Decl,
        Func_Call,

        Struct_Decl,
        Enum_Decl,
        Class_Decl,
        Interface_Decl,

        Operator_Prefix,
        Operator_Infix,
        Operator_Postfix,
        Operator_Decl,
        Operator_Precedence,

        Operator,
        Operator_UserDefined,

        Identifier,	//변수나 클래스나 함수등 사용자 지정 이름

        Literal_Integer, //정수
        Literal_Float,
        Literal_Double, //부동소수점
        Literal_Letter,	//문자
        Literal_String,	//문자열
        Literal_Boolean,		/// true, false

        Assignment,

        Arithmetic_Add,
        Arithmetic_Subtract,
        Arithmetic_Multiply,
        Arithmetic_Divide,
        Arithmetic_Modulo,
        Arithmetic_Power,

        Relational_Equal,
        Relational_NotEqual,
        Relational_Greater,
        Relational_Less,
        Relational_GreaterEqual,
        Relational_LessEqual,

        Bitwise_And,
        Bitwise_Or,
        Bitwise_Not,
        Bitwise_Xor,
        Bitwise_ShiftRight,
        Bitwise_ShiftLeft,

        Logical_And,
        Logical_Or,
        Logical_Not,

        Optional_Nullable,		/// ?
        Optional_Binding,		/// !

        Range_Closed,	/// m...n : [m,n]
        Range_Opened,	/// m..<n : [m,n)

        Arrow,

        Casting_As,
        Casting_Is,
    };

    /**
     * \brief The token class.
     * This class represents the data when tokenizing source codes.
     */
    class Token final
    {
    public:
        using Value = std::variant<std::monostate, std::string, double, float, int, char, bool>;
        using Ptr = std::unique_ptr<Token>;
        using List = std::vector<Ptr>;
        using Iter = List::iterator;

        Token() = delete;
        Token(Token&) = delete;
        Token(const Token&) = delete;
        Token& operator=(const Token&) = delete;
        ~Token() = default;

        explicit Token(TokenID tokenId, int line, std::string sourceName)
                : _id(tokenId)
                , _line(line)
                , _sourceName(sourceName)
        {
        }

        explicit Token(TokenID tokenId, int line, std::string sourceName, Value value)
            : _id(tokenId)
            , _line(line)
            , _sourceName(sourceName)
            , _value(value)
        {
        }

        [[nodiscard]]
        constexpr bool Is(TokenID tokenId) const
        {
            return _id == tokenId;
        }

        [[nodiscard]]
        TokenID GetTokenID() const
        {
            return _id;
        }

        [[nodiscard]]
        int GetLine() const
        {
            return _line;
        }

        [[nodiscard]]
        std::string_view GetSourceName() const
        {
            return _sourceName;
        }

        [[nodiscard]]
        const Value& GetValue()
        {
            return _value;
        }

        template<typename T>
        constexpr bool CheckValueType()
        {
            return std::visit([](auto&& args){
                using ExactT = std::decay_t<decltype(args)>;
//                if constexpr (std::is_same_v<T, ExactT>)
//                {
//                    return true;
//                }
//                else
//                {
//                    return false;
//                }
                return std::is_same_v<T, ExactT>;
            }, _value);
        }

        template<typename T>
        [[nodiscard]]
        std::optional<T> GetValue()
        {
            // assert(_value.index() != 0);
            if (CheckValueType<T>())
            {
                return std::optional<T>(std::get<T>(_value));
            }
            else
            {
                return std::nullopt;
            }
        }

    private:
        const TokenID _id;
        const int _line;
        const std::string _sourceName;
        const Value _value;
    };
}

#endif //RUACH_LANG_TOKEN_HPP
