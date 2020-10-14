#pragma once
#include <string>

#include "Domain/Client/ClientHandler.hpp"

namespace Domain::Client
{
 
  class Clientsection : public ClientHandler
  {
    public:

      Clientsection(const std::string& description, const Client& client);

      // Operations

      std::vector<std::string> getCommands()                                                                     override;    // retrieves the list of actions (commands)
      std::any                 executeCommand(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved


      ~Clientsection() noexcept override = 0 ;

  protected:
  public:  // Dispatched functions need access to these attributes, so for now make these public instead of protected
      using DispatchTable = std::map<std::string, std::any(*)(Domain::Client::Clientsection&, const std::vector<std::string>&)>;
      friend class Policy;

      Client const                                      _Client;
      int const                                         _ClientID; 
      std::string     const                                      _Creator = "Undefined";
      DispatchTable                                              _commandDispatch;

  }; // class Books


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Clientsection::~Clientsection() noexcept
  {}

  struct ClientID : Clientsection { ClientID(const Client& client); };

}  // namespace Domain::Library
