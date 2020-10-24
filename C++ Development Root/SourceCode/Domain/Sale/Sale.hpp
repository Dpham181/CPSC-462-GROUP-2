#pragma once
#include <string>
#include <memory>
#include <string>
#include <vector>

#include "Domain/Sale/SaleHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::Sale
{
 
  class SaleDomain : public SaleHandler
  {
    public:
        
        SaleDomain(const std::string& description, const UserCredentials& user);

      //  Operations menu
       std::vector<std::string> getCommandsSale() override;    // retrieves the list of actions (commands)
       std::any                 executeCommandSale(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

      // Operations
       Sale             MakeSale(const int UserId, const int ClientId, const std::vector<int> purchasedProduct) override;
       Commission       GenerateCommission(const int CommissionId) override;
        void             ViewSale(const Sale &sale) override;
      ~SaleDomain() noexcept override = 0 ;
  protected:
  public:  
      using DispatchTable = std::map<std::string, std::any(*)(Domain::Sale::SaleDomain&, const std::vector<std::string>&)>;

      friend class Policy;

      // Instance Attributes
      std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;
      std::string     const                             _name = "Undefined";
      UserCredentials const                             _Usedby;
      DispatchTable                                    _commandDispatch;
      
      // Product arrtibbutes 
      Product                                            _Product;
      std::vector<Product>                               _ProductDb;
      // sale arrts
      Sale                                               _OneSale;
      std::vector<Sale>                                  _ListOfSale;
      Commission                                         _OneComission;
      std::vector<Commission>                            _ListofCommissions;


  private:
      
  }; // class Product


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline SaleDomain::~SaleDomain() noexcept
  {
      _logger << "Session \"" + _name + "\" shutdown successfully";

  }
  struct SaleManagement : SaleDomain { SaleManagement(const UserCredentials& user); };

 

}  // namespace Domain::Client
