#pragma once

#include <string>;

namespace Domain::Client
{
    struct ClientProfile
    {
      int         clientID;
      std::string client_name;
      std::string DOB;
      int         phone;
      int         income;
      std:: string Creator; 
    };

  // Library Package within the Domain Layer Abstract class
  class ClientHandler
  {
    public:


      // Operations
      //   Work in progress ...
      virtual ClientProfile newClient( const std::string & key );
      virtual ClientProfile modifyClientInformation( const std::string client_name, const std::string DOB, const int phone, const int income );



      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~ClientHandler() noexcept = 0;

    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      ClientHandler & operator=( const ClientHandler &  rhs ) = default;  // copy assignment
      ClientHandler & operator=(       ClientHandler && rhs ) = default;  // move assignment

  };    // class MaintainBooksHandler





  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ClientHandler::~ClientHandler() noexcept = default;


} // namespace Domain::Library
