#pragma once

#include "Domain/Library/MaintainBooksHandler.hpp"

namespace Domain::Library
{
  class Books : public Domain::Library::MaintainBooksHandler
  {
    public:
      // Constructors
      using MaintainBooksHandler::MaintainBooksHandler;  // inherit constructors

      // Operations

     ~Books() noexcept override;
  }; // class Books


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Books::~Books() noexcept
  {}


}  // namespace Domain::Library
