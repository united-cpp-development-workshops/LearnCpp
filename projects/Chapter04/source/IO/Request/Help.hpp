#pragma once

#include "Foundation/types.hpp"

#include "IO/Request/IRequest.hpp"

#include <vector>

namespace IO::Request
{
  enum class HelpOption : fn::u8f
  {
  };

  class Help : public IRequest<HelpOption>
  {
  public:
    /*------------------------------------------------------------------------*\
    *| [public]: Constructors                                                 |*
    \*------------------------------------------------------------------------*/

    Help(const Help&) = delete;
    Help(Help&&)      = delete;
    Help() noexcept   = default;

    /*------------------------------------------------------------------------*\
    *| [public]: Destructor                                                   |*
    \*------------------------------------------------------------------------*/

    ~Help() noexcept override = default;

    /*------------------------------------------------------------------------*\
    *| [public]: Operators                                                    |*
    \*------------------------------------------------------------------------*/

    auto operator=(const Help&) noexcept -> Help& = delete;
    auto operator=(Help&&) noexcept -> Help&      = delete;

    /*------------------------------------------------------------------------*\
    *| [public]: Methods                                                      |*
    \*------------------------------------------------------------------------*/

    auto printResponse() -> void final;

    /*------------------------------------------------------------------------*\
    *| [public]: Mutators                                                     |*
    \*------------------------------------------------------------------------*/

    auto setOptions(std::vector<HelpOption>&& options) noexcept -> void final;

  private:
    /*------------------------------------------------------------------------*\
    *| [private]: Fields                                                      |*
    \*------------------------------------------------------------------------*/

    std::vector<HelpOption> m_options;
  };
} // namespace IO::Request
