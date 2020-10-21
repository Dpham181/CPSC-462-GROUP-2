#include "Domain/Session/Session.hpp"
#include "Domain/Client/Client.hpp"
#include "Domain/User/User.hpp"

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
   
    #define STUBC(functionName)  std::any functionName( Domain::Client::ClientDomain & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now

 
    // Assistant actions
  STUB( ShowAllClients )
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
  STUB( UserManagement )
  STUB( BackupDB )
  STUB( Shutdown )


  std::any AddUser(Domain::User::UserDomain& session, const std::vector<std::string>& agrs)
  {

      auto result = session.addUser({ std::atoi(agrs[0].c_str()), agrs[1], agrs[2] });

      return  result;
  }
  std::any UpdateUserProfile(Domain::User::UserDomain& session, const std::vector<std::string>& agrs)
  {
      auto result = session.searchUserId(std::atoi(agrs[0].c_str()));


      return  result;
  }
  /* std::any ViewUsers(Domain::User::UserDomain& session, const std::vector<std::string>& agrs)
   {



       return  result;
   }*/
  std::any ViewUsers(Domain::User::UserDomain& session, const std::vector<std::string>& agrs) {

      return  "true";
  }
  std::any DeleteUser(Domain::User::UserDomain& session, const std::vector<std::string>& agrs) {

      return  "true";
  }
  //not for IT admin
  std::any ViewUserProfiles(Domain::User::UserDomain& session, const std::vector<std::string>& agrs) {

      return  "true";
  }


  // Security Officer actions
  STUB(blockAccount)

  
 
  


  std::any Add(Domain::Client::ClientDomain& session, const std::vector<std::string>& agrs) {
     
      return  "true";
  }
  std::any View(Domain::Client::ClientDomain& session, const std::vector<std::string>& agrs) {

      return  "true";
  }
  std::any Update(Domain::Client::ClientDomain& session, const std::vector<std::string>& agrs) {

      return  "true";
  }
  std::any Link(Domain::Client::ClientDomain& session, const std::vector<std::string>& agrs) {

      return  "true";
  }
  std::any ClientManagement(Domain::Session::SessionBase& session, const std::vector<std::string>& args) {
      return "True";
  }
  std::any ProductManagement(Domain::Session::SessionBase& session, const std::vector<std::string>& args) {
      return "true";
  }
  
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
        _logger << "Acess to  \"" + _name + "\" being used " + _Creator.userName;
    }


    std::vector<std::string> ClientDomain::getCommands()
    {
        std::vector<std::string> availableCommands;
        availableCommands.reserve(_commandDispatch.size());

        for (const auto& [command, function] : _commandDispatch) availableCommands.emplace_back(command);

        return availableCommands;
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
        std::cout << std::setw(15) << "client id  " << std::setw(15) << " creator \n";
        line();

        for (const auto& c : ClientsDB)
            std::cout << std::setw(10) << std::to_string(c.clientid) << std::setw(15) << c.creator << std::endl;
        line();
    }
    // ADDING NEW CLIENT TO THE MEMORY DATABASE 
    std::vector<Client> ClientDomain::addClient(const Client& Client) {
        _UpdatedDB.push_back(Client); // add new client to list of static client 
        // generating the result in updating table 
        line();
        std::cout << std::setw(49) << "list of clients updated table\n";
        line();
        std::cout << std::setw(15) << "client id  " << std::setw(15) << " creator \n";
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

       /* std::cout << "Client Name: " << ClientName << std::endl;
        std::cout << "Client ID: " << ClientID << std::endl;
        std::cout << "Client's Date of Birth: " << DOB << std::endl;
        std::cout << "Client's Income: $" << Income << std::endl;
        std::cout << "Client's Phone: " << Phone << std::endl;*/
        return newcp;
    }


    ClientManagement::ClientManagement(const UserCredentials& user) : ClientDomain ("Client Management", user)
    {
       
        _commandDispatch = {

                         { "Add Client", Add },
                         {"View All Clients", View},
                         { "Update Client Profile", Update },
                         { "Link Product", Link }//,

                                };
    };


}


namespace Domain::User

{
    auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();

    void line()
    {
        for (int i = 1; i < 41; i++)
            std::cout << "--";
        std::cout << "\n";

    }

    UserDomain::UserDomain(const std::string& description, const UserCredentials& user) : _name(description), _Creator(user)
    {
        _logger << "Acess to  \"" + _name + "\" being used by " + _Creator.userName;
    }


    std::vector<std::string> UserDomain::getCommandsUser()
    {
        std::vector<std::string> availableCommands;
        availableCommands.reserve(_commandDispatch.size());

        for (const auto& [command, function] : _commandDispatch) availableCommands.emplace_back(command);

        return availableCommands;
    }

