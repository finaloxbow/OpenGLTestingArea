#include "camera.h"

camera::camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
: m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(SPEED), m_mouseSens(SENS), m_zoom(ZOOM)
{
	m_position = position;
	m_worldUp = up;
	m_yaw = yaw;
	m_pitch = pitch;
	update_camera_vectors();
}

camera::camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	m_position = glm::vec3(posX, posY, posZ);
	m_worldUp = glm::vec3(upX, upY, upZ);
	m_yaw = yaw;
	m_pitch = pitch;
	update_camera_vectors();
}

glm::mat4 camera::get_view_matrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void camera::process_keyboard(CAMERA_MOVEMENT direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;
	if (direction == FORWARD)
		m_position += m_front * velocity;
	if (direction == BACKWARD)
		m_position -= m_front * velocity;
	if (direction == LEFT)
		m_position -= m_right * velocity;
	if (direction == RIGHT)
		m_position += m_right * velocity;

}

void camera::process_mouse_movement(float xoffset, float yoffset, GLboolean constraintPitch)
{
	xoffset *= m_mouseSens;
	yoffset *= m_mouseSens;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (constraintPitch) {
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	update_camera_vectors();
}

void camera::process_mouse_scroll(float yoffset)
{
	m_zoom -= yoffset;
	if (m_zoom < 1.0f)
		m_zoom = 1.0f;
	if (m_zoom > 45.0f)
		m_zoom = 45.0f;
}

void camera::update_camera_vectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}