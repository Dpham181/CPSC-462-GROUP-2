// this one if u want to check condition like sesstion handler cpp

#include "Domain/Session/SessionHandler.hpp"

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "Domain/Client/Client.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace Domain::Client
{
    ClientHandler::~ClientHandler() noexcept = default;




    // returns a specialized object specific to the specified role
    std::unique_ptr<ClientHandler> ClientHandler::UseClientManagement(const UserCredentials& user)
    {
        auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
        UserCredentials credentialsFromDB = persistentData.findCredentialsByName(user.userName);
        if (credentialsFromDB.roles[0] == "Salesperson") return std::make_unique<Domain::Client::ClientManagement>(user);

        return nullptr;
    }
} // namespace Domain::Session
