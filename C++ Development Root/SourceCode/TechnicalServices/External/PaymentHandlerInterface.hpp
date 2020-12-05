#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>   // domain_error, runtime_error
#include "TechnicalServices/External/Payment.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace TechnicalServices::External
{
  
    using TechnicalServices::Persistence::PaymentOption;

  class PaymentHandlerInterface
  {
    public:

     static std::unique_ptr <PaymentHandlerInterface> PaySystemFactory();

     virtual std::unique_ptr <Payment> PayMethod( std::string & PaymentType) =0;    //choose the type of payment method.
   

      virtual ~PaymentHandlerInterface() noexcept = 0;


      protected :
        // Copy assignment operators, protected to prevent mix derived-type assignments
          PaymentHandlerInterface&
        operator=( const PaymentHandlerInterface& rhs ) = default;                // copy assignment
          PaymentHandlerInterface& operator=(PaymentHandlerInterface&& rhs ) = default;    // move assignment
 
  };    // class PaymentHandler


} // namespace TechnicalServices::External

