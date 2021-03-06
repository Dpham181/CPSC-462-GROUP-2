#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>   // domain_error, runtime_error
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::Client
{
  
    using TechnicalServices::Persistence::Client; 
    using TechnicalServices::Persistence::Clientprofile;
    using TechnicalServices::Persistence::UserCredentials;

  // Client Package within the Domain Layer Abstract class
  class ClientHandler
  {
    public:
      struct ClientException : std::runtime_error   {using runtime_error       ::runtime_error;};
      struct   NoSuchClient         : ClientException {using ClientException::ClientException;};
      struct   NoSuchProperty     : ClientException {using ClientException::ClientException;};
      // object return client, creator
     static std::unique_ptr<ClientHandler> UseClientManagement( const UserCredentials& User);

      //  Operations menu
     virtual std::vector<std::string> getCommandsClient() =0;    // retrieves the list of actions (commands)
     virtual std::any                 executeCommandClient(const std::string& command, const std::vector<std::string>& args) =0;    // executes one of the actions retrieved
    


   // Operations of management client
     // default operations
     virtual Clientprofile                       SearchClientId(const int ClientId) =0;
     virtual std::vector<Client>                 ClientsDB(const std::vector<Client>& ClientsDB) =0;
     virtual std::vector<Clientprofile>          ClientsPDB(const std::vector<Clientprofile>& ClientsPDB) = 0;
  
     
     // Usecase Operations
     virtual void                                ViewClients(const std::vector<Client>& ClientsDB) =0;
     virtual std::vector<Client>                 addClient(const Client& Client) =0;
     virtual std::vector<Clientprofile>                   UpdateClientProfile( const int ClientID, const std::string DOB, const int Income) = 0;


      

      virtual ~ClientHandler() noexcept = 0;


      protected :
        // Copy assignment operators, protected to prevent mix derived-type assignments
        ClientHandler &
        operator=( const ClientHandler & rhs ) = default;                // copy assignment
        ClientHandler & operator=( ClientHandler && rhs ) = default;    // move assignment
 
  };    // class ClientHandler


} // namespace Domain::Client
