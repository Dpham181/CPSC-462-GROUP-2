#include "UI/SimpleUI.hpp"

#include <any>         // any_cast()
#include <iomanip>     // setw()
#include <iostream>    // streamsize
#include <limits>      // numeric_limits
#include <memory>      // unique_ptr, make_unique<>()
#include <string>      // string, getline()
#include <vector>
#include <locale>       // touuper(), locale()

#include "Domain/Session/SessionHandler.hpp"
#include "Domain/Client/Client.hpp"   
#include "Domain/User/User.hpp"
#include "Domain/Event/Event.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace UI
{
    // Default constructor
    SimpleUI::SimpleUI()
        :    // will replace these with factory calls in the next increment

        _loggerPtr(TechnicalServices::Logging::LoggerHandler::create()),
        _persistentData(TechnicalServices::Persistence::PersistenceHandler::instance())
    {
        _logger << "Simple UI being used and has been successfully initialized";
    }



    // Destructor
    SimpleUI::~SimpleUI() noexcept
    {
        _logger << "Simple UI shutdown successfully";
    }


    void line()
    {
        for (int i = 1; i < 41; i++)
            std::cout << "--";
        std::cout << "\n";

    }

    // Operations
    void SimpleUI::launch()
    {
        // 1) Fetch Role legal value list

        std::vector<std::string> roleLegalValues = _persistentData.findRoles();
        std::vector<std::string> officeValues = _persistentData.findOffices();

        std::vector<TechnicalServices::Persistence::Client> ClientsFromDB = _persistentData.ShowAllClients();
        std::vector<TechnicalServices::Persistence::Clientprofile> ClientsProfileFromDB = _persistentData.ShowAllClientsProfile();
        std::vector<TechnicalServices::Persistence::Product> InventoryFromDB = _persistentData.CRMInventory();
        std::vector<TechnicalServices::Persistence::Sale> SaleFromDB = _persistentData.PurchasedHistory();
        std::vector<TechnicalServices::Persistence::UserCredentials> UsersFromDB = _persistentData.ShowAllUsers();
        std::vector<TechnicalServices::Persistence::UserEvents> UserEventsFromDB = _persistentData.ShowAllUserEvents();
        std::vector<TechnicalServices::Persistence::Event> EventsFromDB = _persistentData.ShowAllEvents();

        // 2) Present login screen to user and get username, password, and valid role
        Domain::Session::UserCredentials credentials = { 0, "", "", {""}, 0 };// ensures roles[0] exists
       


        std::unique_ptr<Domain::Session::SessionHandler> sessionControl;

        do
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "  name: ";
            std::getline(std::cin, credentials.userName);

            std::cout << "  pass phrase: ";
            std::getline(std::cin, credentials.passPhrase);

            sessionControl = Domain::Session::SessionHandler::createSession(credentials);
            if (sessionControl != nullptr)
            {
                break;
            }
          
        } while (true);

        // Show upcoming events when user login
        std::cout << std::endl;
        std::cout << "[Notice] Upcoming events: ";
        for (const auto& _user : UsersFromDB) 
        {
            int i = 0;
            if (credentials.userName == _user.userName)
            { 
                i = _user.userID;
            }
            for (const auto& _userEvent : UserEventsFromDB) 
            {
                if (_userEvent.userID == i)
                {
                    std::vector<std::string> _events = _userEvent.events;
                    for (const auto& _eventStr : _events)
                    {
                        std::cout << _eventStr << ". ";
                    }
                }
            }
        }
        std::cout << std::endl;


        // 4) Fetch functionality options for this role
        do
        {
            auto        commands = sessionControl->getCommands();
            std::string selectedCommand;
            unsigned    menuSelection;

            do
            {
                for (unsigned i = 0; i != commands.size(); ++i) std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
                std::cout << std::setw(2) << commands.size() << " - " << "Quit\n";

                std::cout << "  action (0-" << commands.size() << "): ";
                std::cin >> menuSelection;
            } while (menuSelection > commands.size());

            if (menuSelection == commands.size()) break;

            selectedCommand = commands[menuSelection];
            _logger << "Command selected \"" + selectedCommand + '"';


            /******************************************************************************************************************************
            **  5) The user interface will collect relevant information to execute the chosen command.  This section requires the UI to
            **     know what information to collect, and hence what the available commands are.  Our goal is loose (minimal) coupling, not
            **     no coupling. This can be achieved in a variety of ways, but one common way is to pass strings instead of strong typed
            **     parameters.
            ******************************************************************************************************************************/
          
            if (selectedCommand == "Client Management")
            {
                // call client handler 
                std::unique_ptr<Domain::Client::ClientHandler> ClientHandler;
                // checking if user role is correct for using client management 
                ClientHandler = Domain::Client::ClientHandler::UseClientManagement(credentials);

                // return the client management session ortherwise not allow to access
                if (ClientHandler != nullptr) {
                    ClientsFromDB = ClientHandler->ClientsDB(ClientsFromDB);

                    do
                    {
                        // list all the command avaliable in client management 
                        auto        commands = ClientHandler->getCommandsClient();
                        std::string selectedCommand;
                        unsigned    menuSelection;

                        do
                        {

                            for (unsigned i = 0; i != commands.size(); ++i) std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
                            std::cout << std::setw(2) << commands.size() << " - " << "Back to Main Menu\n";

                            std::cout << "  action (0-" << commands.size() << "): ";
                            std::cin >> menuSelection;
                        } while (menuSelection > commands.size());

                        if (menuSelection == commands.size()) break;
                        selectedCommand = commands[menuSelection];
                        _logger << "Command selected \"" + selectedCommand + '"';

                        // adding a new client to memory database  
                        if (selectedCommand == "Add Client") {
                            std::vector<std::string> parameters(4);
                            parameters[0] = credentials.userName;
                            parameters[1] = std::to_string(ClientsFromDB.size() + 1);
                            std::cout << " Enter Name  ";  std::cin >> std::ws;  std::getline(std::cin, parameters[2]);
                            std::cout << " Enter Phone: ";  std::cin >> std::ws;  std::getline(std::cin, parameters[3]);

                            auto results = ClientHandler->executeCommandClient(selectedCommand, parameters);
                            if (results.has_value()) {
                                _logger << "Successfully Added \" ";
                                ClientsFromDB = std::any_cast<const std::vector<TechnicalServices::Persistence::Client>&>(results);
                                ClientsProfileFromDB.push_back({ std::atoi(parameters[1].c_str()),parameters[2] , std::atoi(parameters[3].c_str()) });

                            }

                        }
                        // view all the current clients include static in database 
                        else if (selectedCommand == "View All Clients") {

                            ClientHandler->ViewClients(ClientsFromDB);
                        }
                        // select to update the profile of client.
                        else if (selectedCommand == "Update Client Profile") {
                            ClientHandler->ClientsPDB(ClientsProfileFromDB);
                            ClientHandler->ViewClients(ClientsFromDB);

                            char response;
                            int clientId = 0;
                            std::cout << "Please choose Client Id: ";
                            std::cin >> clientId;
                            do
                            {
                                std::cout << "Do you want to continue Update Profile for Client with Id # " + std::to_string(clientId) + "? (Y/N/Q)";
                                std::cin >> response;
                                response = std::toupper(response, std::locale());
                            } while (response != 'Y' && response != 'Q');

                            if (response == 'Y') {


                                std::vector<std::string> parameters(3);
                                parameters[0] = std::to_string(clientId);
                                std::cout << " Enter DOB: ";  std::cin >> std::ws;  std::getline(std::cin, parameters[1]);
                                std::cout << " Enter Income:   ";  std::cin >> std::ws;  std::getline(std::cin, parameters[2]);

                                auto results = ClientHandler->executeCommandClient(selectedCommand, parameters);
                                if (results.has_value()) {
                                    _logger << "Successfully Updated\n";
                                    ClientsProfileFromDB = std::any_cast<const std::vector<TechnicalServices::Persistence::Clientprofile>&>(results);

                                }


                            }

                        }
                        else if (selectedCommand == "View Client Profile") {
                            ClientHandler->ClientsPDB(ClientsProfileFromDB);
                            ClientHandler->ViewClients(ClientsFromDB);
                            int clientId = 0;
                            std::cout << "Please choose Client Id: ";
                            std::cin >> clientId;
                            std::vector<std::string> parameter(1);
                            parameter[0] = std::to_string(clientId);
                            auto results = ClientHandler->executeCommandClient(selectedCommand, parameter);


                            if (results.has_value())
                            {
                                Domain::Client::Clientprofile  ProfileofClient = std::any_cast<const TechnicalServices::Persistence::Clientprofile&>(results);
                                line();
                                std::cout << std::setw(49) << "Result of Searching\n";
                                line();
                                std::cout << std::setw(15) << "Id" << std::setw(15) << "DOB" << std::setw(15) << "Income\n";

                                line();
                                std::cout << std::setw(15) << std::to_string(ProfileofClient.client_id) << std::setw(15) << ProfileofClient.dob << std::setw(15) << std::to_string(ProfileofClient.income) + "\n";


                            }
                        }


                    } while (true);

                }

                else if (selectedCommand == "Another command") /* ... */ {}

                else sessionControl->executeCommand(selectedCommand, {});
            }
            else if (selectedCommand == "Product Management") {

                _ProductHandler = Domain::Product::ProductHandler::UseProductManagement(credentials);

                if (_ProductHandler != nullptr) {

                    do
                    {
                        auto        commands = _ProductHandler->getCommandsProduct();
                        std::string selectedCommand;
                        unsigned    menuSelection;

                        do
                        {

                            for (unsigned i = 0; i != commands.size(); ++i) std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
                            std::cout << std::setw(2) << commands.size() << " - " << "Back to Main Menu\n";

                            std::cout << "  action (0-" << commands.size() << "): ";
                            std::cin >> menuSelection;
                        } while (menuSelection > commands.size());

                        if (menuSelection == commands.size()) break;
                        selectedCommand = commands[menuSelection];
                        _logger << "Command selected \"" + selectedCommand + '"';

                        if (selectedCommand == "View Inventory") {

                            _ProductHandler->executeCommandProduct(selectedCommand, {});
                        }
                        else if (selectedCommand == "Add New Product") {

                            std::vector<std::string> parameters(3);
                            std::cout << " Enter Name  ";  std::cin >> std::ws;  std::getline(std::cin, parameters[0]);
                            std::cout << " Enter Price: ";  std::cin >> std::ws;  std::getline(std::cin, parameters[1]);
                            _ProductHandler->viewCompany();
                            std::cout << " Enter Company ID(Leave blank for private partner): ";  std::cin >> std::ws;  std::getline(std::cin, parameters[2]);

                            auto result = _ProductHandler->executeCommandProduct(selectedCommand, parameters);
                            if (result.has_value()) {
                                _logger << "Product Already added to Inventory";

                                InventoryFromDB = _ProductHandler->view();
                            }

                        }
                        else if (selectedCommand == "Modify Product") {


                            int productId = 0;
                            std::cout << "Please choose Product Id: ";
                            std::cin >> productId;
                            std::vector<std::string> parameters(3);
                            parameters[0] = std::to_string(productId);
                            std::cout << " Enter Name  ";  std::cin >> std::ws;  std::getline(std::cin, parameters[1]);
                            std::cout << " Enter Price: ";  std::cin >> std::ws;  std::getline(std::cin, parameters[2]);
                            auto result = _ProductHandler->executeCommandProduct(selectedCommand, parameters);
                            if (result.has_value()) {
                                _logger << "Product Already Modified";
                                InventoryFromDB = _ProductHandler->view();
                            }

                        }
                        else if (selectedCommand == "Del product") {

                            int productId = 0;
                            std::cout << "Please choose Product Id: ";
                            std::cin >> productId;
                            std::vector<std::string> parameter(1);
                            parameter[0] = std::to_string(productId);
                            auto result = _ProductHandler->executeCommandProduct(selectedCommand, parameter);

                            if (result.has_value()) {
                                _logger << "Product Already removed from Inventory";
                                InventoryFromDB = _ProductHandler->view();
                            }
                        }


                    } while (true);

                }

            }
            else if (selectedCommand == "Sale Management") {

                _SaleHandler = Domain::Sale::SaleHandler::UseSaleManagement(credentials);


                if (_SaleHandler != nullptr) {

                    do
                    {
                        auto        commands = _SaleHandler->getCommandsSale();
                        std::string selectedCommand;
                        unsigned    menuSelection;

                        do
                        {

                            for (unsigned i = 0; i != commands.size(); ++i) std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
                            std::cout << std::setw(2) << commands.size() << " - " << "Back to Main Menu\n";

                            std::cout << "  action (0-" << commands.size() << "): ";
                            std::cin >> menuSelection;
                        } while (menuSelection > commands.size());


                        if (menuSelection == commands.size()) break;
                        selectedCommand = commands[menuSelection];
                        _logger << "Command selected \"" + selectedCommand + '"';

                        if (selectedCommand == "Make Sale") {
                            int selectedProduct;
                            std::vector<int> productsPurchased;
                            std::vector<std::string> parameters(2);
                            parameters[0] = std::to_string(_persistentData.findCredentialsByName(credentials.userName).userID);
                            std::cout << " Enter Your Client Id: ";  std::cin >> std::ws;  std::getline(std::cin, parameters[1]);
                            std::cout << " Please Choose the Product Match with CommandLine then Hit Process!!!\n";
                            do {
                                unsigned    menuSelection;
                                do
                                {

                                    for (unsigned i = 0; i != InventoryFromDB.size(); ++i) std::cout << std::setw(2) << i << " - " << InventoryFromDB[i].Name << "->"<< InventoryFromDB[i].Price<<"$" << '\n';
                                    std::cout << std::setw(2) << InventoryFromDB.size() << " - " << "Process\n";

                                    std::cout << "  action (0-" << InventoryFromDB.size() << "): ";
                                    std::cin >> menuSelection;

                                    //TODO
                                } while (menuSelection > InventoryFromDB.size());

                                if (menuSelection == InventoryFromDB.size()) break;
                                selectedProduct = InventoryFromDB[menuSelection].id;

                                if (selectedProduct > 0) {

                                    parameters.push_back(std::to_string(selectedProduct));
                                    _logger << "Added product  -> \"" + InventoryFromDB[menuSelection].Name + '"';

                                }

                            } while (true);

                            auto result = _SaleHandler->executeCommandSale(selectedCommand, parameters);
                            if (result.has_value()) {
                                TechnicalServices::Persistence::Sale salerecord = std::any_cast<const TechnicalServices::Persistence::Sale&>(result);
                                _SaleHandler->ViewSale(salerecord);
                                SaleFromDB.push_back(salerecord);
                                int subtotal = 0;
                                line();
                                std::cout << std::setw(49) << "list of Purchased Product\n";
                                line();
                                std::cout << std::setw(15) << "Id" << std::setw(15) << "Name" << std::setw(15) << "Price\n";
                                line();
                                for (const auto& productid : salerecord.ProductsId) {
                                    for (const auto& productidDB : InventoryFromDB) {
                                        if (productidDB.id == productid) {
                                            std::cout << std::setw(15) << std::to_string(productidDB.id) << std::setw(15) << productidDB.Name << std::setw(15) << std::to_string(productidDB.Price) << std::endl;
                                            subtotal += productidDB.Price;
                                        }
                                    }
                                }
                                line();
                                std::cout << std::setw(40) << "SubTotal:    " + std::to_string(subtotal) + "$\n";

                            }
                        }
                    } while (true);
                }
                else _logger << "Your account got Locked Please contact It Admin for more Infor";

                



            }
            else if (selectedCommand == "Manage Subscription") {
                 _SubscriptionHandler = Domain::Subscription::SubscriptionHandler::MaintainSubscription(credentials);
                 if (_SubscriptionHandler != nullptr) {
                     do
                     {
                         auto        commands = _SubscriptionHandler->getCommandsSubscription();
                         std::string selectedCommand;
                         unsigned    menuSelection;


                         do
                         {

                             for (unsigned i = 0; i != commands.size(); ++i) std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
                             std::cout << std::setw(2) << commands.size() << " - " << "Back to Main Menu\n";

                             std::cout << "  action (0-" << commands.size() << "): ";
                             std::cin >> menuSelection;
                         } while (menuSelection > commands.size());

                         if (menuSelection == commands.size()) break;
                         selectedCommand = commands[menuSelection];
                         if (selectedCommand == "Upgrade License") {
                             _logger << "exe 1\"";
                             // todo 
                             auto        Subcripstions = _persistentData.ShowAllSubcripstion();
                             int selectedSubcripstion;
                             unsigned    menuSelection;

                             do
                             {
                                 
                                 line();
                                     std::cout << std::setw(49) << "List of Subscription\n";
                                     line();
                                     std::cout << std::setw(15) << "Choose" << std::setw(15) << "Package" << std::setw(20) << "Price" << std::setw(20) << "AvalibleUsers" << "\n";
                                     line();

                                 for (unsigned i = 0; i != Subcripstions.size(); ++i)

                                 
                                     
                                     std::cout << std::setw(15) << i << std::setw(15) << Subcripstions[i].SubsType << std::setw(20) << Subcripstions[i].Price << std::setw(20) << Subcripstions[i].Description << std::endl;
                                    
                                 
                                 line();
                                   
                                 std::cout << std::setw(2) << Subcripstions.size() << " - " << "Cancel\n";
                                 std::cout << "  action (0-" << Subcripstions.size() << "): ";
                                 std::cin >> menuSelection;
                             } while (menuSelection > Subcripstions.size());
                                    if (menuSelection == Subcripstions.size()) break; 
                            selectedSubcripstion = Subcripstions[menuSelection].SubsID;
                        
                          
                            std::vector<std::string> parameter(1);
                            parameter[0] = std::to_string(selectedSubcripstion);
                            auto result =  _SubscriptionHandler->executeCommandSubscription(selectedCommand, parameter);
                            std::string selectedPaymethod;
                            unsigned    menuPaySelection;
                            if (result.has_value()) {
                                std::vector<TechnicalServices::Persistence::PaymentOption>   PayOps = std::any_cast<const std::vector<TechnicalServices::Persistence::PaymentOption>&>(result);
                                do
                                {

                                   
                                    for (unsigned i = 0; i != PayOps.size(); ++i) std::cout << std::setw(2) << i << " - " << PayOps[i].PaymentTypeName << '\n';
                                    std::cout << std::setw(2) << PayOps.size() << " - " << "Back to Main Menu\n";

                                    std::cout << "  action (0-" << PayOps.size() << "): ";
                                    std::cin >> menuPaySelection;
                                } while (menuPaySelection > PayOps.size());
                                if (menuPaySelection == PayOps.size()) break;
                            }
                         }

                     } while (true);
                  }
                 
                 _logger << "Your License Invalid\"";
                    
                 
            }

            else if (selectedCommand == "User Management")
            {
                std::unique_ptr<Domain::User::UserHandler> UserHandler; // call user domain 
                UserHandler = Domain::User::UserHandler::UseUserManagement(credentials);
                if (UserHandler != nullptr)
                {
                    UsersFromDB = UserHandler->UsersDB(UsersFromDB);

                    do
                    {

                        auto        commands = UserHandler->getCommandsUser();
                        std::string selectedCommand;
                        unsigned    menuSelection;

                        do
                        {

                            for (unsigned i = 0; i != commands.size(); ++i) std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
                            std::cout << std::setw(2) << commands.size() << " - " << "Back to Main Menu\n";

                            std::cout << "  action (0-" << commands.size() << "): ";
                            std::cin >> menuSelection;
                        } while (menuSelection > commands.size());

                        if (menuSelection == commands.size()) break;
                        selectedCommand = commands[menuSelection];
                        _logger << "Command selected \"" + selectedCommand + '"';
                        if (selectedCommand == "Add User")
                        {
                            std::vector<std::string> parameters(3);
                            parameters[0] = std::to_string(UsersFromDB.size() + 1);
                            std::cout << " Enter User Name: ";  std::cin >> std::ws;  std::getline(std::cin, parameters[1]);
                            std::cout << " Select User Role \n";
                            for (size_t i = 0; i < roleLegalValues.size(); ++i)
                            {
                                std::cout << " " << i << " " << roleLegalValues[i] << std::endl;
                            }
                            int roleChoice;
                            do
                            {
                                std::cout << "Please Choose 0-4: ";
                                std::cin >> roleChoice;
                            } while (roleChoice < 0 || roleChoice > 4);
                            parameters[2] = roleLegalValues[roleChoice];

                            auto results = UserHandler->executeCommandUser(selectedCommand, parameters);
                            if (results.has_value())
                            {
                                _logger << "Successfully Added. ";
                                UsersFromDB = std::any_cast<const std::vector<TechnicalServices::Persistence::UserCredentials>&>(results);
                                UserEventsFromDB.push_back({ std::atoi(parameters[0].c_str()), {} , {} });           //add a user profile to User Events
                            }
                        }

                        else if (selectedCommand == "View All Users")
                        {

                            UserHandler->viewUsers( );
                        }

                        else if (selectedCommand == "Block a User")
                        {
                            UserHandler->viewUsers();
                            char response;
                            int userId;
                            std::cout << "Please choose Client Id: ";
                            std::cin >> userId;
                            do
                            {
                                std::cout << "Do you want to block the User with Id # " + std::to_string(userId) + "? (Y/N/Q)";
                                std::cin >> response;
                                response = std::toupper(response, std::locale());
                            } while (response != 'Y' && response != 'Q');

                            if (response == 'Y')
                            {
                                UserHandler->banUser(userId);
                            }
                        }

                        else if (selectedCommand == "Update User Profile")
                        {
                            UserHandler->viewUsers( );
                            char response;
                            int userId;
                            std::cout << "Please choose Client Id: ";
                            std::cin >> userId;
                            do
                            {
                                std::cout << "Do you want to continue Update Profile for User with Id # " + std::to_string(userId) + "? (Y/N/Q)";
                                std::cin >> response;
                                response = std::toupper(response, std::locale());
                            } while (response != 'Y' && response != 'Q');

                            if (response == 'Y') 
                            {
                                std::vector<std::string> parameters(5);
                                parameters[0] = std::to_string(userId);
                                parameters[1] = "";
                                parameters[2] = "";
                                parameters[3] = "";
                                parameters[4] = "-1";
                                bool isFinish = false;
                                do
                                {
                                    std::cout << " Please choose one option: " << std::endl;
                                    std::cout << "  1. Change the User Name\n"
                                              << "  2. Set Password to default\n"
                                              << "  3. Change the User Role" << std::endl;
                                    std::cout << " Your selection: ";  std::cin >> response;
                                    if (response == '1')
                                    {
                                        std::cout << " Enter New UserName: ";  std::cin >> std::ws;  std::getline(std::cin, parameters[1]);
                                        
                                    }
                                    if (response == '2')
                                    {
                                        parameters[2] = "123456";
                                    }
                                    if (response == '3')
                                    {
                                        std::cout << " Select User Role \n";
                                        for (size_t i = 0; i < roleLegalValues.size(); ++i)
                                        {
                                            std::cout << " " << i << " " << roleLegalValues[i] << std::endl;
                                        }
                                        int roleChoice;
                                        do
                                        {
                                            std::cout << "Please Choose 0-4: ";
                                            std::cin >> roleChoice;
                                        } while (roleChoice < 0 || roleChoice > 4);
                                        parameters[3] = roleLegalValues[roleChoice];
                                    }

                                    std::cout << " Do you want to continue change other informations? (Y/N)"; std::cin >> response;
                                    response = std::toupper(response, std::locale());
                                    if (response != 'Y')
                                    {
                                        isFinish = true;
                                    }
                                    std::cout << std::endl;

                                } while (isFinish == false);

                                auto results = UserHandler->executeCommandUser(selectedCommand, parameters);
                                if (results.has_value()) 
                                {
                                    _logger << "Successfully Updated\n";
                                    UsersFromDB = std::any_cast<const std::vector<TechnicalServices::Persistence::UserCredentials>&>(results);
                                }
                                
                            }

                        }

                    } while (true);

                }

            }

            else if (selectedCommand == "Event Management")
            {
            std::unique_ptr<Domain::Event::EventHandler> EventHandler; // call event domain 
            EventHandler = Domain::Event::EventHandler::UseEventManagement(credentials);
            if (EventHandler != nullptr)
            {
                EventsFromDB = EventHandler->EventsDB(EventsFromDB);
                UserEventsFromDB = EventHandler->UserEventsDB(UserEventsFromDB); 
                UsersFromDB = EventHandler->UsersDB(UsersFromDB);

                do
                {

                    auto        commands = EventHandler->getCommandsEvent();
                    std::string selectedCommand;
                    unsigned    menuSelection;

                    do
                    {

                        for (unsigned i = 0; i != commands.size(); ++i) std::cout << std::setw(2) << i << " - " << commands[i] << '\n';
                        std::cout << std::setw(2) << commands.size() << " - " << "Back to Main Menu\n";

                        std::cout << "  action (0-" << commands.size() << "): ";
                        std::cin >> menuSelection;
                    } while (menuSelection > commands.size());

                    if (menuSelection == commands.size()) break;
                    selectedCommand = commands[menuSelection];
                    _logger << "Command selected \"" + selectedCommand + '"';
                    if (selectedCommand == "Add New Meeting")
                    {
                        std::vector<std::string> parameters(5);
                        parameters[0] = std::to_string(EventsFromDB.size() + 1);

                        // Meeting name
                        std::cout << " Enter Meeting Name: ";  std::cin >> std::ws;  std::getline(std::cin, parameters[1]);

                        std::vector<std::string> timeVector = {};
                        std::vector<std::string> locationVector = {};
                        do
                        {
                            // Meeting paticipants
                            std::cout << " Select Meeting Participants \n";
                            EventHandler->viewUserEvents( );
                            std::cout << " Select the User ID(separete with space): "; std::cin >> std::ws;  std::getline(std::cin, parameters[2]);

                            // Meeting time
                            std::cout << " Available Meeting Time \n";
                            timeVector = EventHandler->availableTimes(parameters[2]);
                            if (timeVector.size() == 0)
                            {
                                std::cout << " No available meeting time for selected users " << std::endl;
                                std::cout << " Please choose meeting participants again" << std::endl;
                            }
                            else
                            {
                                for (size_t i = 0; i < timeVector.size(); ++i) std::cout << " " << i + 1 << ". " << timeVector[i] << std::endl;
                                int mt = 0;
                                
                                std::cout << "Please choos the meeting time: "; std::cin >> mt;
                                int index1 = mt - 1;
                                parameters[3] = timeVector[index1];

                                // Meeting location
                                std::cout << " Available Meeting Location \n";
                                locationVector = EventHandler->availableLocations(officeValues, parameters[3]);
                                if (locationVector.size() == 0)
                                {
                                    std::cout << " No available meeting location for selected time " << std::endl;
                                    std::cout << " Please choose meeting participants again" << std::endl;
                                }
                                else
                                {
                                    for (size_t i = 0; i < locationVector.size(); ++i) std::cout << " " << i + 1 << ". " << locationVector[i] << std::endl;

                                    int ml = 0;
                                    
                                    std::cout << " Please choos the meeting Location: "; std::cin >> ml;
                                    int index2 = ml - 1;
                                    parameters[4] = locationVector[index2];

                                }
                            }
                        } while (timeVector.size() == 0 || locationVector.size() == 0);

                        auto results = EventHandler->executeCommandEvent(selectedCommand, parameters);
                        if (results.has_value())
                        {
                            _logger << "Successfully Added. ";
                            EventsFromDB = std::any_cast<const std::vector<TechnicalServices::Persistence::Event>&>(results);
                            EventHandler->sendNotifications(parameters[1], parameters[2], parameters[3], parameters[4]);          // Send notifications and update UserEventsFromDB
                            std::cout << std::endl;
                            std::cout << std::endl;
                        }
                    }

                    else if (selectedCommand == "View All Meetings")
                    {
                        EventHandler->viewEvents( );
                    }

                    else if (selectedCommand == "Update Meeting")
                    {
                        //to do

                    }

                } while (true);

            }

            }
          

            _logger << "Ending session and terminating";
        } while (true);

    }
}
