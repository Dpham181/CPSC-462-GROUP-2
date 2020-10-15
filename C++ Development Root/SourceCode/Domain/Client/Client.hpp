#pragma once
#include <string>

#include "Domain/Client/ClientHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::Client
{
 
  class ClientDomain : public ClientHandler
  {
    public:
        
        ClientDomain(const std::string& description, const Client& Client);


      // Operations
      virtual std::vector<Client>                 ClientsDB(const std::vector<Client>& ClientsDB) override;
      virtual std::vector<Clientprofile>          ClientsPDB(const std::vector<Clientprofile>& ClientsPDB) override;

      virtual std::vector<Client>                 addClient(const Client &Client  ) override;
      virtual Clientprofile                       UpdateClientProfile(const std::string ClientName, const int ClientID, const std::string DOB, const int Income, int Phone) override ;

      ~ClientDomain() noexcept override = 0 ;
  protected:
  public:  
      friend class Policy;

      // Instance Attributes
      std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;
      std::vector<Client>                               _UpdatedDB;
      std::vector<Clientprofile>                        _UpdatedprofileDB;
      std::string     const                             _name = "Undefined";
      Client const                                      _Client;
      Clientprofile                                     _Clientprofile;
  private:
      
  }; // class Client


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ClientDomain::~ClientDomain() noexcept
  {
      _logger << "Session \"" + _name + "\" shutdown successfully";

  }
  struct ClientSession : ClientDomain { ClientSession(const Client& Client); };

 

}  // namespace Domain::Client
