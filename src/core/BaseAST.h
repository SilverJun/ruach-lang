//
// Created by SilverJun on 2020-11-16.
//

#ifndef RUACH_LANG_BASEAST_H
#define RUACH_LANG_BASEAST_H

#include <vector>
#include <memory>

#include "Token.hpp"

namespace ruach::core {
    class BaseAST
    {
    public:
        using Ptr = std::unique_ptr<BaseAST>;
        using List = std::vector<Ptr>;

        BaseAST() = default;
        virtual ~BaseAST() = default;

        static Ptr Create(Token::Iter& iter);
        virtual void Dump() {}
        virtual void CodeGen() {}
    };
}

#endif //RUACH_LANG_BASEAST_H
