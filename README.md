# rose.parser

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

### Example:

See bin folder for test cases and example output.

