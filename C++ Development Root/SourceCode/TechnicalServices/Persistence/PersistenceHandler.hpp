#pragma once

#include <map>
#include <stdexcept>    // domain_error, runtime_error
#include <string>
#include <vector>




namespace TechnicalServices::Persistence
{

    // User objects
  struct UserCredentials
  {
    int                       userID;
    std::string               userName;
    std::string               passPhrase;
    std::vector<std::string>  roles;
    int                       status;
  };

  struct UserEvents 
  {
    int                       userID;
    std::vector<std::string>  freeTime;
    std::vector<std::string>  events;
  };

  // Client objects
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

  // Product objects 
  struct Product
  {
      int         id;
      std::string Name;
      int         Price;
      int     ProductCommany;

  };

  struct ProductCompany {
      int Id;
      std::string Name;
      int Rate;
  };

  // Commission objects
  struct Commission {
      int        ID;
      int        Revenue = 0;
      int        Commission_Rate = 0;
      bool       Status = false;
  };

  struct Sale
  {
      int         id;
      int        Commission_ID;
      int         UserId;
      int         ClientId;
      std::string DateOfSale;
      std::vector<int> ProductsId;


  };

  // Event object
  struct Event 
  {
      int               eventID;
      std::string       eventName;
      std::vector<int>  eventUsers;
      std::string       eventTime;
      std::string       eventLocation;
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
      virtual std::vector<std::string> findOffices()                                     = 0;   // Returns list of all office rooms
      virtual UserCredentials          findCredentialsByName( const std::string & name ) = 0;   // Returns credentials for specified user, throws NoSuchUser if user not found
      
      // client operations
      
     
       virtual std::vector<Client> ShowAllClients() = 0;
       virtual std::vector<Clientprofile> ShowAllClientsProfile() = 0;
       virtual std::vector<Product> CRMInventory() =0 ;

       virtual std::vector<ProductCompany> CRMCompanypartnerships() = 0;
       virtual std::vector<Sale> PurchasedHistory() = 0;
       virtual std::vector<Commission> CHistory() = 0;

       // user
       virtual std::vector<UserCredentials> ShowAllUsers() = 0;
       virtual std::vector<UserEvents> ShowAllUserEvents() = 0;
       virtual std::vector<Event> ShowAllEvents() = 0;

      // Adaptation Data read only access.  Adaptation data is a Key/Value pair
      // Throws NoSuchProperty
      virtual const std::string & operator[]( const std::string & key ) const = 0;

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~PersistenceHandler() noexcept = 0;
  };
} // namespace TechnicalServices::Persistence
