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
#include <map>
#include <stack>

namespace FG {


    class FunctionGraph {
        public:
            //--- Construction / Destruction
            FunctionGraph(const std::string &name_);
            virtual ~FunctionGraph() {};

            //--- Primary functionality
            virtual double evaluate() const=0;

            //--- Accessors and info
            const std::set<std::string> &get_dependency_set() const;
            bool depends_on(const std::string &var) const;
            bool assign_var(const std::string &name, double &val);
            const std::string &get_name() { return name; }

            void DFS();

            std::vector<std::unique_ptr<FunctionGraph>> args;

        protected:
            std::set<std::string> dependency_set;
            //std::vector<std::unique_ptr<FunctionGraph>> args;
            const std::string name;

        private:
            
           
            
    };


    class ConstField : public FunctionGraph {
        public:
            ConstField(const std::string &name, const double &val);
            double evaluate() const;
            ~ConstField() {};

        private:
            const double value;
    };

    class VarField : public FunctionGraph {
        public:
            VarField(const std::string &name_, 
                     const std::string &var_name_, 
                     const double &init_val_);
            void set(const double &val_);
            double &get() { return value; }
            double evaluate() const;
            ~VarField() {};

            const std::string var_name;

        protected:
            double value;
    };

    class Sum : public FunctionGraph {
        public:
            Sum(const std::string &name_,
                      std::unique_ptr<FunctionGraph> &&fg1_, 
                      std::unique_ptr<FunctionGraph> &&fg2_);
           
            double evaluate() const;

             ~Sum() {};

        private:
    };

    class Product : public FunctionGraph {
        public:
            Product(const std::string &name_,
                          std::unique_ptr<FunctionGraph> &&fg1_, 
                          std::unique_ptr<FunctionGraph> &&fg2_);
           
            double evaluate() const;

             ~Product() {};

        private:
    };

    class FunctionIter {
        public:
            FunctionIter(FunctionGraph *root_);
            FunctionGraph *next();
        private:
            //const std::unique_ptr<FunctionGraph> &root;
            FunctionGraph *root;
            std::stack<FunctionGraph*> rec_stack;
            FunctionGraph *cur_ptr;

    };



};