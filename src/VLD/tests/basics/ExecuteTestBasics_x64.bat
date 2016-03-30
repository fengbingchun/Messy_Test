@echo off

set Platform=.\x64
"%Platform%\Debug(Release)\test_basics"
"%Platform%\Debug(Release)\test_basics" invalid_argument 5
"%Platform%\Debug(Release)\test_basics" malloc 5
"%Platform%\Debug(Release)\test_basics" new 5
"%Platform%\Debug(Release)\test_basics" new_array 5
"%Platform%\Debug(Release)\test_basics" calloc 5
"%Platform%\Debug(Release)\test_basics" realloc 5
"%Platform%\Debug(Release)\test_basics" CoTaskMem 5

"%Platform%\Debug(Release)_StaticCrt\test_basics" 
"%Platform%\Debug(Release)_StaticCrt\test_basics" invalid_argument 5
"%Platform%\Debug(Release)_StaticCrt\test_basics" malloc 5
"%Platform%\Debug(Release)_StaticCrt\test_basics" new 5
"%Platform%\Debug(Release)_StaticCrt\test_basics" new_array 5
"%Platform%\Debug(Release)_StaticCrt\test_basics" calloc 5
"%Platform%\Debug(Release)_StaticCrt\test_basics" realloc 5
"%Platform%\Debug(Release)_StaticCrt\test_basics" CoTaskMem 5

pause

@echo on