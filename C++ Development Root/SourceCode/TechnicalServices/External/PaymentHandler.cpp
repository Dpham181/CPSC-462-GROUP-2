// this one if u want to check condition like sesstion handler cpp

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "TechnicalServices/External/PaymentHandlerConcrete.hpp"
#include "TechnicalServices/External/PaymentHandlerInterface.hpp"
#include "TechnicalServices/External/Payment.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace TechnicalServices::External
{
    PaymentHandlerInterface::~PaymentHandlerInterface() noexcept = default;




        // returns a specialized object specific to the specified role
        std::unique_ptr< PaymentHandlerInterface > PaymentHandlerInterface::PaySystemFactory()
        {
             std::string Paytype = "";
            
            if (Paytype == "Credit" ) return std::make_unique<TechnicalServices::External::CreditPayment>();
            if (Paytype == "Debit") return std::make_unique<TechnicalServices::External::DebitPayment>();
            if (Paytype == "GateWay") return std::make_unique<TechnicalServices::External::GatewayPayment>();
        }
    
    
} // namespace Domain::Session
