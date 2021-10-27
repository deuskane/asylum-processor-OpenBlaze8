#include <cstring>
//---------------------------------------------------------------------------- 
// picoasm
//
// Stripped out the GUI from kpicosim to create a command-line Picoblaze
// assembler and VHDL/verilog file generator.
//
//---------------------------------------------------------------------------- 

//---------------------------------------------------------------------------- 
// History - most recent first 
/*****************************************************************************
02/10/2021 V 1.0
* Add multi dialect
* Add verbose option
* Add generic ROM generation
/*****************************************************************************
02/02/2007 V 0.2
* Added assembler listing file = src file name with .log ext.
* By default look for template file in source dir.
* Suppress symbol table print to cout (in CAssembler::buildSymbolTable()). 
* Added bVHDL parm to CAssembler::exportVHDL() to process either VHDL or 
  verilog. 
* George found problem with instrOR_SX_SY in CAssembler::addInstruction().
  Fixed it here. 
/*****************************************************************************
02/01/2007 V 0.1
Initial version based on kpicosim version 0.1.
* Uses cassembler, cpicoblaze, and cinstruction.cpp/.h files and
  types.h, hexcodes.h
* Modifications:
  - In any of these, I changed "\r\n" to use endl. This makes the endlines
    in cout platform independent.
  - In cassembler, I removed references to the QT m_messageList.
  - My code is in main.cpp        
* Just does VHDL output, but planning for adding verilog.
*****************************************************************************/
//---------------------------------------------------------------------------- 

#include "cassembler.h"
#include "cpicoblaze.h"
#include "cinstruction.h"

#include <string>
#include <iostream>
#include <stdio.h>      // printf
#include <unistd.h>     // getopt
#include <libgen.h>     // dirname, basename
#include <strings.h>    // strcasecmp

#define LA_PICOASM_DEF_TPL      "ROM_form.v"      // default template file
#define LA_PICOASM_VERILOG_EXT  ".v"              // verilog file ext
#define LA_PICOASM_VHDL_EXT     ".vhd"            // VHDL file ext
#define LA_PICOASM_LISTING_EXT  ".log"            // assembler listing ext 
#define LA_PICOASM_HEX_EXT      ".hex"            // assembler hex ext 

using namespace std;

static const char version[] = "1.0";
static const char AppDescription[] = "Picoblaze Assembler based on kpicosim";

CPicoBlaze *m_picoBlaze;
CAssembler *m_assembler; 

// function prototypes ------------------------- 
bool printListing(string strFileName, string outFileName);
bool printHex(string strFileName, string outFileName);
void usage(string strName);

//---------------------------------------------------------------------------- 
// usage
// Print app usage
//
// parms: strName: app name
//
//  ret: none
//---------------------------------------------------------------------------- 
void usage(string strName){

  printf("%s Version %s - %s\n", strName.c_str(), version, AppDescription);
  printf("USAGE:\n");
  printf(" -i <input file>      Picoblaze source file\n");
  printf(" [-t <template file>] verilog/VHDL template file.\n" 
         "                      Default = %s\n"
         "                      Extension determines verilog/VHDL processing\n"
         "                      \"%s\" = verilog, otherwise VHDL\n", 
         LA_PICOASM_DEF_TPL, LA_PICOASM_VERILOG_EXT);
  printf(" [-m <module name>]   Verilog module or VHDL entity name.\n"
         "                      Default = input file base name\n");  
  printf(" [-o <filename>]      Output filename.\n"
         "                      Default = input file base name\n");
  printf(" [-d <directory>]     Output file directory.\n"
         "                      Default = input file directory\n");
  printf(" [-a <asm>]           Assembler dialect (kcpsm3 or pblazeide)\n"
         "                      Default = kcpsm3\n");
}

