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
#include <Kernel/Parsers/MSLParser.h>
#include <Kernel/Parsers/MSLPreprocessor.h>
#include <MPY/MPYWrapper.h>
#include <string>
#include <unistd.h>
#include <sstream>

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

string getAppFileName(char* appPath) {
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
	if (argc == 1) {
		// Execute the binary
		/* Parser and init CODE */
		try {

			/* Initializations */
			MPYWrapper::getInstance()->initPython();
			World::getInstance()->initWorld(640, 480);
			VideoFactory::getInstance()->addVideoSource("cam", 0);
			TrackingMethodFactory::getInstance(); /* Init tracking */

			/* Setting application directory */
			setAppDirectory(initialPath, argv[1]);

			/* Preprocessing! */
			MSLPreprocessor preprocessor;
			string appName = getAppFileName(argv[1]);
			stringstream finalFile;
			preprocessor.start(appName, finalFile);

			/* Parsing! */
			// Redirect cin
			streambuf* cinold = cin.rdbuf();
			cin.rdbuf(finalFile.rdbuf());

			Logger::getInstance()->out("Starts the source file parsing...");
			MSLParser parser;
			parser.yyparse();

			// Restoring cin
			cin.rdbuf(cinold);

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

	} else if (argc == 2) {
		//Generate the binary
		/* Setting application directory */
		setAppDirectory(initialPath, argv[1]);

		// Copies the binary

		// Parses the code looking for resources, and pack them!
		/* Preprocessing! */
		MSLPreprocessor preprocessor;
		string appName = getAppFileName(argv[1]);
		stringstream finalFile;
		preprocessor.start(appName, finalFile);

		/* Parsing! */
		// Redirect cin
		streambuf* cinold = cin.rdbuf();
		cin.rdbuf(finalFile.rdbuf());

		Logger::getInstance()->out("Starts the source file parsing...");

		MSLParser parser;
		parser.yyparse();

		/* Also, pack the source code! */
		ResourcesManager::getInstance()->pack();

		// Restoring cin
		cin.rdbuf(cinold);

	} else {
		cout << "ARGUMENTS ERROR!" << endl;
		cout << "\tUsage:" << endl;
		cout << "\tGenerate: minerva <source_file>" << endl << endl;
		cout << "Building Augmented Reality Apps has never been so easy!"
				<< endl;
		return -1;
	}

	return 0;
}
