#include "Domain/Session/Session.hpp"
#include "Domain/Client/Client.hpp"
#include "Domain/Product/Product.hpp"
#include "Domain/User/User.hpp"
#include "Domain/Event/Event.hpp"
#include <string>
#include <any>
#include <iomanip>     // setw()
#include <locale>       // touuper(), locale()

#include <vector>

namespace  // anonymous (private) working area
{
  auto & persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();

  // 1)  First define all system events (commands, actions, requests, etc.)
  #define STUB(functionName)  std::any functionName( Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now
  
 
  
// Client management  
 //---------------------------------------------------------------------------------
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
// product management 
 //---------------------------------------------------------------------------------
   //{ "Add New Product", AddProduct },
       //{"View Inventory", ViewProducts},
       //{ "Modify Product", ModifyProduct },
       //{ "Del product", Delproduct }//,
 #define STUBC(functionName)  std::any functionName( Domain::Product::ProductDomain & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  
 STUB(ProductManagement)
 
 std::any AddProduct(Domain::Product::ProductDomain& productcontrol, const std::vector<std::string>& agrs) 
 {
     int increment = productcontrol._ProductDb.size() + 1;
     auto newproduct = productcontrol.add(increment, agrs[0], std::atoi(agrs[1].c_str()));
     std::cout << std::setw(15) << std::to_string(newproduct.id) << std::setw(15) << newproduct.Name << std::setw(15) << std::to_string(newproduct.Price) << std::endl;

     auto inventoryUpdated = productcontrol.save(newproduct);

     return inventoryUpdated;
 
 }
     
 std::any ViewProducts(Domain::Product::ProductDomain& productcontrol, const std::vector<std::string>& agrs)
 {
     productcontrol.view();

     return {};

 }
 std::any ModifyProduct(Domain::Product::ProductDomain& productcontrol, const std::vector<std::string>& agrs)
 {
     //Todo
     return {};

 }
 std::any Delproduct(Domain::Product::ProductDomain& productcontrol, const std::vector<std::string>& agrs)
 {  
     //Todo

     return {};

 }



  
  
}    // anonymous (private) working area

// User management
STUB(UserManagement)

std::any AddUser(Domain::User::UserDomain& session, const std::vector<std::string>& agrs)
{

    auto result = session.addUser( std::atoi(agrs[0].c_str()), agrs[1], agrs[2] );

    return  result;
}

 std::any UpdateUser(Domain::User::UserDomain& session, const std::vector<std::string>& agrs)
 {
     auto result = session.updateUser({ std::atoi(agrs[0].c_str()), agrs[1], agrs[2], {agrs[3]}, std::atoi(agrs[4].c_str()) });

     return  result;
 }

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

// Office events management
STUB(EventManagement)

std::any AddEvent(Domain::Event::EventDomain& session, const std::vector<std::string>& agrs)
{
    std::string s1 = agrs[2];
    std::vector<int> res;
    while (!s1.empty())
    {
        if (s1.find(" ") == std::string::npos) 
        {
            res.push_back(stoi(s1));
            s1.clear();
            break;
        }
        std::string s_temp = s1.substr(0, s1.find(" "));
        res.push_back(stoi(s_temp));
        s1.erase(0, s1.find(" ") + 1);
    }
    auto result = session.addEvent({ std::atoi(agrs[0].c_str()), agrs[1], res, agrs[3], agrs[4] });

    return  result;
}

std::any UpdateEvent(Domain::Event::EventDomain& session, const std::vector<std::string>& agrs)
{
    std::string s1 = agrs[2];
    std::vector<int> res;
    while (!s1.empty())
    {
        if (s1.find(" ") == std::string::npos)
        {
            res.push_back(stoi(s1));
            s1.clear();
            break;
        }
        std::string s_temp = s1.substr(0, s1.find(" "));
        res.push_back(stoi(s_temp));
        s1.erase(0, s1.find(" ") + 1);
    }
    auto result = session.updateEvent({ std::atoi(agrs[0].c_str()), agrs[1], res, agrs[3], agrs[4] });

    return  result;
}

std::any ViewEvents(Domain::Event::EventDomain& session, const std::vector<std::string>& agrs)
{
    return  "true";
}

std::any DeleteEvent(Domain::Event::EventDomain& session, const std::vector<std::string>& agrs)
{
    return "true";
}

// IT Admin actions
STUB(BackupDB)
STUB(Shutdown)

// Assistant actions
STUB(AskHelp)

