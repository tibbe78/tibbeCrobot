@Echo off
cls

for /f "tokens=1" %%I IN (c:\crobots\tibbe.txt) DO set tibbe=%%I
copy c:\crobots\%tibbe%.c c:\crobots\tibbeCrobot.r

REM Uses the fnr.exe - Find And Replace Tool
REM https://findandreplace.codeplex.com/

REM Remove LineFeed, NewLine, TAB
fnr --cl --dir "c:\crobots" --fileMask "tibbeCrobot.r" --caseSensitive --useEscapeChars --useRegEx --silent --find "[\r\n\t]?" --replace ""

REM Find comments and remove them. /* Stuff with Lazy find */
fnr --cl --dir "c:\crobots" --fileMask "tibbeCrobot.r" --caseSensitive --useEscapeChars --useRegEx --silent --find "\/\*.*?\*\/" --replace ""

REM Find something with zero space or many, and alot of special caracters, and zero space or many, save the middle special character and use it in replace.
fnr --cl --dir "c:\crobots" --fileMask "tibbeCrobot.r" --caseSensitive --useEscapeChars --useRegEx --silent --find " *([+\-*\/=><;\(\)\{\}\[\]\,]) *" --replace "$1"

REM find my varible names that should be camelCase like thisVarible, one or more a-z, zero or many a-Z, one or many A-Z, zero or many a-Z. save each and mix them with the replace command
fnr --cl --dir "c:\crobots" --fileMask "tibbeCrobot.r" --caseSensitive --useEscapeChars --useRegEx --silent --find "([a-z]+)([a-zA-Z]*)([A-Z]+)([a-zA-Z]*)" --replace "$4$2$3$1"

REM find my functions that use PascalCase. kinda same as above.
fnr --cl --dir "c:\crobots" --fileMask "tibbeCrobot.r" --caseSensitive --useEscapeChars --useRegEx --silent --find "([A-Z]+)([a-z]*)([A-Z]*)([a-zA-Z]*)" --replace "$4$2$1$3"
