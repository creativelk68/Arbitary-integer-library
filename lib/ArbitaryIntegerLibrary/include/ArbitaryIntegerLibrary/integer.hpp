#pragma once

#include "integer.h"

#include <ostream>

namespace Arbitary
{
    class Integer
    {
        Integer_struct m_integer;

    public:

        inline Integer() : m_integer(construct_integer()) {}

        explicit inline Integer(const int32_t& value) : m_integer(construct_integer_from_int32(value)) {}

        explicit inline Integer(const uint32_t& value) : m_integer(construct_integer_from_uint32(value)) {}

        inline ~Integer() { destruct_integer(&m_integer); }


        void dump() const;

        inline bool get_is_negative() const { return m_integer.is_negative; }

        inline size_t get_size() const { return m_integer.size; }


        inline unsigned* get_digits() { return m_integer.digits; }

        inline const unsigned* get_digits() const { return m_integer.digits; }

        inline unsigned get_digit(const size_t& index) const { return m_integer.digits[index]; }
    };

    std::ostream& operator<<(std::ostream& os, const Arbitary::Integer& integer);

} // namespace Integer
