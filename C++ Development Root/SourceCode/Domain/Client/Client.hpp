#pragma once
#include <string>

#include "Domain/Client/ClientHandler.hpp"

namespace Domain::Client
{
 
  class ClientDomain : public ClientHandler
  {
    public:
        // object return user with creator 
        static std::unique_ptr<ClientHandler> createClient(const Client& client);

        //using ClientHandler::ClientHandler;
        //ClientDomain(const std::string username, const int ID);  // inherit constructors
      // Operations

      //virtual Client                 GetbackClient(const std::string username, const int ID) override;


      ~ClientDomain() noexcept override = 0 ;

  
  }; // class Books


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ClientDomain::~ClientDomain() noexcept
  {
  }

 

}  // namespace Domain::Library
