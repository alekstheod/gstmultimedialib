/*
 * IGLModelFactory.h
 *
 *  Created on: Apr 3, 2011
 *      Author: m1cRo
 */

#ifndef IGLMODELFACTORY_H_
#define IGLMODELFACTORY_H_
#include <Utilities/Memory/SmartPtr/SharedPtr.h>
#include <vector>
#include <GLEngine/Model/IModel.h>
#include <istream>

namespace gl
{

class IModelFactory
{
private:
    virtual utils::SharedPtr<IModel> createModelImpl ( std::istream& modelData ) =0;

public:
    IModelFactory();
    utils::SharedPtr<IModel> createModel (std::istream& modelData );
    virtual ~IModelFactory();

};

}

#endif /* IGLMODELFACTORY_H_ */
