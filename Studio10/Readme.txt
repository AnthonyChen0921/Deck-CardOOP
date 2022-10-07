1.  
    Anthony Chen, Yunlai Chen


2.  Declaration of the class:

    class Foo {
    private:
        std::string name;
    };


3.  Output:
        Copy Constructor Called
        this: 0x16ae97348
        other: 0x16ae97360

4.  Output:
        Foo Object at: 0x16f90f360 name: hello
        Copy Constructor Called
        this: 0x16f90f320
        other: 0x16f90f360
        other.name: hello
        Foo Object at: 0x16f90f320 name: hello destroyed
        Foo Object at: 0x16f90f360 name: hello destroyed


5.  Output:
        Foo Object at: 0x16b1db360 name: foo1
        Foo Object at: 0x16b1db320 name: foo2
        Foo Object at: 0x16b1db2f0 name: foo3
        Assignment Operator Called
        this: 0x16b1db320
        this.name: foo2
        other: 0x16b1db2f0
        other.name: foo3
        Assignment Operator Called
        this: 0x16b1db360
        this.name: foo1
        other: 0x16b1db320
        other.name: foo3
        Foo Object at: 0x16b1db2f0 name: foo3 destroyed
        Foo Object at: 0x16b1db320 name: foo3 destroyed
        Foo Object at: 0x16b1db360 name: foo3 destroyed




6.  Output:
        Foo Object at: 0x139e067d0 name: hello
        Foo Object at: 0x139e067d0 name: hello destroyed





7.  Output:
        Foo Object at: 0x122e067d0 name: hello
        Foo Object at: 0x122e067d0 name: hello
        Foo Object at: 0x122e067d0 name: hello destroyed


8.  Output:
        Foo Object at: 0x153e067d0 name: hello
        Foo Object at: 0x153e067d0 name: hello
        Foo Object at: 0x153e067d0 name: hello
        Foo Object at: 0x153e067d0 name: hello destroyed