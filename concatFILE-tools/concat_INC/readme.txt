Concat in template (main) file by replacing a marker

    Set the template's marker by editing the regexp in :

        marker.regexp.txt

    Place marker.regexp.txt in same folder than concatINC executable app.

        otherwise the default regexp is :

            "(\\s*)(;//CONCAT_HERE)"

        and the default maker is :

            ;//CONCAT_HERE

        - read marker.regexp.readme.txt for more info.

    concatINC output template file file file etc..

        output : name of new output file

        template : name of template file

        file : name of input file


Example :

    marker.regexp.txt :

        ^()(\/\*\s*concat input file contents here\s*\*\/)

        - to match with :

            /* concat input file contents here */

    template.js :

        |const app = (()=>{
        |
        |	/* concat input file contents here */
        |
        |	return app;
        |})();

    command :

        concatINC output.js template.js file_A.js file_B.js etc..

    output.js :

        |const app = (()=>{
        |
        |	const a = ()=>{
        |		// code (file_A.js)
        |	};
        |	const b = ()=>{
        |		// code (file_B.js)
        |	};
        |
        |	return app;
        |})();