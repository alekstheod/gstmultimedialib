/*
 * IGLModelFactory.cpp
 *
 *  Created on: Apr 3, 2011
 *      Author: m1cRo
 */

#include "IModelFactory.h"

namespace gl
{

IModelFactory::IModelFactory()
{
    // TODO Auto-generated constructor stub

}

IModelFactory::~IModelFactory()
{
    // TODO Auto-generated destructor stub
}

utils::SharedPtr<Model> IModelFactory::createModel ( std::istream& modelData )
{
  return createModelImpl(modelData);
}

}
