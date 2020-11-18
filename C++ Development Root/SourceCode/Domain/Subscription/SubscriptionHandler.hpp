#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>   // domain_error, runtime_error
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::Subscription
{
   using TechnicalServices::Persistence::UserCredentials;
   using TechnicalServices::Persistence::Subcripstion;
   using TechnicalServices::Persistence::PaymentOption;
   using TechnicalServices::Persistence::SubscriptionStatus;
   using TechnicalServices::Persistence::Paid;

  // Product Package within the Domain Layer Abstract class
  class SubscriptionHandler
  {
    public:
     
     static std::unique_ptr<SubscriptionHandler> MaintainSubscription( const UserCredentials& User);

      //  Operations menu
     virtual std::vector<std::string> getCommandsSubscription() =0;    // retrieves the list of actions (commands)
     virtual std::any                executeCommandSubscription(const std::string& command, const std::vector<std::string>& args) =0;    // executes one of the actions retrieved



   // Operations of Maintain Subscription
     // default operations
     virtual SubscriptionStatus viewSubscriptionStatus() = 0 ;
     virtual PaymentOption selectSubscription(const Subcripstion & SelectedId) = 0;
     virtual std::string completePayment() = 0; 
     virtual bool validationPayment( const std::string CCnumber, const int CVCnumber) = 0;
     virtual ~SubscriptionHandler() noexcept = 0;
      protected:
        // Copy assignment operators, protected to prevent mix derived-type assignments
          SubscriptionHandler&
        operator=( const SubscriptionHandler& rhs ) = default;                // copy assignment
          SubscriptionHandler& operator=(SubscriptionHandler&& rhs ) = default;    // move assignment
 
  };    // class SubscriptionHandler


} // namespace Domain:: Subscription
