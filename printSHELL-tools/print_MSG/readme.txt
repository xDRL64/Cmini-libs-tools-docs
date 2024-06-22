Simple printf of string with optional font color and background color

    printMSG string ?color1 ?color2

        string : text to display

        color1 : optional color arg (see below)

        color2 : optional color arg (see below)

    color args :

        Specify one arg for font color (fg) and one arg for background color (bg).
        Args order does not matter.

        Available colors are :

            Name :   |  FG :  |  FG bright :  |  BG :  |  BG bright :
            ---------|--------|---------------|--------|-------------
            Black    |  k     |  K            |  _k    |  _K
            Red      |  r     |  R            |  _r    |  _R
            Green    |  g     |  G            |  _g    |  _G
            Yellow   |  y     |  Y            |  _y    |  _Y
            Blue     |  b     |  B            |  _b    |  _B
            Magenta  |  m     |  M            |  _m    |  _M
            Cyan     |  c     |  C            |  _c    |  _C
            White    |  w     |  W            |  _w    |  _W

        Color fg and bg combination :

            Depands on the system, in general shell will not allow
            combination with bad color contraste.

    Syntaxe examples (yellow fg, blue bg) :

        .\printMSG.exe "Hello" y _b

        .\printMSG.exe "Hello" _b y

        .\printMSG.exe "Hello" yellow _blue

        .\printMSG.exe "Hello" ylelwo _buel

        (Only '_' character as first char and color's first letter, do matter)