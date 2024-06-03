Replace only one occurence by line in file.

    It creates a new file containing replacements.

    Regex groups are not supported for catching.

    Regex groups allowed to be more precise.

    Using :

        replace1BYLINE output input regex replacement bufferSize

            output : name of new output file (no confirmation on existing file)
                The file which will contain modifications.

            input : name of input file
                The base file to parse lines and to replace occurences.

            regex : regex patern for replacing
                The regex that expects to work on each line of a file.
                Can use ^ and $ in regex syntax.
                Better always to define this arg with double quote ""

            replacement : string to put as replacement on regex matching
                The string data that can be shorter or longer than the replaced data.
                Also better to define this arg with double quote ""
                You can simply remove occurence by giving an empty string "" as replacement arg

            bufferSize : line buffer base size (units : byte)
                The size of buffer to store line while replacing process.
                
                By default is 1024 bytes, and the minimum is restric to 1024.
                Optional argument, define it to increase value if
                your input file has lines longer than 1024 characters by line.

                If a line in input file is bigger than buffer, it should break line
                and we could have 2 mojor problems :

                    1. if it breaks in middle occurence, it will not be replaced.
                    2. end of 1st part and start of 2nd part of broken line could match with ^ and $

    Example :

        Input file :

            |const function_A = ()=>{
            |    
            |};
            |
            |const function_B = ()=>{
            |    
            |   const function_C = ()=>{
            |
            |   };
            |};

        Command :

            replace1BYLINE output.js input.js "^const" "let"

        Output file :

            |let function_A = ()=>{
            |    
            |};
            |
            |let function_B = ()=>{
            |    
            |   const function_C = ()=>{
            |
            |   };
            |};
