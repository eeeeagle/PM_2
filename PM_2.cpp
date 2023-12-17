#include <iostream>
#include <string>
#include <stack>

double perform_operation(const double& first, const double& second, const char& operation)
{
    std::cout << "Calculate: " << first << ' ' << operation << ' ' << second << std::endl;

    switch (operation)
    {
    case '+':
        return first + second;
    case '-':
        return first - second;
    case '*':
        return first * second;
    case '/':
        return first / second;
    default:
        throw std::logic_error("Invalid operaion");
    }
}

bool is_double(const std::string& str)
{
    bool result = true;
    try
    {
        double d = std::stod(str);
    }
    catch (const std::invalid_argument& err)
    {
        result = false;
    }
    catch (const std::out_of_range& err)
    {
        result = false;
    }
    return result;
}

bool is_operation(const char& in)
{
    return (in == '+' || in == '-' || in == '*' || in == '/');
}

int main()
{
    std::cout << "Enter value, operation or type \'q\' to exit" << std::endl << std::endl;
    std::string input;
    std::stack<double> values;
    while (true)
    {
        try
        {
            
            getline(std::cin, input);

            if (input == "q" || input == "Q" || input == "exit")
            {
                if (!values.empty())
                    std::cout << "Result = " << values.top() << std::endl;
                return 0;
            }

            if (is_double(input))
            {
                values.push(std::stod(input));
                std::cout << "Added to values stack: " << values.top() << std::endl;
            }
            else if (is_operation(input[0]) && input.size() == 1)
            {
                char operand = input[0];
                std::cout << "Added operation: " << operand << std::endl;

                if (values.size() < 2)
                    throw std::logic_error("Stack of values contains less than 2 values");

                double second = values.top();
                values.pop();

                double first = values.top();
                values.pop();

                double res = perform_operation(first, second, operand);
                values.push(res);
                std::cout << "Added to values stack: " << values.top() << std::endl;
            }
            else
                throw std::invalid_argument("Invalid input. Try again.");
        }
        catch (std::invalid_argument& err)
        {
            std::cout << "ERROR: " << err.what() << std::endl;
        }
        catch (std::logic_error& err)
        {
            std::cout << "ERROR: " << err.what() << std::endl;
        }
    }
}