/*
 * main.cpp
 *
 *  Created on: 19/02/2011
 *      Author: cesar
 */
#include <Controllers/InputEventController.h>
#include <Controllers/GameLogicController.h>
#include <Controllers/PhysicsController.h>
#include <Factories/VideoFactory.h>
#include <Factories/TrackingMethodFactory.h>
#include <Kernel/VideoSource.h>
#include <Kernel/EndController.h>
#include <Kernel/World.h>
#include <Kernel/Logger.h>
#include <Kernel/MSLParser.h>
#include <Kernel/MSLPreprocessor.h>
#include <MPY/MPYWrapper.h>
#include <string>
#include <unistd.h>
#include <sstream>

#ifdef WIN32
#define MINERVA_HOME "C:\\Minerva"
#else
#define MINERVA_HOME "/usr/share/minerva/"
#endif

using namespace std;

//Global variable :S
char initialPath[255];

void showCurrentDirectory() {
	char c[255];
#ifdef WIN32
	GetCurrentDirectory(255,c);
#else
	getcwd(c, 255);
#endif
	cout << "Current directory: " << c << endl;
}

void saveInitialDirectory() {
#ifdef WIN32
	GetCurrentDirectory(255,initialPath);
#else
	getcwd(initialPath, 255);
#endif
}

void setAppDirectory(char* initialPath, char* appPath) {
	string sAppPath(appPath);
#ifdef WIN32
	int p = sAppPath.rfind('\\');
#else
	int p = sAppPath.rfind('/');
#endif

	string sAppPath2 = sAppPath.substr(0, p);

#ifdef WIN32
	SetCurrentDirectory(initialPath);
	SetCurrentDirectory(sAppPath2.c_str());
#else
	chdir(initialPath);
	chdir(sAppPath2.c_str());
#endif
}

void setMinervaHomeDirectory() {
#ifdef WIN32
	SetCurrentDirectory(MINERVA_HOME);
#else
	chdir(MINERVA_HOME);
#endif
}

string getAppName(char* appPath) {
	string sAppPath(appPath);
	int p = sAppPath.rfind('/');
	string sAppName = sAppPath.substr(p + 1);
	return sAppName;
}

int main(int argc, char* argv[]) {
	cout << "~~~-------~~~" << endl;
	cout << "~~ Minerva! ~" << endl;
	cout << "~~~-------~~~" << endl;

	/* Saving the initial path */
	saveInitialDirectory();

	/* Checking arguments */
	if (argc != 2) {
		cout << "ARGUMENTS ERROR!" << endl;
		cout << "\tUsage: minerva <source_file>" << endl << endl;
		cout << "Building Augmented Reality Apps has never been so easy!"
				<< endl;
		return -1;
	}

	/* Parser and init CODE */
	try {

		/* Initializations */
		setMinervaHomeDirectory();

		MPYWrapper::getInstance()->initPython();
		World::getInstance()->initWorld(640, 480);
		VideoFactory::getInstance()->addVideoSource("cam", 0);
		TrackingMethodFactory::getInstance(); /* Init tracking */

		/* Setting application directory */
		setAppDirectory(initialPath, argv[1]);
		
		/* Preprocessing! */
		MSLPreprocessor preprocessor;
		string appName = getAppName(argv[1]);		
		stringstream finalFile;
		preprocessor.start(appName, finalFile);

		/* Parsing! */
		// Redirect cin
		streambuf* cinold= cin.rdbuf();
		cin.rdbuf(finalFile.rdbuf());

		Logger::getInstance()->out("Starts the source file parsing...");
		MSLParser parser;
		parser.yyparse();

		// Restoring cin
		cin.rdbuf(cinold);

		setMinervaHomeDirectory();

	} catch (string e) {
		cout << "Exception: " << e << endl;
		EndController::getInstance()->end();
	} catch (const char* e) {
		cout << "Exception: " << e << endl;
		EndController::getInstance()->end();
	}

	//Main loop
	while (EndController::getInstance()->isRunning()) {
		//Grab a frame from the camera!
		VideoFactory::getInstance()->getMainCamera().grabFrame();

		//Tracking method!
		TrackingMethodFactory::getInstance()->pollMethods();

		//Physics
		PhysicsController::getInstance()->pollPhysics();

		//Poll Events
		InputEventController::getInstance()->pollEvents();

		//Game Logic
		GameLogicController::getInstance()->pollLogic();

		//Draw
		World::getInstance()->drawWorld();
	}

	//Freeing resources
	World::getInstance()->destroy();
	GameLogicController::getInstance()->destroy();
	TrackingMethodFactory::getInstance()->destroy();
	PhysicsController::getInstance()->destroy();
	InputEventController::getInstance()->destroy();
	VideoFactory::getInstance()->destroy();

	return 0;
}
