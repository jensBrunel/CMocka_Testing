# CorrectWindowsPaths - this module defines one macro
#
# CONVERT_CYGWIN_PATH( PATH )
#  This uses the command cygpath (provided by cygwin) to convert
#  unix-style paths into paths useable by cmake on windows

macro (CONVERT_CYGWIN_PATH placeholder path)
    EXECUTE_PROCESS(COMMAND cygpath.exe -w ${path}
      OUTPUT_VARIABLE newpath)
	  string(STRIP ${newpath} newpath)
	  message(newpath=${newpath})
	  set(retVal ${newpath}) 
	  message(retVal=${retVal} )
endmacro (CONVERT_CYGWIN_PATH)

