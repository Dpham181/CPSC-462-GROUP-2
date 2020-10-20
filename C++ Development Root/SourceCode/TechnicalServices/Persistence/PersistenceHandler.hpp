#pragma once

#include <map>
#include <stdexcept>    // domain_error, runtime_error
#include <string>
#include <vector>




namespace TechnicalServices::Persistence
{
  // Function argument type definitions
  
  struct User
  {
    int                       userID;
    std::string               userName;
    std::string               userRole;
    int                       commission;
  };

  struct UserCredentials
  {
    std::string               userName;
    std::string               passPhrase;
    std::vector<std::string>  roles;
    int                       status;
  };
  
  struct Client
  {
    std::string creator;
    int         clientid; 
    std::string client_name;
    int         phone;
  };
  struct Clientprofile
  {
    int         client_id;
    std::string dob;
    int         income;  
  };

  struct Product
  {
      int         id;
      std::string Name;
      int         Price;
  };

  // Persistence Package within the Technical Services Layer Abstract class
  // Singleton Class - only one instance of the DB exists for the entire system
  class PersistenceHandler
  {
    public:
      // Exceptions
      struct PersistenceException : std::runtime_error   {using runtime_error       ::runtime_error;};
      struct   NoSuchUser         : PersistenceException {using PersistenceException::PersistenceException;};
      struct   NoSuchProperty     : PersistenceException {using PersistenceException::PersistenceException;};

      // Creation (Singleton)
      PersistenceHandler            (                            ) = default;
      PersistenceHandler            ( const PersistenceHandler & ) = delete;
      PersistenceHandler & operator=( const PersistenceHandler & ) = delete;
      static  PersistenceHandler & instance();


      // Operations
      virtual std::vector<std::string> findRoles()                                       = 0;   // Returns list of all legal roles
      virtual UserCredentials          findCredentialsByName( const std::string & name ) = 0;   // Returns credentials for specified user, throws NoSuchUser if user not found
      
      // client operations
      
     
       virtual std::vector<Client> ShowAllClients() = 0;
       virtual std::vector<Clientprofile> ShowAllClientsProfile() = 0;
       virtual std::vector<Product> CRMInventory() =0 ;
    
       virtual std::vector<User> ShowAllUsers() = 0;
       virtual std::vector<UserCredentials> ShowAllUserProfiles() = 0;


      // Adaptation Data read only access.  Adaptation data is a Key/Value pair
      // Throws NoSuchProperty
      virtual const std::string & operator[]( const std::string & key ) const = 0;

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~PersistenceHandler() noexcept = 0;
  };
} // namespace TechnicalServices::Persistence
