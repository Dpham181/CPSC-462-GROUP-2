// this one if u want to check condition like sesstion handler cpp

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
        std::unique_ptr<ClientHandler> ClientHandler::UseClientManagement(const UserCredentials & user)
        {

            try {
                auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
                UserCredentials credentialsFromDB = persistentData.findCredentialsByName(user.userName);
                if (credentialsFromDB.status == 1) return std::make_unique<Domain::Client::ClientManagement>(user);

                return nullptr;
            }
            catch (const TechnicalServices::Persistence::PersistenceHandler::NoSuchUser&) {}

        }
    
    
} // namespace Domain::Session
