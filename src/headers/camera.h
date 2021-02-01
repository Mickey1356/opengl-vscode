#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

enum class CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

class Camera {
public:
	Camera(glm::vec3 position, float camera_speed, float camera_sensitivity);

	glm::mat4 get_view_matrix();
	glm::vec3 get_position();

	float get_camera_fov();

	void process_keyboard(CameraMovement dir, float delta_time);
	void process_mouse(float xoff, float yoff);
	void process_scroll(float yoff);

private:
	float pitch, yaw, fov, speed, sensitivity;
	glm::vec3 position, front, up;
	glm::mat4 view;
};