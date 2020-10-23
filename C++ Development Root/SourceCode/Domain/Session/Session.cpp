#include "Domain/Session/Session.hpp"
#include "Domain/Client/Client.hpp"
#include "Domain/Product/Product.hpp"
#include "Domain/Sale/Sale.hpp"

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
    
     //todo
     auto onesale = saleto.MakeSale(std::atoi(args[0].c_str()), std::atoi(args[1].c_str()), {});
 }

  
  
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
       
        _ListOfSale = persistentData.PurchasedHistory(); if (_ListOfSale.size() >0)   _logger << "Sale Statis Database in use\"";
        _ListofCommissions = persistentData.CommissionHistory(); if (_ListofCommissions.size() > 0)   _logger << "Commission  Statis Database in use\"";
       
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
    Sale  SaleDomain::MakeSale( const int UserId, const int ClientId, const std::vector<Product> purchasedProduct) {
       
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        _OneSale.id= _ListOfSale.size() + 1;

        _OneSale.ClientId = ClientId;

        _OneSale.UserId = UserId;

        _OneSale.Commission_ID = _ListofCommissions.size() + 1;


        std::ostringstream oss;
        oss << std::put_time(std::localtime(&now), "%Y-%m-%d %X");
        auto str = oss.str();
        _OneSale.DateOfSale = str;


        for (const auto&  p : purchasedProduct) {
            _OneSale.ProductsId.push_back(p.id) ;
        }
        return  _OneSale;
    }
    Commission SaleDomain::GenerateCommission(const int CommissionId) {
        _OneComission.ID = CommissionId;

        _ListofCommissions.push_back(_OneComission);
        return   _OneComission;
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
        std::cout << std::setw(15) << "Id" << std::setw(15) << "Name" << std::setw(15) << "Price" << std::setw(15) << "CompanyID\n";
        line();

        for (const auto& p : _ProductDb)
           std::cout << std::setw(15) << std::to_string(p.id) << std::setw(15) << p.Name << std::setw(15) << std::to_string(p.Price)<< std::setw(15) << std::to_string(p.ProductCommany)<< std::endl;
        line();
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
    Product   ProductDomain::add(const int ProductId, const std::string ProductName, const int Price , const int CompanyID) {

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
      
            for ( auto& p : _ProductDb) {
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
        {"Product Management", ProductManagement},
        {"Sale Management", SaleManagement}
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
