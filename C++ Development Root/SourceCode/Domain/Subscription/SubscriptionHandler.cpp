// this one if u want to check condition like sesstion handler cpp

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "Domain/Subscription/Subscription.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace Domain::Subscription
{
    SubscriptionHandler::~SubscriptionHandler() noexcept = default;

    std::unique_ptr<SubscriptionHandler> SubscriptionHandler::MaintainSubscription(const UserCredentials& user)
    {
        auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
       SubscriptionStatus SubscriptionStatusDB = persistentData.StacticSubscriptionSatus();
        if (SubscriptionStatusDB.SubsctiptionStatusId != NULL) return std::make_unique<Domain::Subscription::SubcriptionsInUse>(user);

        return nullptr;
    }


  
} // namespace Domain::Session
