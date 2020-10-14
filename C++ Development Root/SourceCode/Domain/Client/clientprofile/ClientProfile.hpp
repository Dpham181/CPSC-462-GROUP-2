#pragma once

#include <string>

#include "Domain/Client/ClientHandler.hpp"

namespace Domain::ClientProfile
{
  
  class ClientProfile : public Domain::Client::ClientHandler
  {
    public:
      // Constructors
      using ClientHandler::ClientHandler;  // inherit constructors

      // Operations

     ~ClientProfile() noexcept override;
  }; // class Books


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ClientProfile::~ClientProfile() noexcept
  {}


}  // namespace Domain::ClientProfile
