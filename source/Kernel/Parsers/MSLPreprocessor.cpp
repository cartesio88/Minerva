/*
 * MSLPreprocessor.cpp
 *
 *  Created on: 09/02/2013
 *      Author: cesar
 */

#include <Kernel/Parsers/MSLPreprocessor.h>

using namespace std;

MSLPreprocessor::MSLPreprocessor() {
}

void MSLPreprocessor::start(const std::string& file, stringstream& finalFile){
  ifstream fileStream;
  fileStream.open(file.c_str());

  Logger::getInstance()->out("Preprocessing file: "+file);
  
  if (!fileStream.is_open()) {
    Logger::getInstance()->error(
				 "Application file not found!: " + file);
    throw "File not found exception: " + file;
  }
  
  char line[1024];
  char firstWord[1024];
  char path[1024];
  while(!fileStream.eof()){
    fileStream.getline(line, 1024);
    
    // Checking for import sentences
    sscanf(line,"%s %s", firstWord, path);
    if(string(firstWord) == "include"){
      firstWord[0] = '\0';

      string pathString(path);
      pathString = pathString.substr(1, pathString.length()-2); // Removing quotes
      start(pathString, finalFile);
    }else{
      finalFile << line<<endl;
    }
  }

  fileStream.close();
}

MSLPreprocessor::~MSLPreprocessor() {
}