// Client domain implementation 
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
                         { "View All Clients", View},
                         { "Update Client Profile", Update },
                         { "View Client Profile", ViewClientProfile }//,

                                };
    };


}
// Product domain implementation 
namespace Domain::Product

{
    auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
    
    void line()
    {
        for (int i = 1; i < 41; i++)
            std::cout << "--";
        std::cout << "\n";

    }
    
   
    ProductDomain::ProductDomain(const std::string& description, const UserCredentials& user) : _name(description), _Usedby(user)
    {
        _logger << "Acess to  \"" + _name + "\" being used by " + _Usedby.userName;
        _ProductDb = persistentData.CRMInventory();

    }


    std::vector<std::string> ProductDomain::getCommandsProduct()
    {
        std::vector<std::string> availableCommands;
        availableCommands.reserve(_commandDispatch.size());

        for (const auto& [command, function] : _commandDispatch) availableCommands.emplace_back(command);

        return availableCommands;
    }

    std::any ProductDomain::executeCommandProduct(const std::string& command, const std::vector<std::string>& args)
    {
        std::string parameters;
        for (const auto& arg : args)  parameters += '"' + arg + "\"  ";
        _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

        auto it = _commandDispatch.find(command);

        auto results = it->second(*this, args);

        return results;
    }


    void ProductDomain::view() {

        line();
        std::cout << std::setw(49) << "Inventory of CRM\n";
        line();
        std::cout << std::setw(15) << "Id" << std::setw(15) << "Name" << std::setw(15) << "Price\n";
        line();

        for (const auto& p : _ProductDb)
           std::cout << std::setw(15) << std::to_string(p.id) << std::setw(15) << p.Name << std::setw(15) << std::to_string(p.Price)<< std::endl;
        line();
    }
   
    Product   ProductDomain::add(const int ProductId, const std::string ProductName, const int Price) {
        Product newProduct = { 0,"",0 };
        if (ProductId > 0) newProduct.id = ProductId;
        if (ProductName != "") newProduct.Name = ProductName;
        if (Price > 0) newProduct.Price = Price;
        return   newProduct;
    }
    std::vector<Product> ProductDomain::save(const Product& Newproduct) {
        char reponse;
        do
        {
            std::cout <<   "Do you want to save this product? (Y/N/Q)";
            std::cin >> reponse;
            reponse = std::toupper(reponse, std::locale());
        } while (reponse != 'Y' && reponse != 'Q');

        if (reponse == 'Y') _ProductDb.push_back(Newproduct);

        return _ProductDb;
    }
    std::vector<Product>   ProductDomain::del(const int ProductId) {
        //Todo
        return {};
    }
    std::vector<Product>   ProductDomain::modify(const Product CurrentProduct, const std::string ProductName, const int Price) {
        //Todo
        return {};
    }
    ProductManagement::ProductManagement(const UserCredentials& user) : ProductDomain("Product Management", user)
    {

        _commandDispatch = {

                         { "Add New Product", AddProduct },
                         {"View Inventory", ViewProducts},
                         { "Modify Product", ModifyProduct },
                         { "Del product", Delproduct }//,

        };
    };


}

