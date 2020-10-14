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
        // Just as a smart defensive strategy, one should verify this role is one of the roles in the DB's legal value list.  I'll come
        // back to that

        // This is a good example of a Factory - the function takes the "order" (role) and builds the "product" (session) to fulfill the
        // order. This, however, still leaks knowledge of the kinds of sessions to the client, after all the client needs to specify
        // with role.

        // ToDo: Make this an Abstract Factory by:
        //  1) removing the parameter from the function's signature :  std::unique_ptr<SessionHandler>  SessionHandler::createSession();
        //  2) read the role from a proprieties files or (preferred) look up the role in the persistent data

        // Authenticate the requester
        try
        {
            auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
           
        }
        catch (const TechnicalServices::Persistence::PersistenceHandler::NoSuchUser&) {}  // Catch and ignore this anticipated condition

        return nullptr;
    }
} // namespace Domain::Session
