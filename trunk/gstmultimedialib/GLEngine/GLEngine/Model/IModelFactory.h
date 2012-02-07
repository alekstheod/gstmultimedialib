/*
 * IGLModelFactory.h
 *
 *  Created on: Apr 3, 2011
 *      Author: m1cRo
 */

#ifndef IGLMODELFACTORY_H_
#define IGLMODELFACTORY_H_
#include <Utilities/SmartPtr/SmartPtr.h>
#include <vector>
#include <GLEngine/Model/IModel.h>

namespace gl {

class IModelFactory {
public:
	IModelFactory();
	virtual ~IModelFactory();
	virtual utils::SmartPtr<IModel> getInstance(
			const std::vector<unsigned char>& modelData)=0;
};

}

#endif /* IGLMODELFACTORY_H_ */
