#pragma once

#include <vector>

namespace IO::Request
{
  template <typename Option> //
  class IRequest
  {
  public:
    /*------------------------------------------------------------------------*\
    *| [public]: Constructors                                                 |*
    \*------------------------------------------------------------------------*/

    IRequest(const IRequest&) = delete;
    IRequest(IRequest&&)      = delete;
    IRequest() noexcept       = default;

    /*------------------------------------------------------------------------*\
    *| [public]: Destructor                                                   |*
    \*------------------------------------------------------------------------*/

    virtual ~IRequest() noexcept = default;

    /*------------------------------------------------------------------------*\
    *| [public]: Operators                                                    |*
    \*------------------------------------------------------------------------*/

    auto operator=(const IRequest&) noexcept -> IRequest& = delete;
    auto operator=(IRequest&&) noexcept -> IRequest&      = delete;

    /*------------------------------------------------------------------------*\
    *| [public]: Methods                                                      |*
    \*------------------------------------------------------------------------*/

    virtual auto printResponse() -> void = 0;

    /*------------------------------------------------------------------------*\
    *| [public]: Mutators                                                     |*
    \*------------------------------------------------------------------------*/

    virtual auto setOptions(std::vector<Option>&& options) noexcept -> void = 0;
  };
} // namespace IO::Request
