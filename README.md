# MySQLHello

Starter code for a modern c++ sql application.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

### Prerequisites

* ISO C++17 Compiler (tested with clang 6.0)

To obtain clang 6.0:

Getting clang 6.0 for OSX.

$ brew install --with-toolchain llvm

It may be worth running the following command first if you already have an existing homebrew installation:

$ brew info llvm
Seeing not seeing llvm v6.0 listed? I recommend updating homebrew

To update homebrew, simply run:

$ brew update
$ brew upgrade

$ brew info llvm will show path so that you can put clang 6.0 at the front of the search path

Installing on Ubuntu

Please follow tutorial here (https://www.linuxhelp.com/how-to-install-llvm-6-on-ubuntu-17-04/).  
Be sure to update your path to find clang.

The example itself runs against a table created like so:

```
CREATE TABLE {tablename} ( id smallint unsigned not null auto_increment, name varchar(20) not null, constraint pk_example primary key (id) );
```

With rows inserted like so:

```
INSERT INTO example ( id, name ) VALUES ( null, 'Sample data' );
```

### Installing

If you are using visual code, there is visual code configuration in the workspace, just open MySQLHello.code-workspace. You may need to change the path of the compiler in c_cpp_properties.json depending
on where you installed clang 6.

You may need to change includedirs and libdirs in premake5.lua depending on where the mysql development
libraries were installed.

If you are using the command line to invoke make just cd to the project directory and run:

```
make
```

End with an example of getting some data out of the system or using it for a little demo

Output will resemble (when run against the ubiqutous Shapes demo)

    ...
    BLUE               174               198                30                 0                 0
    ...

## Built With

* [args](https://github.com/Taywee/args) - The single header modern c++ arg parsing library

## Authors

* **Rennie Allen** - *Initial work* 

