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
#include <vector>

namespace FG {


    class FunctionGraph {
        public:
            //--- Construction / Destruction
            FunctionGraph() {};
            virtual ~FunctionGraph() {};

            //--- Primary functionality
            virtual double evaluate() const=0;

            //--- Accessors and info
            const std::set<std::string> &get_dependency_set() const;
            bool depends_on(const std::string &var) const;

        protected:
            std::set<std::string> dependency_set;
            std::vector<std::shared_ptr<FunctionGraph>> args;

        private:
            
           
            
    };


    class ConstField : public FunctionGraph {
        public:
            ConstField(const double &val);
            double evaluate() const;
            ~ConstField() {};

        private:
            const double value;
    };

    class VarField : public FunctionGraph {
        public:
            VarField(const std::string &name, const double &init_val);
            void set(const double &val);
            double evaluate() const;
            ~VarField() {};

            const std::string var_name;

        private:
            double value;
    };

    class Sum : public FunctionGraph {
        public:
            Sum(std::shared_ptr<FunctionGraph> fg1, 
                std::shared_ptr<FunctionGraph> fg2);
           
            double evaluate() const;

             ~Sum() {};

        private:
           //const std::shared_ptr<FG::FunctionGraph> arg1;
           //const std::shared_ptr<FG::FunctionGraph> arg2;
    };

    class Product : public FunctionGraph {
        public:
            Product(const std::shared_ptr<FunctionGraph> fg1, 
                    const std::shared_ptr<FunctionGraph> fg2);
           
            double evaluate() const;

             ~Product() {};

        private:
           //const std::shared_ptr<FunctionGraph> arg1;
           //const std::shared_ptr<FunctionGraph> arg2;
    };



};