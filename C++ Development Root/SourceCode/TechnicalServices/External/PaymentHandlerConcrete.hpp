#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>   // domain_error, runtime_error
#include "TechnicalServices/External/PaymentHandlerInterface.hpp"
#include "TechnicalServices/External/PaymentMethod.hpp"

namespace TechnicalServices::External
{
  


  struct CreditPayment : PaymentHandlerInterface { 
  
	 
	  std::unique_ptr <Payment> PayMethod(std::string  &PaymentType) override;
	  
  };



 struct DebitPayment : PaymentHandlerInterface { 
	 std::unique_ptr <Payment> PayMethod(std::string& PaymentType) override; };




 struct GatewayPayment : PaymentHandlerInterface {
	 std::unique_ptr <Payment> PayMethod(std::string& PaymentType) override;
 };



} // namespace TechnicalServices::External

