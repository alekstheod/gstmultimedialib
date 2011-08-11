/*
 * GstObject.h
 *
 *  Created on: Jul 22, 2011
 *      Author: alekstheod
 */

#ifndef GSTOBJECT_H_
#define GSTOBJECT_H_

namespace multimedia {

	class GstObject {
		public:
			static const bool CONST_GST_INITIALIZED;

		private:
			static bool initGstreamer();

		public:
			GstObject();
			virtual ~GstObject();
	};

}

#endif /* GSTOBJECT_H_ */
