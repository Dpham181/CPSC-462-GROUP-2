#pragma warning(disable:4996)
#include "Domain/Session/Session.hpp"
#include "Domain/Client/Client.hpp"
#include "Domain/Product/Product.hpp"
#include "Domain/Sale/Sale.hpp"
#include "Domain/User/User.hpp"
#include "Domain/Event/Event.hpp"

#include "Domain/Subscription/Subscription.hpp"

#include <string>
#include <any>
#include <iomanip>     // setw()
#include <locale>       // touuper(), locale()
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>

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
     auto newproduct = productcontrol.add(increment, agrs[0], std::atoi(agrs[1].c_str()), std::atoi(agrs[2].c_str()));

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
     productcontrol.view();
     auto newDBproduct = productcontrol.modify(std::atoi(agrs[0].c_str()), agrs[1], std::atoi(agrs[2].c_str()));
     return newDBproduct;

 }
 std::any Delproduct(Domain::Product::ProductDomain& productcontrol, const std::vector<std::string>& agrs)
 {
     productcontrol.view();
     auto newDBproduct = productcontrol.del(std::atoi(agrs[0].c_str()));

     return newDBproduct;

 }
 // sale management 
 STUB(SaleManagement)
#define STUBS(functionName)  std::any functionName( Domain::Sale::SaleDomain & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  

     std::any makesale(Domain::Sale::SaleDomain& saleto, const std::vector<std::string>& args) {
     std::vector<int> productsId;
     for (unsigned i = 2; i != args.size(); ++i)
     {
         productsId.push_back(std::atoi(args[i].c_str()));

     }
     //todo
     auto onesale = saleto.MakeSale(std::atoi(args[0].c_str()), std::atoi(args[1].c_str()), productsId);

     saleto.GenerateCommission(onesale.Commission_ID);
     return onesale;
 }

 // User management
 STUB(UserManagement)

     std::any AddUser(Domain::User::UserDomain& session, const std::vector<std::string>& agrs)
 {

     auto result = session.addUser(std::atoi(agrs[0].c_str()), agrs[1], agrs[2]);

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
 // manageSubscription
 STUB(manageSubscription);


 // IT Admin actions
 STUB(BackupDB)
     STUB(Shutdown)

     // Assistant actions
     STUB(AskHelp)

  
  
}    // anonymous (private) working area


// sale domain implementtation
namespace Domain::Sale {
    auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();

    void line()
    {
        for (int i = 1; i < 41; i++)
            std::cout << "--";
        std::cout << "\n";

    }

    SaleDomain::SaleDomain(const std::string& description, const UserCredentials& user) : _name(description), _Usedby(user)
    {
        _logger << "Acess to  \"" + _name + "\" being used by " + _Usedby.userName;

        _ListOfSale = persistentData.PurchasedHistory(); if (_ListOfSale.size() > 0)   _logger << "Sale Statis Database in use\"";
        _ListofCommissions = persistentData.CHistory(); if (_ListofCommissions.size() > 0)   _logger << "Commission  Statis Database in use\"";

    }


    std::vector<std::string> SaleDomain::getCommandsSale()
    {
        std::vector<std::string> availableCommands;
        availableCommands.reserve(_commandDispatch.size());

        for (const auto& [command, function] : _commandDispatch) availableCommands.emplace_back(command);

        return availableCommands;
    }