    std::any UserDomain::executeCommandUser(const std::string& command, const std::vector<std::string>& args)
    {
        std::string parameters;
        for (const auto& arg : args)  parameters += '"' + arg + "\"  ";
        _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

        auto it = _commandDispatch.find(command);

        auto results = it->second(*this, args);

        return results;
    }


    // get updating the static data of User and UserCredentials
    std::vector<User> UserDomain::UsersDB(const std::vector<User>& UsersDB) 
    {
        _UpdatedUserDB = UsersDB;
        // generating the result in updating table 

        return _UpdatedUserDB;
    }

    std::vector<UserCredentials> UserDomain::UsersPDB(const std::vector<UserCredentials>& UserprofileDB) 
    {
        _UpdatedUserProfileDB = UserprofileDB;

        return _UpdatedUserProfileDB;
    }

    void UserDomain::viewUsers(const std::vector<User>& UsersDB) 
    {
        line();
        std::cout << std::setw(49) << "list of users\n";
        line();
        std::cout << std::setw(15) << "Id" << std::setw(20) << "Name" << std::setw(20) << "Role" << "\n";
        line();

        for (const auto& c : UsersDB)
            std::cout << std::setw(15) << std::to_string(c.userID) << std::setw(20) << c.userName << std::setw(20) << c.userRole << std::endl;
        line();
    }

    void UserDomain::viewUserProfiles(const std::vector<UserCredentials>& UsersPDB)
    {
        
        line();
        std::cout << std::setw(49) << "User profiles\n";
        line();
        std::cout << std::setw(15) << "User Name" << std::setw(20) << "Pass Phrase" << std::setw(20) << "Role" << std::setw(20) << "Status" << "\n";
        line();

        for (const auto& c : UsersPDB)
        {
            std::string userStatus;
            if (c.status == 1) userStatus = "Access Allowed";
            else userStatus = "Access Denied";
            std::cout << std::setw(15) << c.userName << std::setw(20) << c.passPhrase << std::setw(20) << c.roles[0] << std::setw(20) << userStatus<< std::endl;
        }
    
        line();
    }

    // ADDING NEW USER TO THE MEMORY DATABASE 
    std::vector<User>  UserDomain::addUser(const User& user) 
    //std::pair<std::vector<User>, std::vector<UserCredentials>>  UserDomain::addUser(const User& user)
    {
        _UpdatedUserDB.push_back(user); // add new User to list of static User 
        UserCredentials newUserProfile = { user.userName,  "123456", std::vector<std::string> {user.userRole}, 1 };    // also create an temporary user profile 
        _UpdatedUserProfileDB.push_back(newUserProfile);

        //std::pair<std::vector<User>, std::vector<UserCredentials>> UerDBPair(_UpdatedUserDB, _UpdatedUserProfileDB);
        //return  UerDBPair;

        return _UpdatedUserDB;
    }

    // Updating the User profile
       /* int         client_id;
        std::string dob;
        int         income;*/
    UserCredentials   UserDomain::searchUserId(const int UserId) {

        for (const auto& StoredUser : _UpdatedUserDB)
        {
            if (StoredUser.userID == UserId) 
            {
                _User = StoredUser;
            }
        }

        for (const auto& UserProfile : _UpdatedUserProfileDB) {
            if (UserProfile.userName == _User.userName) {
                _Userfile = UserProfile;
                return  _Userfile;
            }

        }
    }

    UserCredentials UserDomain::updateUserProfile(const std::string UserName, std::string PassPhrase, std::string Role, const int Status)
    {
        if (UserName != "") {
            _Userfile.userName = UserName;

        }
        else if (PassPhrase != "") {
            _Userfile.passPhrase = PassPhrase;
        }
        else if (Role != "") {
            _Userfile.roles[0] = Role;
        }
        else if (Status != -1) {
            _Userfile.status = Status;

        }



        return _Userfile;
    }

    UserManagement::UserManagement(const UserCredentials& user) : UserDomain("User Management", user)
    {

        _commandDispatch = {

                         { "Add User", AddUser },
                         { "View All Users", ViewUsers },
                         { "View All User Profiles", ViewUserProfiles },
                         { "Update User Profile", UpdateUserProfile },
                         { "Delete User", DeleteUser }

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

    _commandDispatch = { {"User Management",    UserManagement },
                         {"Back-up Database",   BackupDB },
                         {"Shutdown System",    Shutdown } 
    };
  }




  AssistantSession::AssistantSession( const UserCredentials & credentials ) : SessionBase( "Assistant", credentials )
  {
    _logger << "Login Successful for \"" + credentials.userName + "\" as role \"Assistant\".";

    //_commandDispatch = {
    //                     { "Show All Clients", ShowAllClients },
    //                     {"Add New Client", addNewClient},
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

    _commandDispatch = { {"Manage Subscription", manageSubscription}//,
                         //{"Help",       help} 
    };
  }
}    // namespace Domain::Session
