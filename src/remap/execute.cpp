#include <stdio.h>
#include <stdlib.h>

#include "base.hpp"
#include "execute.hpp"


void
UltraRemapExecute::process(sgxString &resultPattern, const sgxString &source) const {

   FILE *fpipe;
   char line[256];

   if (!(fpipe = (FILE*)popen(source.c_str(),"r"))) {
	   resultPattern = "Server error : Problems with UltraRemapExecute pipe";
	   exit(1);
   }

   resultPattern = "";
   while (fgets(line, sizeof(line), fpipe)) {
	   resultPattern += line;
   }
   pclose(fpipe);
}

