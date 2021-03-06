//
// Created by nikjan on 3/11/19.
//

#include <GL/glut.h>
#include <cmath>
#include "camera.hpp"

#define FIRST_VIEW (1)
#define SECOND_VIEW (2)
#define THIRD_VIEW (3)
#define FOURTH_VIEW (4)

Camera::Camera(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX,
               double upY, double upZ) : eyeX(eyeX), eyeY(eyeY), eyeZ(eyeZ), centerX(centerX), centerY(centerY),
                                         centerZ(centerZ), upX(upX), upY(upY), upZ(upZ) {}

extern float z_pos, y_pos, u;
void Camera::setLook(int id) {
    switch (id) {
        case FIRST_VIEW:
            setEyeX(0); setEyeY(0.6 + y_pos); setEyeZ(5 + z_pos);
            setCenterX(0); setCenterY(0); setCenterZ(z_pos-2);
            break;
        case SECOND_VIEW:
            setEyeX(0); setEyeY(2.2 +  y_pos); setEyeZ(z_pos + 3);
            setCenterX(0); setCenterY(0); setCenterZ(z_pos-2);
            break;
        case THIRD_VIEW:
            setEyeX(2); setEyeY(4); setEyeZ(5+z_pos);
            setCenterX(0); setCenterY(0); setCenterZ(z_pos + 1.5);
            break;
		case FOURTH_VIEW:
			setEyeX(0); setEyeY(1.6 + 3*sin(u)); setEyeZ(3+z_pos);
            setCenterX(0); setCenterY(0); setCenterZ(z_pos-2);
    }
    setUpX(0); setUpY(1); setUpZ(0);
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

void Camera::setEyeX(double eyeX) {
    Camera::eyeX = eyeX;
}

void Camera::setEyeY(double eyeY) {
    Camera::eyeY = eyeY;
}

void Camera::setEyeZ(double eyeZ) {
    Camera::eyeZ = eyeZ;
}

void Camera::setCenterX(double centerX) {
    Camera::centerX = centerX;
}

void Camera::setCenterY(double centerY) {
    Camera::centerY = centerY;
}

void Camera::setCenterZ(double centerZ) {
    Camera::centerZ = centerZ;
}

void Camera::setUpX(double upX) {
    Camera::upX = upX;
}

void Camera::setUpY(double upY) {
    Camera::upY = upY;
}

void Camera::setUpZ(double upZ) {
    Camera::upZ = upZ;
}
