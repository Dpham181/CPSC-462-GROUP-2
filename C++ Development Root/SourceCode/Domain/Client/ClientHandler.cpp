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
    std::unique_ptr<ClientHandler> ClientHandler::createClient(const Client& client)
    {
        if (client.clientid >0 && client.creator !="") {
            return std::make_unique<Domain::Client::ClientManagement>(client);
        }

        return nullptr;
    }
} // namespace Domain::Session
