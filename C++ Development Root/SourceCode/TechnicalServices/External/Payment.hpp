#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>   // domain_error, runtime_error
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace TechnicalServices::External
{
    using TechnicalServices::Persistence::PaymentOption;
   

  // Client Package within the Domain Layer Abstract class
  class Payment
  {
    public:
        Payment( std::string &paymentType);
        
      //  Operations menu
     virtual void Requestpayinfor() =0;    // pay request information from end user.
   

      virtual ~Payment() noexcept = 0;

      public:
          std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
          TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;

      protected :
          std::string _paymentType;
        // Copy assignment operators, protected to prevent mix derived-type assignments
          Payment&
        operator=( const Payment& rhs ) = default;                // copy assignment
          Payment& operator=(Payment&& rhs ) = default;    // move assignment
 
  };    // class PaymentHandler


} // namespace TechnicalServices::External

