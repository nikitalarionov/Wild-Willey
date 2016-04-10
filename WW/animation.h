#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <vector>

namespace GameSpace
{
	class Animation
	{
	public:
		struct Frame
		{
			int m_x;
			int m_y;
			int m_width;
			int m_height;
			Frame(int x, int y, int width, int height) 
				: m_x(x), m_y(y), m_width(width), m_height(height)
			{}
		};
		enum class MoveState{	MS_STAY_LEFT, MS_STAY_RIGHT, 
								MS_MOVE_LEFT, MS_MOVE_RIGHT,
								MS_JUMP_LEFT, MS_JUMP_RIGHT, 
								MS_FALL_LEFT, MS_FALL_RIGHT };
	private:
		// ���� ������� ��������� �� ���������
		Frame m_defaultFrame;
		// ������� ���������
		MoveState m_currentState;
		// ������� ����
		float m_currentFrame;
		// ���������� ��������� � ������ � ���������
		// ������� ��������� ������������� ���� �������� �������� � ���������� ��������
		std::map<MoveState, std::pair<float, std::vector<Frame>>> m_animations;
	public:
		/*
			@brief ������� ���������
			@param defaultFrame ����, ��������� �� ���������
			@param initState ��������� ��������� �������
		*/
		Animation(const Frame& defaultFrame, MoveState initState);
		/*
			@brief ������ �������� �������� ��� ���������
			@param state ���������
			@param animationSpeed �������� ��������
		*/
		void setStateSpeed(MoveState state, float animationSpeed);
		/*
			@brief ��������� ���� � ����� ������������� ���������
			@param state ���������, � �������� ����� �������� ����
			@param frame ��� ����
		*/
		void addFrame(MoveState state, const Frame& frame);
		/*
			@brief ���������� ��� ���� ��������
			@param state ������� ��������� � ������� ��������� ������
			@param delta ���� ������� �������� � ��������
		*/
		void animate(MoveState state, float delta);
		/*
			@param	useDefault ������������ ��� �������� ���� �� ���������
			@brief	���������� ���� �������� ��� ���������
					� ������ ���������� �������� ��� ��������� ��������� ����
		*/
		Frame getFrame(bool useDefault = false) const;
		/*
			@brief ���������� ������� ���������
		*/
		MoveState getState() const;
	};
}

#endif // !ANIMATION_H
