#pragma once

#include <string>
#include <vector>
#include <stdexcept>    // domain_error, runtime_error

namespace Domain::Client
{
  struct Client
  {
    std::string Creator;
    int         ClientId;
  };
  struct ClientProfile
  {
    std::string Client_Name;
    int         Client_Id;
    std::string DOB;
    int         InCome;
    int         Phone;
  };
  // Library Package within the Domain Layer Abstract class
  class ClientHandler
  {
    public:
      struct ClientException : std::runtime_error   {using runtime_error       ::runtime_error;};
      struct   NoSuchClient         : ClientException {using ClientException::ClientException;};
      struct   NoSuchProperty     : ClientException {using ClientException::ClientException;};


      // Creation (Singleton)
      ClientHandler()                                  = default;
      ClientHandler( const ClientHandler & ) = delete;
      ClientHandler &             operator=( const ClientHandler & ) = delete;
      static ClientHandler & instance();



      // Operations
      
      virtual int GenerateClientId(std::string & User_name) = 0;
      virtual ClientProfile addClientInformation(int clientID, std::string client_name, std::string DOB, int income, int phone) = 0;
      virtual std::vector<Client> ShowAllClient()=0; 
      virtual ClientProfile SearchforClientinfor( int ClientID )=0;


      // Adaptation Data read only access.  Adaptation data is a Key/Value pair
      // Throws NoSuchProperty
      virtual const std::string & operator[]( const std::string & key ) const = 0;


      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~ClientHandler() noexcept = 0;

    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      ClientHandler & operator=( const ClientHandler &  rhs ) = default;  // copy assignment
      ClientHandler & operator=(       ClientHandler && rhs ) = default;  // move assignment

  };    // class ClientHandler





  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ClientHandler::~ClientHandler() noexcept = default;


} // namespace Domain::Client
