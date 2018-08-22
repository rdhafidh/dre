set idlpath=D:\masteraplikasi\transferh11nov\flatbuffergit\msvcinstall
set typebuild=release
%idlpath%\%typebuild%\bin\flatc.exe --scoped-enums --gen-mutable --cpp -o . data.fbs  
