#pragma once

#include "Domain/Client/ClientHandler.hpp"

namespace Domain::Client
{
  class Client : public Domain::Client::ClientHandler
  {
    public:
      // Constructors
      using ClientHandler::ClientHandler;  // inherit constructors

      // Operations

     ~Client() noexcept override;
  }; // class Books


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Client::~Client() noexcept
  {}


}  // namespace Domain::Client
