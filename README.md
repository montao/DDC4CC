# DDC4CC
## PoC for diverse-double compiling for cryptocurrency

## What is it?
The purpose of this repository is to provide a proof-of-concept for the trusting trust attack against a cryptocurrency application. It also includes a method to detect to attack by use of diverse-double-compiling. The goal has been to make the example self-contained and as easy as possible.  

## Why did you do this?  
I (Niklas Rosencrantz) chose this project for my degree project at the university.  

## How does it work?  
A C compiler (TCC) is c ompromised to replace code of itself, when compiling itself, and similarly will replace code of a cryptocurrency application when compiling that, according to the trusting trust attack as originally described by Ken Thompson. 

## How do I run it myself?
It will only work with Linux (Ubuntu).  
Locally, first download and install makoe (the cryptocurrency app)
```
git clone https://github.com/chjj/mako.git
git clone https://github.com/chjj/mako.git
cd mako
chmod +x automgen.sh
./autogen.sh
./configure
make
```

clone the repository  
`git clone https://github.com/montao/DDC4CC/
