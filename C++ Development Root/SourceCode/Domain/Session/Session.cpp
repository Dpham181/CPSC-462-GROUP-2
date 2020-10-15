#include "Domain/Session/Session.hpp"
#include "Domain/Client/Client.hpp"

#include <string>
#include <any>
#include <iomanip>     // setw()

#include <vector>

namespace  // anonymous (private) working area
{
  auto & persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();

  // 1)  First define all system events (commands, actions, requests, etc.)
  #define STUB(functionName)  std::any functionName( Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now
   
  //STUB( bugPeople    )
  //STUB( collectFines )
  //STUB( help         )
  //STUB( openArchives )
  //STUB( payFines     )
  //STUB( resetAccount )
  //STUB( returnBook   )
  //STUB( shutdown     )
 
    // Assistant actions
  STUB(ShowAllClients )
  STUB( modifyClient)
  STUB( askHelp )
  STUB( scheduleEvent )
  STUB( attachClientDocument )
  STUB( inviteClient )

 
    // Salesperson actions
  STUB( makeSale )

    // Sales Manager actions
  STUB( manageSubscription )

    // IT Admin actions
  STUB( addNewAccount )
  STUB( backupDB )
  
    // Security Officer actions
  STUB( blockAccount )
  


  std::any checkoutBook( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    // TO-DO  Verify there is such a book and the mark the book as being checked out by user
    std::string results = "Title \"" + args[0] + "\" checkout by \"" + session._credentials.userName + '"';
    session._logger << "checkoutBook:  " + results;
    return results;
  }
  std::any addNewClient(Domain::Session::SessionBase& session, const std::vector<std::string>& args) {
      std::string results = "";
      return "test";

  }
  

  
}    // anonymous (private) working area



namespace Domain::Client

{
    void line()
    {
        for (int i = 1; i < 41; i++)
            std::cout << "--";
        std::cout << "\n";

    }

    ClientDomain::ClientDomain(const std::string& description, const Client& Client) : _Client(Client), _name(description)
    {
        _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
    }
    // get updating the static data of Client and Client Profile
    std::vector<Client> ClientDomain::ClientsDB(const std::vector<Client>& ClientsDB) {
        _UpdatedDB = ClientsDB;

        return _UpdatedDB;
    }
    std::vector<Clientprofile> ClientDomain::ClientsPDB(const std::vector<Clientprofile>& ClientprofileDB) {
        _UpdatedprofileDB = ClientprofileDB;

        return _UpdatedprofileDB;
    }

    // ADDING NEW CLIENT TO THE MEMORY DATABASE 
    std::vector<Client> ClientDomain::addClient(const Client& Client) {
        _UpdatedDB.push_back(Client); // add new client to list of static client 
        // generating the result in updating table 
        line();
        std::cout << std::setw(49) << "List Of Clients Updated Table\n";
        line();
        std::cout << std::setw(15) << "Client ID  " << std::setw(15) << " Creator \n";
        line();

        for (const auto& c : _UpdatedDB)
            std::cout << std::setw(10) << std::to_string(c.clientid) << std::setw(15) << c.creator << std::endl;
        line();
        return  _UpdatedDB;
    }
    // Updating the Client profile
    Clientprofile ClientDomain::UpdateClientProfile(const std::string ClientName, const int ClientID, const std::string DOB, const int Income, int Phone) {
        Clientprofile newcp = { "", 0, "", 0, 0 };
        newcp.client_id = ClientID;
        newcp.client_name = ClientName;

        std::cout << "Client Name: " << ClientName << std::endl;
        std::cout << "Client ID: " << ClientID << std::endl;
        std::cout << "Client's Date of Birth: " << DOB << std::endl;
        std::cout << "Client's Income: $" << Income << std::endl;
        std::cout << "Client's Phone: " << Phone << std::endl;
        return newcp;
    }


    ClientSession::ClientSession(const Client& Client) : ClientDomain("Client ID Genarated", Client)
    {
        _logger << " Client ID: \"" + std::to_string(Client.clientid) ;

        
    }


}

namespace Domain::Session
{
  SessionBase::SessionBase( const std::string & description, const UserCredentials & credentials ) : _credentials( credentials ), _name( description )
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
  }


 

  SessionBase::~SessionBase() noexcept
  {
    _logger << "Session \"" + _name + "\" shutdown successfully";
  }




  std::vector<std::string> SessionBase::getCommands()
  {
    std::vector<std::string> availableCommands;
    availableCommands.reserve( _commandDispatch.size() );

    for( const auto & [command, function] : _commandDispatch ) availableCommands.emplace_back( command );

    return availableCommands;
  }




  std::any SessionBase::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    std::string parameters;
    for( const auto & arg : args )  parameters += '"' + arg + "\"  ";
    _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commandDispatch.find( command );
    if( it == _commandDispatch.end() )
    {
      std::string message = __func__;
      message += " attempt to execute \"" + command + "\" failed, no such command";

      _logger << message;
      throw BadCommand( message );
    }

    auto results = it->second( *this, args);

    if( results.has_value() )
    {
      // The type of result depends on function called.  Let's assume strings for now ...
      _logger << "Responding with: \"" + std::any_cast<const std::string &>( results ) + '"';
    }

    return results;
  }



  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
  ITAdministratorSession::ITAdministratorSession( const UserCredentials & credentials ) : SessionBase( "IT Admin", credentials )
  {
    _logger << "Login Successful for \"" + credentials.userName + "\" as role \"IT Admin\".";

    _commandDispatch = { {"Add New Account",   addNewAccount },
                         {"Back-up Database",   backupDB }//,
                         //{"Shutdown System", shutdown    } 
    };
  }




  AssistantSession::AssistantSession( const UserCredentials & credentials ) : SessionBase( "Assistant", credentials )
  {
    _logger << "Login Successful for \"" + credentials.userName + "\" as role \"Assistant\".";

    _commandDispatch = {
                         { "Show All Clients", ShowAllClients },
                        {"Add New Client", addNewClient},
                         {"Modify Client",          modifyClient        },
                         {"Ask IT for Help",     askHelp    },
                         {"Schedule Event",   scheduleEvent  },
                         { "Attach Client Document", attachClientDocument },
                         { "Invite Client", inviteClient }//,
    };
  }




  SalespersonSession::SalespersonSession( const UserCredentials & credentials ) : SessionBase( "Salesperson", credentials )
  {
    _logger << "Login Successful for \"" + credentials.userName + "\" as role \"Salesperson\".";

    _commandDispatch = { {"Make Sale", makeSale}//,
                         //{"Collect Fines", collectFines},
                         //{"Help",          help        },
                         //{"Open Archives", openArchives} 
    };
  }




  SalesManagerSession::SalesManagerSession( const UserCredentials & credentials ) : SessionBase( "Sales Manager", credentials )
  {
    _logger << "Login Successful for \"" + credentials.userName + "\" as role \"Sales Manager\".";

    _commandDispatch = { {"Manage Subscription", manageSubscription}//,
                         //{"Help",       help} 
    };
  }
}    // namespace Domain::Session
