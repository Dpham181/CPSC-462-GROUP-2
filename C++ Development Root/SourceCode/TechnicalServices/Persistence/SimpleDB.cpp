﻿#include "TechnicalServices/Persistence/SimpleDB.hpp"

#include <fstream>    // streamsize
#include <iomanip>    // quoted()
#include <limits>     // numeric_limits
#include <memory>     // make_unique()
#include <string>
#include <vector>

#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"





namespace
{
  // User defined manipulator with arguments that allows std::istream::ignore to be called "in-line" (chained)
  // Usage example:
  //    stream >> first >> ignore(',') second >> ignore('\n') ;
  struct ignore
  {
    char _seperator;
    ignore( char delimiter = '\n' ) : _seperator( delimiter ) {}
  };

  std::istream & operator>>( std::istream & s, ignore && delimiter )
  {
    s.ignore( std::numeric_limits<std::streamsize>::max(), delimiter._seperator );
    return s;
  }
}    // namespace




namespace TechnicalServices::Persistence
{
  // Design decision/Programming note:
  //  - The persistence database contains adaptation data, and one of the adaptable items is which Logger component to use
  //  - The factory function TechnicalServices::Logging::create(std::ostream &) depends of the persistence database to obtain
  //    through adaptation data which kind of Logging component to create
  //  - However, the Persistence database implementations, like this one, should (must?) be able to log messages
  //  - Therefore, to maintain the design decision to allow Logging to depend on Persistence, but not Persistence to depend on
  //    Logging, we mustn't create this logger through the LoggingHandler interface, but rather select and create a specific Logger
  SimpleDB::SimpleDB() : _loggerPtr( std::make_unique<TechnicalServices::Logging::SimpleLogger>() )
  {
    _logger << "Simple DB being used and has been successfully initialized";


    // Let's look for an adaptation data file, and if found load the contents.  Otherwise create some default values.
    std::ifstream adaptationDataFile( "Library_System_AdaptableData.dat", std::ios::binary );

    if( adaptationDataFile.is_open() )
    {
      // Expected format:  key = value
      // Notes:
      //   1) if key or value contain whitespace, they must be enclosed in double quotes
      //   2) if the same Key appears more than once, last one wins
      //   3) everything after the value is ignored, allowing that space to be used as comments
      //   4) A Key of "//" is ignored, allowing the file to contain comment lines of the form // = ...
      std::string key, value;
      while( adaptationDataFile >> std::quoted( key ) >> ignore( '=' ) >> std::quoted( value ) >> ignore( '\n' ) )   _adaptablePairs[key] = value;
      _adaptablePairs.erase( "//" );
    }

    else
    {
      _adaptablePairs = { /* KEY */               /* Value*/
                          {"Component.Logger",    "Simple Logger"},
                          {"Component.UI",        "Simple UI"}
//                        {"Component.UI",        "Contracted UI"}
                        };
    }
  }




  SimpleDB::~SimpleDB() noexcept
  {
    _logger << "Simple DB shutdown successfully";
  }


  std::vector<std::string> SimpleDB::findRoles()
  {
    return { "Assistant", "Salesperson", "Sales Manager", "IT Admin", "Security Officer" };
  }


   std::vector<Client> SimpleDB::ShowAllClients()
  {
      
     return { { "A", 1,"D",714000000 }, { "B", 2, "C",714000000 } };
  }
   
   std::vector<Clientprofile> SimpleDB::ShowAllClientsProfile ()
   {

       return { {1,"10/18/2000",20000},
                {2,"10/18/2001",20000},
       
       
       };
   }

   std::vector<Product> SimpleDB::CRMInventory()
   {

       return { 
                {1,"House 1",400000 ,1},
                {2,"House 2",500000, 2},


       };
   }

   // Company mock DB
   std::vector<ProductCompany> SimpleDB::CRMCompanypartnerships()
   {

       return {
                {1,"lUX Real Estate",80},
                {2,"JH Real Estate",90},


       };
   }
   // Sale  mock DB

