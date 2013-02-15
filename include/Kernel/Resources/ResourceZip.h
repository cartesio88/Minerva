/*
 * ResourceZip.h
 *
 *  Created on: 12/02/2013
 *      Author: cesar
 */

#ifndef RESOURCEZIP_H_
#define RESOURCEZIP_H_

#include <Kernel/Resources/Resource.h>

class ResourceZip: public Resource {

	zip* _dataFile;


	void load();

public:
	ResourceZip(zip* dataFile, std::string uri);

	virtual ~ResourceZip();
};

#endif /* RESOURCEZIP_H_ */
