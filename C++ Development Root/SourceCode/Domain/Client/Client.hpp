#pragma once
#include <string>
#include <memory>
#include <string>
#include <vector>

#include "Domain/Client/ClientHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::Client
{
 
  class ClientDomain : public ClientHandler
  {
    public:
        
        ClientDomain(const std::string& description, const UserCredentials& user);

      //  Operations menu
       std::vector<std::string> getCommandsClient() override;    // retrieves the list of actions (commands)
       std::any                 executeCommandClient(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

      // Operations
       std::vector<Client>                 ClientsDB(const std::vector<Client>& ClientsDB) override;
       std::vector<Clientprofile>          ClientsPDB(const std::vector<Clientprofile>& ClientsPDB) override;
       void                                ViewClients(const std::vector<Client>& ClientsDB) override;
       Clientprofile                       SearchClientId(const int ClientId) override;
       std::vector<Client>                 addClient(const Client &Client  ) override;
       std::vector<Clientprofile>          UpdateClientProfile( const int ClientID, const std::string DOB, const int Income) override ;

      ~ClientDomain() noexcept override = 0 ;
  protected:
  public:  
      using DispatchTable = std::map<std::string, std::any(*)(Domain::Client::ClientDomain&, const std::vector<std::string>&)>;

      friend class Policy;

      // Instance Attributes
      std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;
      std::vector<Client>                               _UpdatedDB;
      std::vector<Clientprofile>                        _UpdatedprofileDB;
      std::string     const                             _name = "Undefined";
      Clientprofile                                     _Clientprofile;
      DispatchTable                                    _commandDispatch;
      UserCredentials const                                      _Creator;

  private:
      
  }; // class Client


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ClientDomain::~ClientDomain() noexcept
  {
      _logger << "Session \"" + _name + "\" shutdown successfully";

  }
  struct ClientManagement : ClientDomain { ClientManagement(const UserCredentials& user); };

 

}  // namespace Domain::Client
