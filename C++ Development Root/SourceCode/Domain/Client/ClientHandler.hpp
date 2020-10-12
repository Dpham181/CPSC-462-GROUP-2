#pragma once

#include <string>
#include <vector>
#include <stdexcept>    // domain_error, runtime_error
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include <any>

namespace Domain::Client
{
  
    using TechnicalServices::Persistence::Client; 
  // Library Package within the Domain Layer Abstract class
  class ClientHandler
  {
    public:
      struct ClientException : std::runtime_error   {using runtime_error       ::runtime_error;};
      struct   NoSuchClient         : ClientException {using ClientException::ClientException;};
      struct   NoSuchProperty     : ClientException {using ClientException::ClientException;};

      // object return user with creator 
      static std::unique_ptr<ClientHandler> createClient( const Client & client );


      // 
       virtual std::vector<std::string> getCommands()                                                                        = 0;    // retrieves the list of actions (commands)
      virtual std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args ) = 0;    // Throws BadCommand

  
      // Operations
      

      virtual ~ClientHandler() noexcept = 0;


      protected :
        // Copy assignment operators, protected to prevent mix derived-type assignments
        ClientHandler &
        operator=( const ClientHandler & rhs ) = default;                // copy assignment
        ClientHandler & operator=( ClientHandler && rhs ) = default;    // move assignment
 

  };    // class ClientHandler






} // namespace Domain::Client