int main(int argc, char **argv)
{

  string strSrcFile;
  string strTplFile;
  string strOutputDir;
  string strFileName;
  string strEntityName;
  string hexOutFile;
  string lstOutFile;
  string dialect = "kcpsm3";
  bool   verbose = false;
  string strTemp;
  int iCompareLen;
  const string strVerilogExt = LA_PICOASM_VERILOG_EXT;

  const char optstring[] = "i:t:d:m:o:a:v";
  bool bOptErr = false;
  bool bVHDL = true;
  int optch;

  char *cpTemp;
  char *cpBase;
  char *cpExt;

  bool bRet; 
  int iRet = 0;

  while ((optch = getopt(argc, argv, optstring)) != -1){
    switch (optch)
      {
      case 'i': // input source file
        strSrcFile = optarg;
        break;

      case 't': // input template file
        strTplFile = optarg;
        break;

      case 'f': // filename
        strFileName = optarg;
        break;

      case 'm': // entity or module name
        strEntityName = optarg;
        break;

      case 'd': // output directory
        strOutputDir = optarg;
        break;

      case 'o':
        strFileName = optarg;
        break;

      case 'a': // dialect
        dialect = optarg;
        break;

      case 'v': // verbose
	verbose = true;
	break;
	
      default:
        cout << "ERR: Unknown command line option" << endl; 
        bOptErr = true;
        break;

      } // switch
  } // while

  // check cmd line options
  if (verbose)
    cout << "[DEBUG  ] Check command line options" << endl;
  
  if (strSrcFile.empty()){
    cout << "ERR: Input source file missing." << endl; 
    usage(basename(argv[0]));
    return (-1);
  }
  
  if (bOptErr){
    usage(basename(argv[0]));
    return (-1);
  }

  if ((dialect != "kcpsm3"   ) &&
      (dialect != "pblazeide"))
      {
	cout << "ERR: Invalid dialect : " << dialect << endl; 
	usage(basename(argv[0]));
	return (-1);
      }
  
  // build optional parms if needed
  if (strOutputDir.empty()){
    cpTemp = strdup(strSrcFile.c_str());
    strOutputDir = dirname(cpTemp);
    free(cpTemp);
  }
  
  if (strFileName.empty()){
    // build file name from source file name with no path or extension 
    cpTemp = strdup(strSrcFile.c_str());
    cpBase = basename(cpTemp);
    cpExt = strrchr(cpBase, '.');
    if (cpExt != NULL){
      *cpExt = '\0';
    }
    strFileName = cpBase;
    free(cpTemp);
  }

  if (strEntityName.empty()){
    // build entity name from source file name with no path or extension 
    cpTemp = strdup(strSrcFile.c_str());
    cpBase = basename(cpTemp);
    cpExt = strrchr(cpBase, '.');
    if (cpExt != NULL){
      *cpExt = '\0';
    }
    strEntityName = cpBase;
    free(cpTemp);
  }

  if (strTplFile.empty()){
    // build template file from source file dir + default name
    cpTemp = strdup(strSrcFile.c_str());
    cpBase = dirname(cpTemp);
    strTplFile = cpBase;
    strTplFile += "/";
    strTplFile += LA_PICOASM_DEF_TPL;
    free(cpTemp);
  }

  
  hexOutFile = strOutputDir + '/' + strFileName + LA_PICOASM_HEX_EXT;
  lstOutFile = strOutputDir + '/' + strFileName + LA_PICOASM_LISTING_EXT;

  // determine VHDL or verilog by looking for verilog file extension
  // on template file.
  iCompareLen = strVerilogExt.size();
  if ((strTplFile.size()) > iCompareLen){
    strTemp = strTplFile.substr(strTplFile.size() - iCompareLen, iCompareLen); 
    if (strcasecmp(strTemp.c_str(), strVerilogExt.c_str()) == 0){
      bVHDL = false;   // its verilog
    }
  }

  if (verbose)
  cout
    << "[DEBUG  ] Input Source File : " << strSrcFile    << endl
    << "[DEBUG  ] Dialect           : " << dialect       << endl
    << "[DEBUG  ] Output Directory  : " << strOutputDir  << endl
    << "[DEBUG  ] Hex File          : " << hexOutFile    << endl
    << "[DEBUG  ] Listing File      : " << lstOutFile    << endl
    << "[DEBUG  ] Entity Name       : " << strEntityName << endl
    << "[DEBUG  ] Template File     : " << strTplFile    << endl
    << "[DEBUG  ] Generate VHDL     : " << bVHDL         << endl
    ;  

  m_picoBlaze = new CPicoBlaze();
  m_assembler = new CAssembler();
  m_assembler->verbose = verbose;
  m_assembler->setDialect(dialect);
  m_assembler->setCode(m_picoBlaze->code);
  m_assembler->setFilename(strSrcFile);
  if (m_assembler->assemble() == true){
    if (verbose) cout << "[DEBUG  ] Print" << endl;
    m_picoBlaze->code->Print();

    if (verbose) cout << "[DEBUG  ] Print Hex" << endl;
    printHex(strSrcFile, hexOutFile);

    if (verbose) cout << "[DEBUG  ] Print Listing" << endl;
    printListing(strSrcFile, lstOutFile);

    if (m_assembler->exportVHDL(strTplFile, 
                                strOutputDir, 
				strFileName,
                                strEntityName,
                                bVHDL) == true){
      if (bVHDL){
        cout << "Generated VHDL entity file " 
             << strOutputDir << "/" << strFileName 
             << LA_PICOASM_VHDL_EXT << endl;
      } else {
        cout << "Generated verilog module file " 
             << strOutputDir << "/" << strFileName 
             << LA_PICOASM_VERILOG_EXT << endl;
      }
    } else {
      if (bVHDL){
        cout << "ERR: VHDL entity file not generated" << endl;
      } else {
        cout << "ERR: Verilog module file not generated" << endl;
      }
      iRet = -1;
    }
  
  } else {
    iRet = -1;
  }

  delete m_assembler;
  delete m_picoBlaze;

  return(iRet);

}

