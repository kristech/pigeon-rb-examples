# Library for Pigeon computers
 
To build library:
```
git clone https://github.com/kristech/pigeon-rb-examples.git
cd pigeon-rb-examples/C/library/
chmod u+x makelib
./makelib build
```

To build examples:
```
cd examples
gcc example-rb100.c -o example-rb100 -lpigeonRB -lwiringPi
gcc example-rb300.c -o example-rb300 -lpigeonRB -lwiringPi
```

To run examples:
```
./example-rb100
./example-rb300
```