// User domain implemention
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
    std::vector<UserCredentials> UserDomain::UsersDB(const std::vector<UserCredentials>& UsersDB)
    {
        _UpdatedUserDB = UsersDB;
        // generating the result in updating table 

        return _UpdatedUserDB;
    }

    void UserDomain::viewUsers(const std::vector<UserCredentials>& UsersDB)
    {
        line();
        std::cout << std::setw(49) << "list of users\n";
        line();
        std::cout << std::setw(15) << "Id" << std::setw(20) << "Name" << std::setw(20) << "Role" << "\n";
        line();

        for (const auto& c : UsersDB)
            std::cout << std::setw(15) << std::to_string(c.userID) << std::setw(20) << c.userName << std::setw(20) << c.roles[0] << std::endl;
        line();
    }

    void UserDomain::viewUserProfiles(const std::vector<UserCredentials>& UsersDB)
    {

        line();
        std::cout << std::setw(49) << "User profiles\n";
        line();
        std::cout << std::setw(15) << "User Name" << std::setw(20) << "Pass Phrase" << std::setw(20) << "Role" << std::setw(20) << "Status" << "\n";
        line();

        for (const auto& c : UsersDB)
        {
            std::string userStatus;
            if (c.status == 1) userStatus = "Access Allowed";
            else userStatus = "Access Denied";
            std::cout << std::setw(15) << c.userName << std::setw(20) << c.passPhrase << std::setw(20) << c.roles[0] << std::setw(20) << userStatus << std::endl;
        }

        line();
    }

    // ADDING NEW USER TO THE MEMORY DATABASE 
    std::vector<UserCredentials>  UserDomain::addUser(const int UserID, const std::string UserName, const std::string Role)
    {
        UserCredentials newUser = { UserID,  UserName, "123456", {Role}, 1 }; 
        _UpdatedUserDB.push_back(newUser); // add new User to list of static User 

        return _UpdatedUserDB;
    }

    UserCredentials   UserDomain::searchUserId(const int UserId) 
    {
        for (const auto& StoredUser : _UpdatedUserDB)
        {
            if (StoredUser.userID == UserId)
            {
                _User = StoredUser;
            }
        }

        return _User;
    }

    std::vector<UserCredentials> UserDomain::updateUser(const UserCredentials& User)
    {
        _User = searchUserId(User.userID);
        int ReplaceIndex = User.userID - 1;
        if (User.userName != "") 
        {
            _User.userName = User.userName;
        }
        if (User.passPhrase != "") 
        {
            _User.passPhrase = User.passPhrase;
        }
        if (User.roles[0] != "")
        {
            _User.roles = User.roles;
        }
        if (User.status != -1) 
        {
            _User.status = User.status;
        }

        _UpdatedUserDB.at(ReplaceIndex) = _User;

        return _UpdatedUserDB;
    }

    UserManagement::UserManagement(const UserCredentials& user) : UserDomain("User Management", user)
    {

        _commandDispatch = {

                         { "Add User", AddUser },
                         { "View All Users", ViewUsers },
                         { "View All User Profiles", ViewUserProfiles },
                         { "Update User Profile", UpdateUser },
                         { "Delete User", DeleteUser }//,

        };
    };
}

//Envent domain implemention
namespace Domain::Event

{
    auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();

    void line()
    {
        for (int i = 1; i < 41; i++)
            std::cout << "--";
        std::cout << "\n";

    }

    EventDomain::EventDomain(const std::string& description, const UserCredentials& user) : _name(description), _Creator(user)
    {
        _logger << "Acess to  \"" + _name + "\" being used by " + _Creator.userName;
    }


    std::vector<std::string> EventDomain::getCommandsEvent()
    {
        std::vector<std::string> availableCommands;
        availableCommands.reserve(_commandDispatch.size());

        for (const auto& [command, function] : _commandDispatch) availableCommands.emplace_back(command);

        return availableCommands;
    }

    std::any EventDomain::executeCommandEvent(const std::string& command, const std::vector<std::string>& args)
    {
        std::string parameters;
        for (const auto& arg : args)  parameters += '"' + arg + "\"  ";
        _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

        auto it = _commandDispatch.find(command);

        auto results = it->second(*this, args);

        return results;
    }

    // get updating the static data of Events
    std::vector<Event> EventDomain::EventsDB(const std::vector<Event>& EventsDB)
    {
        _UpdatedEventDB = EventsDB;
        // generating the result in updating table 

        return _UpdatedEventDB;
    }

    // get updating the static data of UserEvents
    std::vector<UserEvents> EventDomain::UserEventsDB(const std::vector<UserEvents>& UserEventsDB)
    {
        _UpdatedUserEventsDB = UserEventsDB;
        // generating the result in updating table 

        return _UpdatedUserEventsDB;
    }

    std::vector<UserCredentials> EventDomain::UsersDB(const std::vector<UserCredentials>& UsersDB)
    {
        _UpdatedUserDB = UsersDB;
        // generating the result in updating table 

        return _UpdatedUserDB;
    }

    void EventDomain::viewEvents(const std::vector<Event>& EventsDB)
    {
        line();
        std::cout << std::setw(49) << "list of users\n";
        line();
        std::cout << std::setw(15) << "Id" << std::setw(20) << "Event" << std::setw(20) << "Time" << std::setw(20) << "Location" << "\n";
        line();

        for (const auto& c : EventsDB)
            std::cout << std::setw(15) << std::to_string(c.eventID) << std::setw(20) << c.eventName << std::setw(20) << c.eventTime << std::setw(20) << c.eventLocation << std::endl;
        line();
    }

