1. Anthony Chen, Yunlai Chen

2. output:
        Studio6 % ./studio6
        Mon Tue Wed Thu Fri Sat Sun 
        Low Med High 


3. output is the same as in question 2, 
   The code we use to replace the using namespace std:
        using std::cout;
        using std::endl;


4. After wrapping the enum weekday and pressure in enumerations, we got compliation error show in part as following:
    ./Studio6.h:23:16: note: 'enumerations::Pressure' declared here
        enum class Pressure
                ^
    main.cpp:16:25: error: use of undeclared identifier 'Pressure'; did you mean 'enumerations::Pressure'?
        Pressure pressure = Pressure::lo;
                            ^~~~~~~~
                            enumerations::Pressure

    The complier suggest that should scoping into the enumerations namespace to access the Pressure and weekday enum class


5.
    (1)
    using std::cout;        // already there before 5th question
    using std::endl;        // already there before 5th question
    using namespace enumerations;


    (2)
    because the Weekday and Pressure are defined in the same file, so the complier can find the definition of the Weekday and Pressure in the same file.

6. 
    Replaced the using namespace enumerations; with:
        using enumerations::Pressure;
        using enumerations::Weekday;

    
