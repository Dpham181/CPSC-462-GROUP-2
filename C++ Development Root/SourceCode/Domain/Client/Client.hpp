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
        
        ClientDomain(const std::string& description, const Client& Client);

      //  Operations menu
       std::vector<std::string> getCommands() override;    // retrieves the list of actions (commands)
       std::any                 executeCommand(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

      // Operations
       std::vector<Client>                 ClientsDB(const std::vector<Client>& ClientsDB) override;
       std::vector<Clientprofile>          ClientsPDB(const std::vector<Clientprofile>& ClientsPDB) override;

       std::vector<Client>                 addClient(const Client &Client  ) override;
       Clientprofile                       UpdateClientProfile(const std::string ClientName, const int ClientID, const std::string DOB, const int Income, int Phone) override ;

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
      Client const                                      _Client;
      Clientprofile                                     _Clientprofile;
      DispatchTable                                    _commandDispatch;

  private:
      
  }; // class Client


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ClientDomain::~ClientDomain() noexcept
  {
      _logger << "Session \"" + _name + "\" shutdown successfully";

  }
  struct ClientManagement : ClientDomain { ClientManagement(const Client& Client); };

 

}  // namespace Domain::Client
