//
// Vivado(TM)
// rundef.js: a Vivado-generated Runs Script for WSH 5.1/5.6
// Copyright 1986-1999, 2001-2013 Xilinx, Inc. All Rights Reserved.
//

var WshShell = new ActiveXObject( "WScript.Shell" );
var ProcEnv = WshShell.Environment( "Process" );
var PathVal = ProcEnv("PATH");
if ( PathVal.length == 0 ) {
  PathVal = "E:/programming/tools/xilinx/SDK/2013.4/bin/nt;E:/programming/tools/xilinx/Vivado/2013.4/ids_lite/EDK/bin/nt;E:/programming/tools/xilinx/Vivado/2013.4/ids_lite/EDK/lib/nt;E:/programming/tools/xilinx/Vivado/2013.4/ids_lite/ISE/bin/nt;E:/programming/tools/xilinx/Vivado/2013.4/ids_lite/ISE/lib/nt;E:/programming/tools/xilinx/Vivado/2013.4/bin;";
} else {
  PathVal = "E:/programming/tools/xilinx/SDK/2013.4/bin/nt;E:/programming/tools/xilinx/Vivado/2013.4/ids_lite/EDK/bin/nt;E:/programming/tools/xilinx/Vivado/2013.4/ids_lite/EDK/lib/nt;E:/programming/tools/xilinx/Vivado/2013.4/ids_lite/ISE/bin/nt;E:/programming/tools/xilinx/Vivado/2013.4/ids_lite/ISE/lib/nt;E:/programming/tools/xilinx/Vivado/2013.4/bin;" + PathVal;
}

ProcEnv("PATH") = PathVal;

var RDScrFP = WScript.ScriptFullName;
var RDScrN = WScript.ScriptName;
var RDScrDir = RDScrFP.substr( 0, RDScrFP.length - RDScrN.length - 1 );
var ISEJScriptLib = RDScrDir + "/ISEWrap.js";
eval( EAInclude(ISEJScriptLib) );


ISEStep( "vivado",
         "-log system_withPL_wrapper.rds -m32 -mode batch -messageDb vivado.pb -source system_withPL_wrapper.tcl" );



function EAInclude( EAInclFilename ) {
  var EAFso = new ActiveXObject( "Scripting.FileSystemObject" );
  var EAInclFile = EAFso.OpenTextFile( EAInclFilename );
  var EAIFContents = EAInclFile.ReadAll();
  EAInclFile.Close();
  return EAIFContents;
}
