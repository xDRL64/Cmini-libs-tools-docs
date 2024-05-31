"JSIIFE" (JavaScript Immediately Invoked Function Expression)

Concat in (()=>{ ... })();

    concatJSIIFE output_name file file file etc..

        output_name : name of new output file

        file : name of input file


Example :

    input file :

        |const a = ()=>{
        |    // code ...
        |};

    output file :

        |(()=>{
        |const a = ()=>{
        |    // code ...
        |};
        |})();