#include "UI/SimpleUI.hpp"

#include <any>         // any_cast()
#include <iomanip>     // setw()
#include <iostream>    // streamsize
#include <limits>      // numeric_limits
#include <memory>      // unique_ptr, make_unique<>()
#include <string>      // string, getline()
#include <vector>
#include <locale>       // touuper(), locale()

#include "Domain/Library/Books.hpp"    // Include for now - will replace next increment
#include "Domain/Session/SessionHandler.hpp"
#include "Domain/Client/Client.hpp"   
#include "Domain/User/User.hpp"
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

        std::vector<TechnicalServices::Persistence::Client> ClientsFromDB = _persistentData.ShowAllClients();
        std::vector<TechnicalServices::Persistence::User> UsersFromDB = _persistentData.ShowAllUsers();
        std::vector<TechnicalServices::Persistence::UserCredentials> UserFilesFromDB = _persistentData.ShowAllUserProfiles();


        // 2) Present login screen to user and get username, password, and valid role
        Domain::Session::UserCredentials credentials = { "", "", {""}, 1 };// ensures roles[0] exists
        Domain::Client::Client Client = { "", 0 };// ensures roles[0] exists

        auto& selectedRole = credentials.roles[0];     // convenience alias


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
            //_logger << "Login failure for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";
            //_logger << "Login failure for \"" + credentials.userName + "\" as a user. ";    //+ "\"";

        } while (true);


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
            /*if( selectedCommand == "Checkout Book" )
            {
              std::vector<std::string> parameters( 3 );

              std::cout << " Enter book's title:  ";  std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
              std::cout << " Enter book's author: ";  std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
              std::cout << " Enter book's ISBN:   ";  std::cin >> std::ws;  std::getline( std::cin, parameters[2] );

              auto results = sessionControl->executeCommand( selectedCommand, parameters );
              if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
            }*/

            if (selectedCommand == "Client Management")
            {

                std::unique_ptr<Domain::Client::ClientHandler> ClientHandler; // call clientdomain 
                ClientHandler = Domain::Client::ClientHandler::UseClientManagement(credentials);
                if (ClientHandler != nullptr) {
                    ClientsFromDB = ClientHandler->ClientsDB(ClientsFromDB);
                   
                    do
                    {
                        
                        auto        commands = ClientHandler->getCommands();
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
                        if (selectedCommand == "Add Client") {
                            int increment = ClientsFromDB.size() + 1;
                            ClientsFromDB = ClientHandler->addClient({ credentials.userName ,increment });


                        }
                        else if (selectedCommand == "View All Clients") {
                               
                            ClientHandler->ViewClients(ClientsFromDB);
                        }
                        else if (selectedCommand == "Update Client Profile") {
                            ClientHandler->ViewClients(ClientsFromDB);
                            char response;

                            int clientId;
                            std::cout << "Please choose Client Id: ";
                            std::cin >> clientId;
                            do
                            {
                                std::cout << "Do you want to continue Update Profile for Client with Id # " + std::to_string(clientId) + "? (Y/N/Q)";
                                std::cin >> response;
                                response = std::toupper(response, std::locale());
                            } while (response != 'Y' && response != 'Q');

                            if (response == 'Y') {
                                //TODO
                            }

                        }
                        else if (selectedCommand == "Link Product") {
                            //todo
                        }


                    } while (true);

                }

                else if (selectedCommand == "Another command") /* ... */ {}

                else sessionControl->executeCommand(selectedCommand, {});
            }

            else if (selectedCommand == "User Management")
            {
                std::unique_ptr<Domain::User::UserHandler> UserHandler; // call user domain 
                UserHandler = Domain::User::UserHandler::UseUserManagement(credentials);
                if (UserHandler != nullptr)
                {
                    UsersFromDB = UserHandler->UsersDB(UsersFromDB);
                    UserFilesFromDB = UserHandler->UsersPDB(UserFilesFromDB);

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
                                std::cout << i << " " << roleLegalValues[i] << std::endl;
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
                                UsersFromDB = std::any_cast<const std::vector<TechnicalServices::Persistence::User>&>(results);
                            }
                            auto newUser = UsersFromDB[UsersFromDB.size() - 1];
                            auto newUserProfile = UserFilesFromDB[UserFilesFromDB.size() - 1];
                            newUserProfile = { newUser.userName,  "123456", std::vector<std::string> {newUser.userRole}, 1 };    // also create an temporary user profile 
                            UserFilesFromDB.push_back(newUserProfile);
                        }

                        else if (selectedCommand == "View All Users") 
                        {

                            UserHandler->viewUsers(UsersFromDB);
                        }

                        else if (selectedCommand == "View All User Profiles")
                        {
                            UserHandler->viewUserProfiles(UserFilesFromDB);
                        }

                        else if (selectedCommand == "Update User Profile") 
                        {
                            UserHandler->viewUsers(UsersFromDB);
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

                            if (response == 'Y') {
                                //TODO
                            }

                        }



                    } while (true);

                }
            }

            _logger << "Ending session and terminating";
        } while (true);

    }
}
