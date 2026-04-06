# Demo Generative Coding Agent Rules

## Documentation
- All header files must have a file-level comment at the top of the file describing the purpose of the file and any important details (before any include guards or #includes).
- All methods must be documented with Doxygen-style comments with the following sections: @brief, @param, @return, and @details (if needed).
- @param section must include the direction of the parameter (in, out, inout) using [in], [out], or [in,out] tags.

## Semantics
- Use spaces for indentation, with a width of 4 spaces per indentation level.
- Do not use `using namespace` directives anywhere
- All variables and functions must use snake_case naming convention (e.g. `my_variable`, `my_function()`).
- Upper camel case for class and struct names (e.g. `MyClass`)
- Interfaces must be prefixed with "I" (e.g. `IMyInterface`).
- Interfaces must be pure abstract classes (i.e. all methods are pure virtual).
- All header files must have include guards using #pragma once. 
- Always use `this`-> to access member variables and functions within class methods.
- Do not use `_` prefix or suffix for private member variables (e.g. `this->_my_private_variable`).
- One class per file, and the file name must match the class name but in snake_case (e.g. `MyClass` -> `my_class.hpp`).
- Use `constexpr` for compile-time constants and `const` for runtime constants.
- Enums must be scoped (i.e. `enum class`).
- Enums must use upper camel case for enum names and upper snake case for enum values (e.g. `enum class MyEnum { VALUE_ONE, VALUE_TWO }`) and have a final enumerator named `COUNT` that represents the number of valid enum values (e.g. `VALUE_ONE`, `VALUE_TWO`, `COUNT`).

## Implementation Constraints
- Use float instead of double for all floating-point calculations. All floating-point literals must have an 'f' suffix (e.g. `3.14f`).
- Prefer object composition over inheritance.
- Functions must have a single point of return.
- Prefer dependency injection.
- Do not use dynamic memory allocation.
- Do not use the C++ standard library (`std::`) with the exception of `std::array` and `std::span` if needed for fixed-size collections.
- Do not use C++ exceptions (`throw`, `try`, `catch`).
- Do not use Standard Template Library (STL).
- Do not use RTTI (Run-Time Type Information).
- All domain logic code must use interfaces to hardware abstractions (e.g. GPIO, ADC, etc.) rather than direct hardware access.
- In header files, prefer forward declarations over #include for types used only by pointer or reference. Only include a header when the full type definition is required (by-value members, base classes, or inline method bodies).
