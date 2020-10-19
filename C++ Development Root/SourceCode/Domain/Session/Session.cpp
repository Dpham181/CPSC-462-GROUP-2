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
  // Client management control with UI  
  #define STUBC(functionName)  std::any functionName( Domain::Client::ClientDomain & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now





 STUB(ClientManagement)
 STUBC(View)
 
 std::any Add(Domain::Client::ClientDomain& session, const std::vector<std::string>& agrs) {

     auto result = session.addClient({ agrs[0],std::atoi(agrs[1].c_str()),agrs[2],std::atoi(agrs[3].c_str()) });

     return  result;
 }
  std::any Update(Domain::Client::ClientDomain& session, const std::vector<std::string>& agrs) {
      auto newClientProfilebyId = session.UpdateClientProfile(std::atoi(agrs[0].c_str()), agrs[1], std::atoi(agrs[2].c_str()));
     
      return  newClientProfilebyId;
  }
  std::any ViewClientProfile(Domain::Client::ClientDomain& session, const std::vector<std::string>& agrs) {
      auto ClientProfilebyId = session.SearchClientId(std::atoi(agrs[0].c_str()));

      return  ClientProfilebyId;
  }
 STUB(ProductManagement)

   


  
  
}    // anonymous (private) working area



namespace Domain::Client

{
    auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
    
    void line()
    {
        for (int i = 1; i < 41; i++)
            std::cout << "--";
        std::cout << "\n";

    }

    ClientDomain::ClientDomain(const std::string& description, const UserCredentials& user) :  _name(description),_Creator(user)
    {
        _logger << "Acess to  \"" + _name + "\" being used by " + _Creator.userName;
    }


    std::vector<std::string> ClientDomain::getCommandsClient()
    {
        std::vector<std::string> availableCommands;
        availableCommands.reserve(_commandDispatch.size());

        for (const auto& [command, function] : _commandDispatch) availableCommands.emplace_back(command);

        return availableCommands;
    }

    std::any ClientDomain::executeCommandClient(const std::string& command, const std::vector<std::string>& args)
    {
        std::string parameters;
        for (const auto& arg : args)  parameters += '"' + arg + "\"  ";
        _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

        auto it = _commandDispatch.find(command);
        
        auto results = it->second(*this, args);

        return results;
    }

   
    // get updating the static data of Client and Client Profile
    std::vector<Client> ClientDomain::ClientsDB(const std::vector<Client>& ClientsDB) {
        _UpdatedDB = ClientsDB;
        // generating the result in updating table 
       
        return _UpdatedDB;
    }
    std::vector<Clientprofile> ClientDomain::ClientsPDB(const std::vector<Clientprofile>& ClientprofileDB) {
        _UpdatedprofileDB = ClientprofileDB;

        return _UpdatedprofileDB;
    }
    void ClientDomain::ViewClients(const std::vector<Client>& ClientsDB) {
        line();
        std::cout << std::setw(49) << "list of clients\n";
        line();
        std::cout << std::setw(15) << "Id" << std::setw(15) << "Name" << std::setw(15) << "Phone" << std::setw(20) << " Created By \n";
        line();

        for (const auto& c : ClientsDB)
            std::cout << std::setw(15) << std::to_string(c.clientid) << std::setw(15) << c.client_name << std::setw(15) << std::to_string(c.phone) << std::setw(15) << c.creator << std::endl;
        line();
    }
    // ADDING NEW CLIENT TO THE MEMORY DATABASE 
    std::vector<Client> ClientDomain::addClient(const Client& Client) {
        _UpdatedDB.push_back(Client); // add new client to list of static client 
        Clientprofile newcp = { Client.clientid,  "", 0 }; // also create an temporary profile 
        _UpdatedprofileDB.push_back(newcp);
        return  _UpdatedDB;
    }
    // Updating the Client profile
       /* int         client_id;
        std::string dob;
        int         income;*/
    Clientprofile   ClientDomain::SearchClientId(const int ClientId) {

        for (const auto& ClientProfile : _UpdatedprofileDB) {
            if (ClientProfile.client_id == ClientId) {
                _Clientprofile = ClientProfile;
             
            }

        }
        return  _Clientprofile;
    }

    std::vector<Clientprofile> ClientDomain::UpdateClientProfile( const int ClientID, const std::string DOB, const int Income) {
        
        _Clientprofile = { ClientID ,"",0 };
        int ReplaceIndex = ClientID - 1;
        if (DOB != "")  _Clientprofile.dob = DOB; 
        if (Income > 0) _Clientprofile.income = Income; 
         _UpdatedprofileDB.at(ReplaceIndex) = _Clientprofile;


        return   _UpdatedprofileDB;
    }
    
    ClientManagement::ClientManagement(const UserCredentials& user) : ClientDomain ("Client Management", user)
    {
       
        _commandDispatch = {

                         { "Add Client", Add },
                         {"View All Clients", View},
                         { "Update Client Profile", Update },
                         { "View Client Profile", ViewClientProfile }//,

                                };
    };


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

    //_commandDispatch = { {"add new account",   addnewaccount },
    //                     {"back-up database",   backupdb }//,
    //                     //{"shutdown system", shutdown    } 
    //};
  }




  AssistantSession::AssistantSession( const UserCredentials & credentials ) : SessionBase( "Assistant", credentials )
  {
    _logger << "Login Successful for \"" + credentials.userName + "\" as role \"Assistant\".";

    //_commandDispatch = {
    //                     { "Show All Clients", ShowAllClients },
    //                    {"Add New Client", addNewClient},
    //                     {"Modify Client",          modifyClient        },
    //                     {"Ask IT for Help",     askHelp    },
    //                     {"Schedule Event",   scheduleEvent  },
    //                     { "Attach Client Document", attachClientDocument },
    //                     { "Invite Client", inviteClient }//,
    //};
  }




  SalespersonSession::SalespersonSession( const UserCredentials & credentials ) : SessionBase( "Salesperson", credentials )
  {
    _logger << "Login Successful for \"" + credentials.userName + "\" as role \"Salesperson\".";

    _commandDispatch = { 
        
        {"Client Management", ClientManagement},
        {"Product Management", ProductManagement}
                         
    };
  }




  SalesManagerSession::SalesManagerSession( const UserCredentials & credentials ) : SessionBase( "Sales Manager", credentials )
  {
    _logger << "Login Successful for \"" + credentials.userName + "\" as role \"Sales Manager\".";

   // _commandDispatch = { {"Manage Subscription", manageSubscription}//,
                         //{"Help",       help} 
    };
  }
}    // namespace Domain::Session