   std::vector<Sale> SimpleDB::PurchasedHistory() {
       return {
              {1,1,1,1,"10/22/2020", {1,2}},
              {2,2,2,2,"10/23/2020", {1,2}},
       };
   }

   // Commission Mock Db
   std::vector<Commission> SimpleDB::CHistory() {
       return {
            {1, 20000, 80, false },
            {2, 30000, 90, true },
       };
   }

   std::vector<UserCredentials> SimpleDB::ShowAllUsers()
   {
       return
       {
           //UserID     Username    Pass phrase   Authorized roles       Status
            { 1,        "Tom",      "CPSC",       { "IT Admin" },          1 },
            { 2,        "Amanda",   "",           { "Salesperson" },       1 },
            { 3,        "Sam",      "Assist",     { "Assistant" },         1 },
            { 4,        "Ann",      "Manage",     { "Sales Manager" },     1 },
            { 5,        "Cain",     "Security",   { "Security Officer"},   1 }
       };
   }

   std::vector<UserEvents> SimpleDB::ShowAllUserEvents()
   {
       return
       {
           //UserID     Free time               Events
           { 1,         { "Tu AM" },            { "Office meeting, Fr AM, Office 2" } },
           { 2,         { "Tu AM", "We PM" },   { "Office meeting, Fr AM, Office 2" } },
           { 3,         { "Tu AM" },            { "Office meeting, Fr AM, Office 2" } },
           { 4,         { "Tu AM", "We PM" },   { "Office meeting, Fr AM, Office 2" } }
       };
   }

   // static subscription refs Pricing Summary(Business&Vision)
   std::vector<Subcripstion> SimpleDB::ShowAllSubcripstion() {
       return {

           { 1,    "Very Small", "Free", "≤5" },
           { 2,     "Small" , "10" , "≤10" },
           { 3,      "Medium"  ,"20","≤30" },
           { 4,       "Large" , "35","≤80"},
           { 5,       "Super" ,"50","≤80"}
       };
   }
   std::vector<PaymentOption> SimpleDB::ShowAllPaymentOption() {
       return {
           {1, "Debit"},
           {2, "Credit"},
           {3, "GateWay"}
       };

   }
  
   SubscriptionStatus SimpleDB::StacticSubscriptionSatus()
   {
       return
       { 1, 4, "12/20/2020","Completed", "ana@gmail.com" };
       
   }

  UserCredentials SimpleDB::findCredentialsByName( const std::string & name )
  {
    std::vector<UserCredentials> storedUsers = ShowAllUsers();

    for( const auto & user : storedUsers ) if( user.userName == name ) return user;

    // Name not found, log the error and throw something
    std::string message = __func__;
    message += " attempt to find user \"" + name + "\" failed";

    _logger << message;
    throw PersistenceHandler::NoSuchUser( message );
  }

  std::vector<std::string> SimpleDB::findOffices()
  {
      return { "Office 1", "Office 2", "Office 3" };
  }

  std::vector<Event> SimpleDB::ShowAllEvents()
  {
      return
      {
          //EventID    Event name          Event Paticipants    Event time     Event location
          { 1,         "Office meeting",   {1, 2, 3, 4},        "Fr AM",       "Office 2" }
      };
  }
 
  // TDUFF
  // Return the user's role
  //std::string UsersRole(UserCredentials user) {
  //  if 
  //  return user.roles[0];
  //}


  const std::string & SimpleDB::operator[]( const std::string & key ) const
  {
    auto pair = _adaptablePairs.find( key );
    if( pair != _adaptablePairs.cend() ) return pair->second;

    // Key not found - error
    std::string message = __func__;
    message += " attempt to access adaptation data with Key = \"" + key + "\" failed, no such Key";

    _logger << message;
    throw NoSuchProperty( message );
  }
} // namespace TechnicalServices::Persistence


