//
// Created by SilverJun on 2020-11-16.
//

#include "Object.h"

namespace ruach::core
{


    Object::Object(std::string name, Type type, Lifecycle lifecycle, AccessRange accessRange, Constancy constancy)
            : _name(name)
            , _type(type)
            , _attribute(lifecycle, accessRange, constancy)
    {
    }

    Object::Object(std::string name, Type type, Object::Attribute attribute)
            : _name(name)
            , _type(type)
            , _attribute(attribute)
    {
    }

    Object::Attribute Object::GetAttribute() const {
        return _attribute;
    }

    std::string_view Object::GetName() const {
        return _name;
    }

    Object::Type Object::GetType() const {
        return _type;
    }

    Lifecycle Object::GetLifecycle() const {
        return std::get<Lifecycle>(_attribute);
    }

    AccessRange Object::GetAccessRange() const {
        return std::get<AccessRange>(_attribute);
    }

    Constancy Object::GetConstancy() const {
        return std::get<Constancy>(_attribute);
    }

    Object::Ptr Object::Clone() const {
        return std::make_unique<Object>(this->_name, this->_type, this->_attribute);
    }

}