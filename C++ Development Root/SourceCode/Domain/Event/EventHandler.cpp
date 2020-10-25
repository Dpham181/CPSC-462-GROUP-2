// this one if u want to check condition like sesstion handler cpp

#include "Domain/Session/SessionHandler.hpp"

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "Domain/Event/Event.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace Domain::Event
{
    EventHandler::~EventHandler() noexcept = default;



    // returns a specialized object specific to the specified role
    std::unique_ptr<EventHandler> EventHandler::UseEventManagement(const UserCredentials& user)
    {
        auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
        UserCredentials credentialsFromDB = persistentData.findCredentialsByName(user.userName);
        if (credentialsFromDB.roles[0] == "Assistant") return std::make_unique<Domain::Event::EventManagement>(user);

        return nullptr;
    }


} // namespace Domain::Session
