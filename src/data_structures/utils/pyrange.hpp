#include <numeric>
#include <range/v3/all.hpp>

template<class T = size_t>
class pyrange : public ranges::view_facade<pyrange<T>>
{
    T start, stop, stride;
    friend ranges::range_access;

    T read() const
    {
        return start;
    }

    bool equal(ranges::default_sentinel_t) const
    {
        return start != stop;
    }

    void next()
    {
        start += stride;
    }

public:
    pyrange() = default;

    pyrange(T stop)
      : pyrange(0, stop)
    {}

    pyrange(T start, T stop)
      : pyrange(start, stop, stop < start ? -1 : 1)
    {}

    pyrange(T start, T stop, T stride)
      : start{start}
      , stop{stop}
      , stride{stride}
    {}
};
