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
        //ClientDomain(const std::string username, const int ID);  // inherit constructors


      // Operations
      virtual std::vector<Client>                 ClientsDB(const std::vector<Client>& ClientsDB) override;

      virtual std::vector<Client>                 addClient(const Client &Client  ) override;
      virtual Clientprofile                       UpdateClientProfile(const std::string ClientName, const int ClientID, const std::string DOB, const int Income, int Phone) override ;

      ~ClientDomain() noexcept override = 0 ;
  protected:
  public:  // Dispatched functions need access to these attributes, so for now make these public instead of protected
    // Types
      friend class Policy;

      // Instance Attributes
      std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;
      std::vector<Client>                               _UpdatedDB;
      Client const                                      _Client;
      std::string     const                                      _name = "Undefined";
      Clientprofile                                     _Clientprofile;
  private:
      
  }; // class Books


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ClientDomain::~ClientDomain() noexcept
  {
      _logger << "Session \"" + _name + "\" shutdown successfully";

  }
  struct ClientSession : ClientDomain { ClientSession(const Client& Client); };

 

}  // namespace Domain::Library