    std::any SaleDomain::executeCommandSale(const std::string& command, const std::vector<std::string>& args)
    {
        std::string parameters;
        for (const auto& arg : args)  parameters += '"' + arg + "\"  ";
        _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

        auto it = _commandDispatch.find(command);

        auto results = it->second(*this, args);

        return results;
    }
    Sale  SaleDomain::MakeSale(const int UserId, const int ClientId, const std::vector<int> purchasedProduct) {

        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        _OneSale.id = _ListOfSale.size() + 1;

        _OneSale.ClientId = ClientId;

        _OneSale.UserId = UserId;

        _OneSale.Commission_ID = _ListofCommissions.size() + 1;


        std::ostringstream oss;
        oss << std::put_time(std::localtime(&now), "%Y-%m-%d %X");
        auto str = oss.str();
        _OneSale.DateOfSale = str;


        for (const auto& p : purchasedProduct) {
            _OneSale.ProductsId.push_back(p);
        }
        return  _OneSale;
    }
    Commission SaleDomain::GenerateCommission(const int CommissionId) {
        _OneComission.ID = CommissionId;

        _ListofCommissions.push_back(_OneComission);
        return   _OneComission;
    }
    void SaleDomain::ViewSale(const Sale& sale) {



        line();
        std::cout << std::setw(49) << "Sale Invoice\n";
        line();
        std::cout << "Sale Id" << std::setw(15) << "Commission Id" << std::setw(15) << "Sale By" << std::setw(15) << "Sale To" << std::setw(25) << "Date Of sale\n";
        line();
        std::cout << std::setw(5) << std::to_string(sale.id) << std::setw(15) << std::to_string(sale.Commission_ID) << std::setw(15) << std::to_string(sale.UserId) << std::setw(15) << std::to_string(sale.ClientId) << std::setw(30) << sale.DateOfSale << std::endl;
        line();
    }
    SaleManagement::SaleManagement(const UserCredentials& user) : SaleDomain("Sale Management", user)
    {

        _commandDispatch = {

                         { "Make Sale", makesale },

        };
    };

}
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

    ClientDomain::ClientDomain(const std::string& description, const UserCredentials& user) : _name(description), _Creator(user)
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
        _Clientprofile.client_id = Client.clientid;
        _Clientprofile.dob = "";
        _Clientprofile.income = 0;
        _UpdatedprofileDB.push_back(_Clientprofile);
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

    std::vector<Clientprofile> ClientDomain::UpdateClientProfile(const int ClientID, const std::string DOB, const int Income) {

        _Clientprofile = { ClientID ,"",0 };
        int ReplaceIndex = ClientID - 1;
        if (DOB != "")  _Clientprofile.dob = DOB;
        if (Income > 0) _Clientprofile.income = Income;
        _UpdatedprofileDB.at(ReplaceIndex) = _Clientprofile;


        return   _UpdatedprofileDB;
    }

    ClientManagement::ClientManagement(const UserCredentials& user) : ClientDomain("Client Management", user)
    {

        _commandDispatch = {

                         { "Add Client", Add },
                         {"View All Clients", View},
                         { "Update Client Profile", Update },
                         { "View Client Profile", ViewClientProfile }//,

        };
    };


}
// Product domain implementation 
namespace Domain::Product

