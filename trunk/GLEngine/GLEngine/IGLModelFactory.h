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
#include <GLEngine/IGLModel.h>

namespace gl {

	class IGLModelFactory {
		public:
			IGLModelFactory();
			virtual ~IGLModelFactory();
			virtual utils::SmartPtr<IGLModel> getInstance(const std::vector<unsigned char>& modelData)=0;
	};

}

#endif /* IGLMODELFACTORY_H_ */
