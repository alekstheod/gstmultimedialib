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
#include <GLEngine/Model/Model.h>
#include <istream>

namespace gl
{

class IModelFactory
{
private:
    virtual utils::SharedPtr<Model> createModelImpl ( std::istream& modelData ) =0;

public:
    IModelFactory();
    utils::SharedPtr<Model> createModel (std::istream& modelData );
    virtual ~IModelFactory();

};

}

#endif /* IGLMODELFACTORY_H_ */
