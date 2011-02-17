/*
 * GstException.h
 *
 *  Created on: Jun 4, 2010
 *      Author: m1cro
 */

#ifndef GSTEXCEPTION_H_
#define GSTEXCEPTION_H_
#include <Utilities/AException.h>

class GstException : public utils::AException {
public:
    GstException(const std::string& message);
    virtual ~GstException()throw ();
};

#endif /* GSTEXCEPTION_H_ */
