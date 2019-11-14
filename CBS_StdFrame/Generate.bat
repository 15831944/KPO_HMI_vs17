rem parameters of CBS_CodegenUsingEventLogUtility.vbs:
rem CBS_CodegenUsingEventLogUtility.vbs %CBSDIR%\example\CBS_StdAPI\StdEventLog_Example\cEventLogExampleGenTask.xls %CBSDIR%\example\CBS_StdAPI\StdEventLog_Example" True False True False
rem  1. parameter: location and name of excelfile with definition of eventlogmessages
rem  2. parameter: destinaton folder where the generated files should be stored
rem  3. parameter: should structures or classes be generated (True->structures) 
rem  4. parameter: should unicode be generated (e.g. when russian/chinese language is used
rem  5. parameter: should an xml-File containing destination codes be generated (only for structures)
rem  6. parameter: should static instances be generated (only for classes)

%CBSDIR%\bin\CBS_CodegenUsingEventLogUtility.vbs %X-Pact%\source\CBS_StdFrame\cCBS_StdEventLogFrame.xls %X-Pact%\source\CBS_StdFrame False False False False

pause