    void EventDomain::viewUserEvents(const std::vector<UserEvents>& UserEventsDB, const std::vector<UserCredentials>& UsersDB)
    {
        line();
        std::cout << std::setw(49) << "list of users and user events\n";
        line();
        std::cout << std::setw(15) << "Id" << std::setw(20) << "User Name" << std::setw(20) << "Role" << std::setw(20) << "Free time" << std::setw(20) << "Events" << "\n";
        line();

        for (const auto& c : UserEventsDB)
        {
            std::string userName = "";
            std::vector<std::string> userRole = {};
            std::string s1, s2;
            for (const auto& StoredUser : UsersDB)
            {
                if (StoredUser.userID == c.userID)
                {
                    userName = StoredUser.userName;
                    userRole = StoredUser.roles;
                }
            }
            for (const auto& t : c.freeTime)
            {
                s1 = s1 + t + ", ";
            }
            std::string freeTime = s1.substr(0, s1.size() - 2);
            for (const auto& e : c.events)
            {
                s2 = s2 + e + ", ";
            }
            std::string events = s2.substr(0, s2.size() - 2);

            std::cout << std::setw(15) << std::to_string(c.userID) << std::setw(20) << userName << std::setw(20) << userRole[0] << std::setw(20) << freeTime << std::setw(20) << events << std::endl;
        }
            
        line();
    }

    std::vector<std::string> EventDomain::availableTimes(const std::vector<UserEvents> UserEventsDB, const std::string UserIDs)
    {
        std::string s1 = UserIDs;
        std::vector<int> res;
        std::vector<std::string> meetingTime;
        while (!s1.empty())
        {
            if (s1.find(" ") == std::string::npos)
            {
                res.push_back(stoi(s1));
                s1.clear();
                break;
            }
            std::string s_temp = s1.substr(0, s1.find(" "));
            res.push_back(stoi(s_temp));
            s1.erase(0, s1.find(" ") + 1);
        }
        for (const auto& t : UserEventsDB[res[0] - 1].freeTime)
        {
            size_t i = 1;
            int _bool = 0;
            while (i != res.size())
            {
                for (const auto& tmp : UserEventsDB[res[i] - 1].freeTime)
                {
                    if (tmp == t) _bool = 1;
                }
                if (_bool == 0) break;
                else ++i;
            }
            if (_bool == 1) meetingTime.push_back(t);
        }

        return meetingTime;
    }

    std::vector<std::string> EventDomain::availableLocations(const std::vector<Event> EventsDB, std::vector<std::string> OfficeValues, const std::string Time)
    {
        std::vector<std::string> locations = OfficeValues;
        for (const auto& e : EventsDB)
        {
            if (e.eventTime == Time)
            {
                std::vector<std::string>::iterator it;
                for (it = locations.begin(); it != locations.end(); )
                {
                    if (*it == e.eventLocation) { it = locations.erase(it); }
                    else { ++it; }
                }
            }
        }

        return locations;
    }

    // ADDING NEW EVENT TO THE MEMORY DATABASE 
    std::vector<Event>  EventDomain::addEvent(const Event& Event)
    {
        _UpdatedEventDB.push_back(Event); // add new User to list of static User 

        return _UpdatedEventDB;
    }

    Event   EventDomain::searchEventId(const int EventId)
    {
        for (const auto& StoredEvent : _UpdatedEventDB)
        {
            if (StoredEvent.eventID == EventId)
            {
                _Event = StoredEvent;
            }
        }

        return _Event;
    }

    std::vector<Event> EventDomain::updateEvent(const Event& Event)
    {
        _Event = searchEventId(Event.eventID);
        int ReplaceIndex = Event.eventID - 1;
        if (Event.eventName != "")
        {
            _Event.eventName = Event.eventName;
        }
        if (Event.eventUsers[0] != 0)
        {
            _Event.eventUsers = Event.eventUsers;
        }
        if (Event.eventTime != "")
        {
            _Event.eventTime = Event.eventName;
        }
        if (Event.eventLocation != "")
        {
            _Event.eventLocation = Event.eventLocation;
        }

        _UpdatedEventDB.at(ReplaceIndex) = _Event;

        return _UpdatedEventDB;
    }

    EventManagement::EventManagement(const UserCredentials& user) : EventDomain("Event Management", user)
    {
        
        _commandDispatch = {

                         { "Add New Meeting", AddEvent },
                         { "View All Meetings", ViewEvents },
                         { "Update Meeting", UpdateEvent },
                         { "Delete Meeting", DeleteEvent }
        };
    };
}


// session domain implementation 
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

    _commandDispatch = {
                         { "Client Management", ClientManagement },
                         { "Event Management",  EventManagement },
                         { "Ask IT for Help",   AskHelp }
    };
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
    //};
  }
}    // namespace Domain::Session
