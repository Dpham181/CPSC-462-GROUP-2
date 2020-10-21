#pragma once
#include <string>
#include <memory>
#include <string>
#include <vector>

#include "Domain/Product/ProductHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::Product
{
 
  class ProductDomain : public ProductHandler
  {
    public:
        
        ProductDomain(const std::string& description, const UserCredentials& user);

      //  Operations menu
       std::vector<std::string> getCommandsProduct() override;    // retrieves the list of actions (commands)
       std::any                 executeCommandProduct(const std::string& command, const std::vector<std::string>& args) override;    // executes one of the actions retrieved

      // Operations
        void   view() override;
        Product   add(const int ProductId, const std::string ProductName, const int Price) override;
        std::vector<Product>   save(const Product & Product) override;

        std::vector<Product>   del(const int ProductId) override;
        std::vector<Product>   modify(const int CurrentProduct, const std::string ProductName, const int Price) override;

      ~ProductDomain() noexcept override = 0 ;
  protected:
  public:  
      using DispatchTable = std::map<std::string, std::any(*)(Domain::Product::ProductDomain&, const std::vector<std::string>&)>;

      friend class Policy;

      // Instance Attributes
      std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
      TechnicalServices::Logging::LoggerHandler& _logger = *_loggerPtr;
      std::string     const                             _name = "Undefined";
      UserCredentials const                             _Usedby;
      DispatchTable                                    _commandDispatch;
      // Product arrtibbutes 
      Product                                         _Product;
      std::vector<Product>                               _ProductDb;

  private:
      
  }; // class Product


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ProductDomain::~ProductDomain() noexcept
  {
      _logger << "Session \"" + _name + "\" shutdown successfully";

  }
  struct ProductManagement : ProductDomain { ProductManagement(const UserCredentials& user); };

 

}  // namespace Domain::Client
