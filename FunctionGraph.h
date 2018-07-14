//+----------------------------------------------------------
//|
//| FunctionGraph.h
//|
//| Representation of function as a computational graph
//| Evaluates functions and their derivatives
//|
//|
//+----------------------------------------------------------


#include <memory>
#include <string>
#include <set>

namespace FG {


    class FunctionGraph {
        public:
            //--- Construction / Destruction
            FunctionGraph() {};
            virtual ~FunctionGraph() {};

            //--- Primary functionality
            virtual double evaluate()=0;

            //--- Accessors and info
            const std::set<std::string> &get_dependency_set();
            bool depends_on(const std::string &var);

        protected:
            std::set<std::string> dependency_set;

        private:
            
           
            
    };


    class ConstField : public FunctionGraph {
        public:
            ConstField(const double &val);
            double evaluate();
            ~ConstField() {};

        private:
            const double value;
    };

    class VarField : public FunctionGraph {
        public:
            VarField(const std::string &name, const double &init_val);
            void set(const double &val);
            double evaluate();
            ~VarField() {};

            const std::string var_name;

        private:
            double value;
    };

    class Sum : public FunctionGraph {
        public:
            Sum(std::shared_ptr<FG::FunctionGraph> fg1, 
                std::shared_ptr<FG::FunctionGraph> fg2);
           
            double evaluate();

             ~Sum() {};

        private:
           
           std::shared_ptr<FG::FunctionGraph> arg1;
           std::shared_ptr<FG::FunctionGraph> arg2;
    };

    class Product : public FunctionGraph {
        public:
            Product(std::shared_ptr<FG::FunctionGraph> fg1, 
                std::shared_ptr<FG::FunctionGraph> fg2);
           
            double evaluate();

             ~Product() {};

        private:
        
           std::shared_ptr<FG::FunctionGraph> arg1;
           std::shared_ptr<FG::FunctionGraph> arg2;
    };



};