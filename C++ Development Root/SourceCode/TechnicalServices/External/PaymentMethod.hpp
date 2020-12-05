#pragma once
#include <string>
#include <memory>
#include <string>
#include <vector>

#include "TechnicalServices/External/Payment.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace TechnicalServices::External
{
  /// <summary>
  /// credit payable 
  /// </summary>
  class Credit : public Payment
  {
  public:

	  Credit(std::string&paymentType) ;



	  void Requestpayinfor() override ;


	  ~Credit()  override;
  protected:
  public:
	  std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
	  TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;
  private:
	  long unsigned  _CardNumber = 0;
	  int _CVS = 0; 
	
  };

  class Debit : public Payment
  {
  public:

	  Debit(std::string& paymentType);



	  void Requestpayinfor() override;


	  ~Debit()  override;
  protected:
  public:
	  std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
	  TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;
  private:
	  long unsigned  _CardNumber = 0;
	  int _CVS = 0;

  };
  
  class GateWay : public Payment
  {
  public:

	  GateWay(std::string& paymentType);



	  void Requestpayinfor() override;


	  ~GateWay()  override;
  protected:
  public:
	  std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
	  TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;
  private:
	  long unsigned  _CardNumber = 0;
	  int _CVS = 0;

  };
  
}  // namespace TechnicalServices::External
