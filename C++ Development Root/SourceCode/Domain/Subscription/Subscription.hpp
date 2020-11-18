#pragma once
#include <string>
#include <memory>
#include <string>
#include <vector>

#include "Domain/Subscription/SubscriptionHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::Subscription
{
 
  class SubscriptionDomain : public SubscriptionHandler
  {
    public:
        
        SubscriptionDomain(const std::string& description, const UserCredentials& user);

      //  Operations menu
       std::vector<std::string> getCommandsSubscription() override;    // retrieves the list of actions (commands)
       std::any                 executeCommandSubscription(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

      // Operations
        SubscriptionStatus viewSubscriptionStatus() override;
        PaymentOption selectSubscription(const Subcripstion SelectedId) override;
        std::string completePayment() override;

     ~SubscriptionDomain()  noexcept override = 0;

  protected:
  public:  
      using DispatchSubscriptionDomain = std::map<std::string, std::any(*)(Domain::Subscription::SubscriptionDomain&, const std::vector<std::string>&)>;

      friend class Policy;

      // Instance Attributes
      std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;
      std::string     const                             _name = "Undefined";
      UserCredentials const                             _Usedby;
      DispatchSubscriptionDomain                                    _commandDispatch;
      // Product arrtibbutes 

  private:
      
  }; // class Product


  inline SubscriptionDomain::~SubscriptionDomain() noexcept
  {
      _logger << "Session \"" + _name + "\" shutdown successfully";

  }
 
  struct SubcriptionsInUse : SubscriptionDomain { SubcriptionsInUse(const UserCredentials& user); };

 

}  // namespace Domain::Product
