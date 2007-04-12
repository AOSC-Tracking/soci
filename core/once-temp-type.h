//
// Copyright (C) 2004-2007 Maciej Sobczak, Stephen Hutton
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SOCI_ONCE_TEMP_TYPE_H_INCLUDED
#define SOCI_ONCE_TEMP_TYPE_H_INCLUDED

#include "prepare-temp-type.h"
#include "ref-counted-statement.h"

namespace soci
{
class session;

namespace details
{
// this needs to be lightweight and copyable
class SOCI_DECL once_temp_type
{
public:

    once_temp_type(session &s);
    once_temp_type(once_temp_type const &o);
    once_temp_type & operator=(once_temp_type const &o);

    ~once_temp_type();

    template <typename T>
    once_temp_type & operator<<(T const &t)
    {
        rcst_->accumulate(t);
        return *this;
    }

    once_temp_type & operator,(into_type_ptr const &);
    once_temp_type & operator,(use_type_ptr const &);

private:
    ref_counted_statement *rcst_;
};

// this needs to be lightweight and copyable
class once_type
{
public:
    once_type(session *s) : session_(s) {}

    template <typename T>
    once_temp_type operator<<(T const &t)
    {
        once_temp_type o(*session_);
        o << t;
        return o;
    }

private:
    session *session_;
};


// this needs to be lightweight and copyable
class prepare_type
{
public:
    prepare_type(session *s) : session_(s) {}

    template <typename T>
    prepare_temp_type operator<<(T const &t)
    {
        prepare_temp_type p(*session_);
        p << t;
        return p;
    }

private:
    session *session_;
};

} // namespace details
} // namespace soci

#endif