#pragma once
#include <utility>
#include <memory>


template <typename Sgn>
class MyFunction;

template <typename Ret, typename... Args>
class MyFunction<Ret(Args...)>
{
private:
    struct FunctionBase
    {
        virtual ~FunctionBase() = default;
        virtual Ret invoke(Args&&... args) = 0;
        virtual std::unique_ptr<FunctionBase> clone() const = 0;
    };

    template <typename F>
    struct FunctionHolder : public FunctionBase
    {
        F function;

        template <typename Func>
        FunctionHolder(Func&& f) : function(std::forward<Func>(f)) {}

      Ret invoke(Args&&... args) override
        {
            return function(std::forward<Args>(args)...);
        }

        std::unique_ptr<FunctionBase> clone() const override
        {
            //return std::unique_ptr<FunctionBase>(new FunctionHolder<F>(function));
            return std::make_unique<FunctionHolder<F>>(function);
        }
    };

    std::unique_ptr<FunctionBase> function_holder;

public:
    // Constructors
    template <typename F>
    MyFunction(F f) : function_holder(new FunctionHolder<F>(f)) {}
    //MyFunction(F&& f) : function_holder(new FunctionHolder<std::decay_t<F>>(std::forward<F>(f))) {}
    // PROBLEM OVDJE JE ŠTO PREDLOŽAK KONSTRUKTORA UNIVERZALNOM REFERENCOM POSTAJE BOLJI KANDIDAT
    // OD KONSTRUKTORA KOPIJE I KONSTRUKTOR KOPIJE SE NIKAD NE POZIVA. ZATO KOPIRANJE NIJE RADILO.

    // Copy constructor
    MyFunction(const MyFunction& other) : function_holder(other.function_holder ? other.function_holder->clone() : nullptr){}

    // Copy assignment operator
    MyFunction& operator=(const MyFunction& other)
    {
        if (this != &other)
            function_holder = (other.function_holder ? other.function_holder->clone() : nullptr);
        return *this;
    }

    // Move constructor
    MyFunction(MyFunction&& other) noexcept = default;

    // Move assignment operator
    MyFunction& operator=(MyFunction&& other) noexcept = default;

    // Function call operator
    Ret operator()(Args... args) const
    {
        if (function_holder)
            return function_holder->invoke(std::forward<Args>(args)...);
        else
            throw std::exception();
    }

    // Destructor
    //~MyFunction() = default;
};
