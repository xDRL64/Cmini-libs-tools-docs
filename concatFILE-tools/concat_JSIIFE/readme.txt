"JSIIFE" (JavaScript Immediately Invoked Function Expression)

Concat in (()=>{ ... })();

    concatJSIIFE output file file file etc..

        output : name of new output file

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