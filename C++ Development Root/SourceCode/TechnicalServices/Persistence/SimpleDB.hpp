#pragma once

#include <memory>    // unique_ptr
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

#include "Domain/Client/ClientHandler.hpp"



namespace TechnicalServices::Persistence
{
  class SimpleDB : public TechnicalServices::Persistence::PersistenceHandler
  {
    public:
      using PersistenceHandler::PersistenceHandler;    // inherit constructors
      SimpleDB();


      // Operations
      std::vector<std::string> findRoles()                                       override;  // Returns list of all legal roles
      UserCredentials          findCredentialsByName( const std::string & name ) override;  // Returns credentials for specified user, throws NoSuchUser if user not found
      // Adaptation Data read only access.  Adaptation data is a Key/Value pair
      const std::string & operator[]( const std::string & key ) const override;


      ~SimpleDB() noexcept override;

    private:
      std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

      // convenience reference object enabling standard insertion syntax
      // This line must be physically after the definition of _loggerPtr
      TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;


      // Property data (Key/Value pairs) off-line modifiable by the end-user
      using AdaptationData = std::map<std::string /*Key*/, std::string /*Value*/>;
      AdaptationData _adaptablePairs;

  }; // class SimpleDB


  
}  // namespace TechnicalServices::Persistence
namespace Domain::Client
{
  class SimpleDB : public Domain::Client::ClientHandler
  {
  public:
    using ClientHandler::ClientHandler;    // inherit constructors
    SimpleDB();


    // Operations
    ClientProfile newClient( const std:: string & key ); 

    // Adaptation Data read only access.  Adaptation data is a Key/Value pair


    ~SimpleDB() noexcept override;

  private:
    

  };    // class SimpleDB



}    // namespace TechnicalServices::Persistence