{
    auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
    char reponse;
    void line()
    {
        for (int i = 1; i < 41; i++)
            std::cout << "--";
        std::cout << "\n";

    }
    void menu(std::string message) {

        do
        {
            std::cout << message + " (Y/N/Q)";
            std::cin >> reponse;
            reponse = std::toupper(reponse, std::locale());
        } while (reponse != 'Y' && reponse != 'Q');

    }
    ProductDomain::~ProductDomain() noexcept
    {
        _logger << "Session \"" + _name + "\" shutdown successfully";


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


    std::vector<Product> ProductDomain::view() {

        line();
        std::cout << std::setw(49) << "Inventory of CRM\n";
        line();
        std::cout << std::setw(15) << "Id" << std::setw(15) << "Name" << std::setw(15) << "Price" << std::setw(15) << "CompanyID\n";
        line();

        for (const auto& p : _ProductDb)
            std::cout << std::setw(15) << std::to_string(p.id) << std::setw(15) << p.Name << std::setw(15) << std::to_string(p.Price) << std::setw(15) << std::to_string(p.ProductCommany) << std::endl;
        line();
        return _ProductDb;
    }
    void ProductDomain::viewCompany() {

        line();
        std::cout << std::setw(49) << "Here is the list of PartnerShips\n";
        line();
        std::cout << std::setw(15) << "Id" << std::setw(15) << "Name" << std::setw(25) << "Rate %\n";
        line();

        for (const auto& c : persistentData.CRMCompanypartnerships())
            std::cout << std::setw(15) << std::to_string(c.Id) << std::setw(20) << c.Name << std::setw(15) << std::to_string(c.Rate) << std::endl;
        line();
    }
    Product   ProductDomain::add(const int ProductId, const std::string ProductName, const int Price, const int CompanyID) {

        Product newProduct = { 0,"",0, 0 };
        if (ProductId > 0) newProduct.id = ProductId;
        if (ProductName != "") newProduct.Name = ProductName;
        if (Price > 0) newProduct.Price = Price;
        for (auto const& c : persistentData.CRMCompanypartnerships()) {
            if (c.Id == CompanyID) newProduct.ProductCommany = CompanyID;

        }


        return   newProduct;
    }
    std::vector<Product> ProductDomain::save(const Product& Newproduct) {
        menu("Do you want to add this product?");

        if (reponse == 'Y') _ProductDb.push_back(Newproduct);

        return _ProductDb;
    }
    std::vector<Product>   ProductDomain::del(const int ProductId) {
        menu("Do you want to add del this product?");

        // if unorder index -> need to loop for finding value and remove after.  

            //auto* front = &_ProductDb.front();
            //for (const auto& p : _ProductDb)
            //    if (p.id == ProductId) {
            //        auto position = std::distance(front, &p);
            //    }

        // this method is only work with order index
        int removeat = ProductId - 1;

        if (reponse == 'Y') _ProductDb.erase(_ProductDb.begin() + removeat);
        return _ProductDb;
    }
    std::vector<Product>   ProductDomain::modify(const int CurrentProductId, const std::string ProductName, const int Price) {
        // this also only works with order index 
        menu("Do you want to continute?");
        int ReplaceIndex = 0;

        for (auto& p : _ProductDb) {
            if (p.id == CurrentProductId) {
                ReplaceIndex = p.id - 1;
                if (ProductName != "") p.Name = ProductName;
                if (Price > 0) p.Price = Price;
                _ProductDb.at(ReplaceIndex) = p;
            }
        }
        return _ProductDb;
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
namespace Domain::Subscription

{
    auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
    void line()
    {
        for (int i = 1; i < 41; i++)
            std::cout << "--";
        std::cout << "\n";

    }
    char reponse;
    void menu(std::string message) {

        do
        {
            std::cout << message + " (Y/N/Q)";
            std::cin >> reponse;
            reponse = std::toupper(reponse, std::locale());
        } while (reponse != 'Y' && reponse != 'Q');

    }
    SubscriptionDomain::SubscriptionDomain(const std::string& description, const UserCredentials& user) : _name(description), _Usedby(user)
    {
        _logger << "Acess to  \"" + _name + "\" being used by " + _Usedby.userName;
       

    }
    SubscriptionDomain::~SubscriptionDomain() noexcept
    {
        _logger << "Session \"" + _name + "\" shutdown successfully";


    }
    std::vector<std::string> SubscriptionDomain::getCommandsSubscription()
    {
        std::vector<std::string> availableCommands;
        availableCommands.reserve(_commandDispatch.size());

        for (const auto& [command, function] : _commandDispatch) availableCommands.emplace_back(command);

        return availableCommands;
    }

    std::any SubscriptionDomain::executeCommandSubscription(const std::string& command, const std::vector<std::string>& args)
    {
        std::string parameters;
        for (const auto& arg : args)  parameters += '"' + arg + "\"  ";
        _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

        auto it = _commandDispatch.find(command);

        auto results = it->second(*this, args);

        return results;
    }


    SubscriptionStatus SubscriptionDomain::viewSubscriptionStatus() {
        return persistentData.StacticSubscriptionSatus();
    }
    PaymentOption SubscriptionDomain::selectSubscription(const Subcripstion  & SelectedId) {
     

        for (const auto& s : persistentData.ShowAllSubcripstion()) {
            if (s.SubsID == SelectedId.SubsID) {

                line();
                std::cout << std::setw(49) << "Review Your Order\n";
                line();
                std::cout << std::setw(15) << "Package" << std::setw(20) << "Price" << std::setw(20) << "Description" << "\n";
                line();
                std::cout << std::setw(15) << s.SubsType << std::setw(20) << s.Price << std::setw(20) <<s.Description << std::endl;
                line();
                menu("Do you want to continue to pay?");
                if (reponse == 'Y') {
                    for (const auto& p : persistentData.ShowAllPaymentOption()) {

                        // todo
                    }
                }
            }
        }

    }
    bool validationPayment(const std::string CCnumber, const int CVCnumber) {
        if (CCnumber.length() == 16 && std::to_string(CVCnumber).length() == 4 ) {
            return true;
        }
        return false;
    }
    std::string SubscriptionDomain::completePayment() {
        // todo
    }

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
        std::cout << std::setw(49) << "List of Users\n";
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
        for (int i = 1; i < 51; i++)
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

    void EventDomain::viewEvents(const std::vector<Event>& EventsDB, const std::vector<UserCredentials> UsersDB)
    {
        line();
        std::cout << std::setw(59) << "List of Events\n";
        line();
        std::cout << std::setw(10) << "Id" << std::setw(20) << "Event" << std::setw(35) << "Participants" << std::setw(15) << "Time" << std::setw(15) << "Location" << "\n";
        line();

        for (const auto& c : EventsDB)
        {
            std::string participants = "";
            std::string s1;
            for (const auto& p : c.eventUsers) 
            {
                for (const auto& StoredUser : UsersDB)
                {
                    if (StoredUser.userID == p)
                    {
                        s1 = s1 + StoredUser.userName + ", ";
                    }
                }
            }
            participants = s1.substr(0, s1.size() - 2);
            std::cout << std::setw(10) << std::to_string(c.eventID) << std::setw(20) << c.eventName << std::setw(35) << participants << std::setw(15) << c.eventTime << std::setw(15) << c.eventLocation << std::endl;
        }

        line();
    }

    void EventDomain::viewUserEvents(const std::vector<UserEvents>& UserEventsDB, const std::vector<UserCredentials>& UsersDB)
    {
        line();
        std::cout << std::setw(59) << "List of Users and User Events\n";
        line();
        std::cout << std::setw(5) << "Id" << std::setw(15) << "User Name" << std::setw(20) << "Role" << std::setw(20) << "Free time" << "     " << "Events" << "\n";
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
                s2 = s2 + e + " | ";
            }
            std::string events = s2.substr(0, s2.size() - 2);

            std::cout << std::setw(5) << std::to_string(c.userID) << std::setw(15) << userName << std::setw(20) << userRole[0] << std::setw(20) << freeTime << "     " << events << std::endl;
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
        int index1 = res[0] - 1;
        for (const auto& t : UserEventsDB[index1].freeTime)
        {
            size_t i = 1;
            int _bool = 0;
            while (i != res.size())
            {
                int index2 = res[i] - 1;
                for (const auto& tmp : UserEventsDB[index2].freeTime)
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
        {"Product Management", ProductManagement},

        {"Sale Management", SaleManagement}
    };
  }




  SalesManagerSession::SalesManagerSession( const UserCredentials & credentials ) : SessionBase( "Sales Manager", credentials )
  {
    _logger << "Login Successful for \"" + credentials.userName + "\" as role \"Sales Manager\".";

    _commandDispatch = { {"Manage Subscription", manageSubscription},
                      
    };
  }
}    // namespace Domain::Session
