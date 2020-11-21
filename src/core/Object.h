//
// Created by SilverJun on 2020-11-16.
//

#ifndef RUACH_LANG_OBJECT_H
#define RUACH_LANG_OBJECT_H

#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <unordered_map>

namespace ruach::core {

    // TODO : 다른 파일로 옮기기.
    enum class Lifecycle
    {
        None,
        Block,
        Forever,
    };

    enum class AccessRange
    {
        None,
        Local,
        Global
    };

    enum class Constancy
    {
        None,
        Mutable,
        Immutable
    };

    /**
     * \brief Implementation of first-class object.
     */
    class Object final
    {
    public:
        using Ptr = std::unique_ptr<Object>;
        using List = std::vector<Ptr>;
        using Iter = List::iterator;
        using Table = std::unordered_map<std::string, Ptr>;
        using Attribute = std::tuple<Lifecycle, AccessRange, Constancy>;

        enum class Type
        {
            None,
            Variable,
            Array,
            Dictionary,
            Function,
        };

        Object() = delete;
        Object(Object&) = delete;
        Object(const Object&) = delete;
        Object& operator=(const Object&) = delete;
        ~Object() = default;

        explicit Object(std::string, Type, Lifecycle, AccessRange, Constancy);
        explicit Object(std::string, Type, Attribute);

        [[nodiscard]] std::string_view GetName() const;
        [[nodiscard]] Type GetType() const;
        [[nodiscard]] Attribute GetAttribute() const;
        [[nodiscard]] Lifecycle GetLifecycle() const;
        [[nodiscard]] AccessRange GetAccessRange() const;
        [[nodiscard]] Constancy GetConstancy() const;

        [[nodiscard]] Object::Ptr Clone() const;
    private:
        std::string _name;
        Type _type;
        Attribute _attribute;
    };
}

#endif //RUACH_LANG_OBJECT_H
