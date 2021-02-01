#include "camera.h"

Camera::Camera(glm::vec3 ipos, float camera_speed, float camera_sensitivity) {
    position = ipos;
    speed = camera_speed;
    sensitivity = camera_sensitivity;

    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    fov = 45.0f;
    pitch = 0.0f;
    yaw = -90.0f;
}

glm::mat4 Camera::get_view_matrix() {
    return glm::lookAt(position, position + front, up);
}

float Camera::get_camera_fov() {
    return fov;
}

glm::vec3 Camera::get_position() {
    return position;
}

void Camera::process_keyboard(CameraMovement dir, float delta_time) {
    switch (dir) {
        case CameraMovement::FORWARD:
            position += front * speed * delta_time;
            break;
        case CameraMovement::BACKWARD:
            position -= front * speed * delta_time;
            break;
        case CameraMovement::LEFT:
            position -= glm::normalize(glm::cross(front, up)) * speed * delta_time;
            break;
        case CameraMovement::RIGHT:
            position += glm::normalize(glm::cross(front, up)) * speed * delta_time;
            break;
        case CameraMovement::UP:
            position += up * speed * delta_time;
            break;
        case CameraMovement::DOWN:
            position -= up * speed * delta_time;
            break;
    }
}

void Camera::process_mouse(float xoff, float yoff) {
    xoff *= sensitivity;
    yoff *= sensitivity;

    yaw += xoff;
    pitch += yoff;

    pitch = std::min(pitch, 89.0f);
    pitch = std::max(pitch, -89.0f);

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
}

void Camera::process_scroll(float yoff) {
    fov -= yoff;
    fov = std::min(fov, 45.0f);
    fov = std::max(fov, 1.0f);
}
