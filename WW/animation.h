#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

namespace GameSpace
{
	class Animation
	{
	public:
		enum class MoveState{	MS_STAY_LEFT, MS_STAY_RIGHT,	// �������� ������
								MS_MOVE_LEFT, MS_MOVE_RIGHT,	// �������� ��������
								MS_JUMP_LEFT, MS_JUMP_RIGHT,	// �������� ������
								MS_FALL_LEFT, MS_FALL_RIGHT		// �������� �������
							};
	private:
		// ���� ������� ��������� �� ���������
		sf::IntRect m_defaultFrame;
		// ������� ���������
		MoveState m_currentState;
		// ������� ����
		float m_currentFrame;
		// ���������� ��������� � ������ � ���������
		// ������� ��������� ������������� ���� �������� �������� � ���������� ��������
		std::map<MoveState, std::pair<float, std::vector<sf::IntRect>>> m_animations;
	public:
		/*
			@brief ������� ���������
			@param defaultFrame ����, ��������� �� ���������
			@param initState ��������� ��������� �������
		*/
		Animation(const sf::IntRect& defaultFrame, MoveState initState);
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
		void addFrame(MoveState state, const sf::IntRect& frame);
		/*
			@brief ���������� ��� ���� ��������
			@param state ������� ��������� � ������� ��������� ������
			@param delta ���� ������� �������� � ��������
		*/
		void animate(MoveState state, float delta);
		/*
			@brief ���������� ���� �������� ��� ���������
			@ret   � ������ ���������� �������� ��� ��������� ��������� ����, ����� ������
		*/
		sf::IntRect getFrame() const;
		/*
			@brief ���� �������� �� ���������
		*/
		const sf::IntRect& getDefaultFrame() const;
		/*
			@brief ���������� ������� ���������
		*/
		MoveState getState() const;
	};
}

#endif // !ANIMATION_H
