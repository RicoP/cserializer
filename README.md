# rose.parser
[![Windows Build](https://github.com/RicoP/rose.parser/actions/workflows/windows.yml/badge.svg)](https://github.com/RicoP/rose.parser/actions/workflows/windows.yml)

![preview](.github/readme/header.png)

```
NAME
       rose.parser - generate serialization code for simple c headers.

SYNOPSIS
       rose.parser [OPTION]

DESCRIPTION
       -H, --help
              Show this help.

       -I, --includes
              Followed by a list of headers files, that should be parsed.

       -O, --output
              The output file. [default: stdout]

       -J, --json
              A optional JSON file containing meta info of the header files.
              
       -V, --verbose
              Verbose output.

AUTHOR
       Written by Rico Possienka.
```

### How To Build (Windows)
```
cd externals
clone.bat
cd ..
create_solution.bat
build_solution.bat
```

You must include https://github.com/RicoP/premake-comppp/tree/main/include/serializer 

### Description:

Data-Components are described as regular C++ structs, annotated with a custom meta language. Attributes are enclosed with a "$" symbol which will be translated into whitespace by the preprocessor. Example:

```C++
//game.h
struct Player {
       $(synonym: m_name)
       rstring name;

       int energy = 100;

       Transform transform;
};

struct Enemy {
       int energy = 100;

       Transform transform;
};

struct World {
       Player player;
       std::vector<Enemy> enemies;
};
```

This will generate a file called "game.gen.h" which will contain the following functions:

```
void serialize(Player &, ISerializer &);
void deserialize(Player &, IDeserializer &);
rose::hash_value hash(const Player &);

void serialize(Enemy &, ISerializer &);
void deserialize(Enemy &, IDeserializer &);
rose::hash_value hash(const Enemy &);

void serialize(World &, ISerializer &);
void deserialize(World &, IDeserializer &);
rose::hash_value hash(const World &);
```
