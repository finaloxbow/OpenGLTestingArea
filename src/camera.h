#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>



//default values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENS = 0.1f;
const float ZOOM = 45.0f;

class camera {
public:

	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;
	float m_movementSpeed;
	float m_mouseSens;
	float m_zoom;

	enum CAMERA_MOVEMENT {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
	};

	camera(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = YAW,
		float pitch = PITCH
	);

	camera(
		float posX,
		float posY,
		float posZ,
		float upX,
		float upY,
		float upZ,
		float yaw,
		float pitch
	);

	glm::mat4 get_view_matrix();

	void process_keyboard(CAMERA_MOVEMENT direction, float deltaTime);

	void process_mouse_movement(float xoffset, float yoffset, GLboolean constraintPitch = true);

	void process_mouse_scroll(float yoffset);

private:

	void update_camera_vectors();
};