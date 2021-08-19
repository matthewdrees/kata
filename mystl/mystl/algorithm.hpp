#include <iterator>

template <class InputIt, class UnaryPredicate>
constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p)
{
    for (auto it = first; it != last; ++it)
    {
        if (!p(*it))
        {
            return false;
        }
    }
    return true;
}

template <class InputIt, class UnaryPredicate>
constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p)
{
    for (auto it = first; it != last; ++it)
    {
        if (p(*it))
        {
            return true;
        }
    }
    return false;
}

template <class InputIt, class UnaryPredicate>
constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p)
{
    return !any_of(first, last, p);
}

template <class InputIt, class UnaryFunction>
constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
    for (auto it = first; it != last; ++it)
    {
        f(*it);
    }
    return f;
}

template <class InputIt, class Size, class UnaryFunction>
constexpr InputIt for_each_n(InputIt first, Size n, UnaryFunction f)
{
    auto it = first;
    for (; it != first + n; ++it)
    {
        f(*it);
    }
    return it;
}

template <class InputIt, class T>
constexpr typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T &value)
{
    typename std::iterator_traits<InputIt>::difference_type n = 0;
    for (auto it = first; it != last; ++it)
    {
        if (*it == value)
        {
            ++n;
        }
    }
    return n;
}

template <class InputIt, class UnaryPredicate>
constexpr typename std::iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPredicate p)
{
    typename std::iterator_traits<InputIt>::difference_type n = 0;
    for (auto it = first; it != last; ++it)
    {
        if (p(*it))
        {
            ++n;
        }
    }
    return n;
}

template <class InputIt1, class InputIt2>
constexpr std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1,
         InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (!(*first1 == *first2))
        {
            break;
        }
    }
    return {first1, first2};
}

template <class InputIt, class T>
constexpr InputIt find(InputIt first, InputIt last, const T &value)
{
    for (; first != last; ++first)
    {
        if (*first == value)
        {
            break;
        }
    }
    return first;
}

template <class InputIt, class UnaryPredicate>
constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first)
    {
        if (p(*first))
        {
            break;
        }
    }
    return first;
}

template <class InputIt, class UnaryPredicate>
constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p)
{
    for (; first != last; ++first)
    {
        if (!p(*first))
        {
            break;
        }
    }
    return first;
}

template <class ForwardIt1, class ForwardIt2>
constexpr ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
                              ForwardIt2 s_first, ForwardIt2 s_last)
{
    if (s_first == s_last)
    {
        return last;
    }
    auto ret = last;
    for (; first != last; ++first)
    {
        auto s_it = s_first;
        for (auto it = first; it != last && s_it != s_last; ++it, ++s_it)
        {
            if (!(*it == *s_it))
            {
                break;
            }
        }
        if (s_it == s_last)
        {
            ret = first;
        }
    }
    return ret;
}

template <class InputIt, class ForwardIt>
constexpr InputIt find_first_of(InputIt first, InputIt last,
                                ForwardIt s_first, ForwardIt s_last)
{
    for (; first != last; ++first)
    {
        for (auto it = s_first; it != s_last; ++it)
        {
            if (*first == *it)
            {
                return first;
            }
        }
    }
    return last;
}

template <class ForwardIt>
constexpr ForwardIt adjacent_find(ForwardIt first, ForwardIt last)
{
    if (first == last)
    {
        return last;
    }
    auto next = first;
    while (++next != last)
    {
        if (*first == *next)
        {
            return first;
        }
        first = next;
    }
    return last;
}

template <class ForwardIt1, class ForwardIt2>
constexpr ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 s_first, ForwardIt2 s_last)
{
    if (s_first == s_last)
    {
        return last;
    }
    auto range_last = first;
    for (auto s_it = s_first; ++s_it != s_last && range_last != last; ++range_last)
    {
    }
    for (; range_last != last; ++first, ++range_last)
    {
        // Could replace this with ::equal once it exists.
        auto s_it = s_first;
        for (auto it = first; s_it != s_last; ++it, ++s_it)
        {
            if (!(*it == *s_it))
            {
                break;
            }
        }
        if (s_it == s_last)
        {
            return first;
        }
    }
    return last;
}

template <class ForwardIt, class Size, class T>
constexpr ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T &value)
{
    if (count <= 0)
    {
        return first;
    }
    Size run_count = 0;
    auto run_start = last;
    for (; first != last; ++first)
    {
        if (*first == value)
        {
            if (run_count == 0)
            {
                run_start = first;
            }
            ++run_count;
            if (run_count == count)
            {
                return run_start;
            }
        }
        else
        {
            run_count = 0;
        }
    }
    if (run_count == count)
    {
        return run_start;
    }
    else
    {
        return last;
    }
}

template <class InputIt, class OutputIt>
constexpr OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
    while (first != last)
    {
        *d_first++ = *first++;
    }
    return d_first;
}

template <class InputIt, class OutputIt, class UnaryPredicate>
constexpr OutputIt copy_if(InputIt first, InputIt last,
                           OutputIt d_first,
                           UnaryPredicate pred)
{
    for (; first != last; ++first)
    {
        if (pred(*first))
        {
            *d_first++ = *first;
        }
    }
    return d_first;
}

template <class BidirIt1, class BidirIt2>
constexpr BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
    while (first != last)
    {
        *--d_last = *--last;
    }
    return d_last;
}

template <class InputIt, class OutputIt>
constexpr OutputIt move(InputIt first, InputIt last, OutputIt d_first)
{
    while (first != last)
    {
        *d_first++ = std::move(*first++);
    }
    return d_first;
}

template <class BidirIt1, class BidirIt2>
constexpr BidirIt2 move_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
    while (first != last)
    {
        *--d_last = std::move(*--last);
    }
    return d_last;
}

template <class ForwardIt, class T>
constexpr void fill(ForwardIt first, ForwardIt last, const T &value)
{
    while (first != last)
    {
        *first++ = value;
    }
}
