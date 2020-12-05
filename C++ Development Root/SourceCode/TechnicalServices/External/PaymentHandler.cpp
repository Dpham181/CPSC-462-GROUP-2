// this one if u want to check condition like sesstion handler cpp

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>
#include <iomanip>     // setw()

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

                auto& persistentData = TechnicalServices::Persistence::PersistenceHandler::instance();
                std::vector<TechnicalServices::Persistence::PaymentOption>PayOps =  persistentData.ShowAllPaymentOption();
                   std::string selectedPaymethod;
                   unsigned    menuPaySelection;
                   do
                   {


                       for (unsigned i = 0; i != PayOps.size(); ++i) std::cout << std::setw(2) << i << " - " << PayOps[i].PaymentTypeName << '\n';

                       std::cout << "  action (0-" << PayOps.size() << "): ";
                       std::cin >> menuPaySelection;
                   } while (menuPaySelection > PayOps.size());

                
                   selectedPaymethod = PayOps[menuPaySelection].PaymentTypeName;
                if (selectedPaymethod == "Credit")
                {
                    return std::make_unique<TechnicalServices::External::CreditPayment>();
                }
                    
                if (selectedPaymethod == "Debit") {
                    
                    return std::make_unique<TechnicalServices::External::DebitPayment>(); 
                
                }
                if (selectedPaymethod == "GateWay") return std::make_unique<TechnicalServices::External::GatewayPayment>();
          

        }
    
    
} // namespace Domain::Session