//---------------------------------------------------------------------------- 
// printListing
// Print assembler listing
//
// parms: strFileName: picoblaze source file name
//
//  ret: True: good print   False: problem
//---------------------------------------------------------------------------- 
bool printListing(string strFileName, string outFileName){

  FILE *f ;

  f = fopen( strFileName.c_str(), "r" ) ;

  if ( f == NULL ) {
    cout << "ERR: Unable to load file '" << strFileName << "'" << endl;
    return (false);
  }

  char *cpTemp;
  char *cpExt;
  string strAsmListing;
  FILE *fListing;

  // build assembler listing file name from source file name 
  if (outFileName.empty()) {
     cpTemp = strdup(outFileName.c_str());
     cpExt = strrchr(cpTemp, '.');
     if (cpExt != NULL){
       *cpExt = '\0';
     }
     strAsmListing = cpTemp;
     strAsmListing += LA_PICOASM_LISTING_EXT;
     free(cpTemp);
  } else {
     strAsmListing = outFileName;
  }

  fListing = fopen(strAsmListing.c_str(), "w") ;

  if ( fListing == NULL ) {
    cout << "ERR: Unable to open assembler listing file '" 
         << strAsmListing << "'" << endl;
    fclose(f);
    return (false);
  }

  char buf[ 256 ] ;
  int linenr = 0 ;
  int iCodeLine = 0;
  uint16_t uiAddr = 0;
  uint32_t uiHexCode = 0;

  CInstruction *instr = m_picoBlaze->code->getInstruction( uiAddr ) ;

  if (instr == NULL){
    iCodeLine = 999999;  // no code in file - use a giant line number
  } else {
    iCodeLine = instr->getSourceLine();
    uiHexCode = instr->getHexCode();
  }

  fprintf(fListing, "\n");
  fprintf(fListing, "%s  Version %s\n", AppDescription, version);   // heading
  fprintf(fListing, "Source File: %s\n", strFileName.c_str());
  fprintf(fListing, "\n");
  fprintf(fListing, "Line  Addr Instr  Source Code\n");   
  //                "llll  AAA  HHHHH  SSSSSSSSS...", 

  while( fgets( buf, sizeof( buf ), f ) ) {
    // if this is the next code line 
    if (linenr == iCodeLine){
      fprintf(fListing, 
              "%4d  %03x  %05x  %s", 
              linenr + 1, uiAddr, uiHexCode, buf);  // one-base line number
      // get next instruction
      uiAddr++;
      instr = m_picoBlaze->code->getInstruction( uiAddr ) ;
      if (instr == NULL){
        // no more code in file
        iCodeLine = 999999;  // no code in file - use a giant line number
      } else {
        iCodeLine = instr->getSourceLine();
        uiHexCode = instr->getHexCode();
      }
    } else {
      fprintf(fListing, "%4d              %s", 
              linenr + 1, buf);                    // one-based line number
    }
    linenr++;
  }

  fclose (f);
  fclose(fListing);
                
  return (true);

}



bool printHex(string strFileName, string outFileName){

  FILE *f ;

  f = fopen( strFileName.c_str(), "r" ) ;

  if ( f == NULL ) {
    cout << "ERR: Unable to load file '" << strFileName << "'" << endl;
    return (false);
  }

  char *cpTemp;
  char *cpExt;
  string strAsmListing;
  FILE *fListing;

  // build assembler listing file name from source file name 
  if (outFileName.empty()) {
     cpTemp = strdup(outFileName.c_str());
     cpExt = strrchr(cpTemp, '.');
     if (cpExt != NULL){
       *cpExt = '\0';
     }
     strAsmListing = cpTemp;
     strAsmListing += LA_PICOASM_HEX_EXT;
     free(cpTemp);
  } else {
     strAsmListing = outFileName;
  }
  fListing = fopen(strAsmListing.c_str(), "wb") ;

  if ( fListing == NULL ) {
    cout << "ERR: Unable to open assembler hex file '" 
         << strAsmListing << "'" << endl;
    fclose(f);
    return (false);
  }

  char buf[ 256 ] ;
  int linenr = 0 ;
  int iCodeLine = 0;
  uint16_t uiAddr = 0;
  uint32_t uiHexCode = 0;

  CInstruction *instr = m_picoBlaze->code->getInstruction( uiAddr ) ;

  if (instr == NULL){
    iCodeLine = 999999;  // no code in file - use a giant line number
  } else {
    iCodeLine = instr->getSourceLine();
    uiHexCode = instr->getHexCode();
  }

  int lines=0;
  while( fgets( buf, sizeof( buf ), f ) ) {
    // if this is the next code line 
    if (linenr == iCodeLine){
       fprintf(fListing, "%05x\r\n", uiHexCode);  // one-base line number
       lines++;
       // get next instruction
       uiAddr++;
       instr = m_picoBlaze->code->getInstruction( uiAddr ) ;
       if (instr == NULL){
        // no more code in file
        iCodeLine = 999999;  // no code in file - use a giant line number
      } else {
        iCodeLine = instr->getSourceLine();
        uiHexCode = instr->getHexCode();
      }
    }
    linenr++;
  }

  while (lines < 1024) {
       fprintf(fListing, "%05x\r\n", 0);  // one-base line number
       lines++;
  }
          
  fclose (f);
  fclose(fListing);
                
  return (true);

}
