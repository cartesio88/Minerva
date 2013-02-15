/*
 * ParserOrej.h
 *
 *  Created on: 02/04/2011
 *      Author: cesar
 */
/*
 * This is a Re-Written version of the OreJ importer
 * made by César Mora for The-Minerva Project!
 *
 */

#ifndef PARSEROREJ_H_
#define PARSEROREJ_H_

#include <Kernel/Parsers/Parser.h>

class ParserOrej: public Singleton<ParserOrej>, public Parser {
	void _loadGeometry(const std::string& file, MAORenderable3DModel& model);
	void _loadTexture(const std::string& file, MAORenderable3DModel& model);
public:

	ParserOrej();
	virtual ~ParserOrej();
	void loadModel(const std::string& file, MAORenderable3DModel& model);



};

#endif /* OREJ_H_ */
