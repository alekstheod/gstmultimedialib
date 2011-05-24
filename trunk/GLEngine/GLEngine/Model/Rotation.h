/*
 * Rotation.h
 *
 *  Created on: May 24, 2011
 *      Author: m1cRo
 */

#ifndef ROTATION_H_
#define ROTATION_H_

namespace gl {

	namespace wavefront {

		class Rotation {
			private:
				float _angle;
				float _xAxis;
				float _yAxis;
				float _zAxis;

			public:
				Rotation();
				Rotation(float angle, float xAxis, float yAxis, float zAxis);
				float getAngle();
				float getAxisX();
				float getAxisY();
				float getAxisZ();
				virtual ~Rotation();
		};

	}

}

#endif /* ROTATION_H_ */
