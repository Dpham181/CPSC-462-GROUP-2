#pragma once

#include <memory>    // unique_ptr
#include <string>
#include <vector>

#include "Domain/Client/ClientHandler.hpp"


namespace Domain::Client
{
  class ClientDB : public Domain::Client::ClientHandler
  {
  public:
    using ClientHandler::ClientHandler;    // inherit constructors
    ClientDB();


    // Operations
    
    int                 GenerateClientId(  std::string & User_name ) override;
    ClientProfile       addClientInformation( int clientID, std::string client_name, std::string DOB, int income, int phone ) override;
    std::vector<Client> ShowAllClient() override;
    ClientProfile       SearchforClientinfor( int ClientID ) override;

    // Adaptation Data read only access.  Adaptation data is a Key/Value pair
    //const std::string & operator[]( const std::string & key ) const override;


    ~ClientDB() noexcept override;

}
