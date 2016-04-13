#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <stdexcept>
#include <vector>

#include <tinyxml.h>

namespace GameSpace
{
	/*
		@brief	��������� ������������ ����
				������ ������������ �� ����������������� ����� ����
				����� ���������� ������������ ��� ���������� ���������
				��� ��������� ����������
	*/
	class Config final
	{
	public:
		// @brief ��������� ��������� ������
		struct ScreenConfig
		{
			unsigned int m_width, m_height;
			std::string m_caption;
			bool m_isFullScreen;
			ScreenConfig(unsigned int width, unsigned int height, const std::string& caption, bool isFullScreen)
				: m_width(width), m_height(height), m_caption(caption), m_isFullScreen(isFullScreen)
			{}
			ScreenConfig() = default;
		};
		// @brief ��������� ��������� ����
		struct MenuConfig
		{
			std::string m_backgroundImage;
			std::string m_startImage;
			std::string m_exitImage;
			std::string m_sound;
			MenuConfig(const std::string& backgroundImage,
				const std::string& startImage,
				const std::string& exitImage,
				const std::string& sound)
				: m_backgroundImage(backgroundImage),
				m_startImage(startImage),
				m_exitImage(exitImage),
				m_sound(sound)
			{}
			MenuConfig() = default;
		};
		// ��������� ��������� �������
		struct LevelsConfig
		{
			std::string m_backgroundImage;
			int m_blockPerLine;
			int m_linePerScreen;
			std::string m_loadImage;
			std::string m_sound;
			struct Level
			{
				std::string m_image;
				std::string m_levelFile;
				std::string m_levelSound;
				bool m_isCompleted;
				Level(	const std::string& image, 
						const std::string& levelFile, 
						const std::string& levelSound, 
						bool isCompleted)
					:	m_image(image), 
						m_levelFile(levelFile), 
						m_levelSound(levelSound),
						m_isCompleted(isCompleted)
				{}
			};
			std::vector<Level> m_levels;
			LevelsConfig(	const std::string backgroundImage, int blockPerLine, int linePerScreen, 
							const std::string& loadImage, const std::string& sound)
				:	m_backgroundImage(backgroundImage), 
					m_blockPerLine(blockPerLine), 
					m_linePerScreen(linePerScreen),
					m_loadImage(loadImage),
					m_sound(sound)
			{}
			LevelsConfig() = default;
		};
		// ��������� ��������� �������������� �������
		struct InfoConfig
		{
			std::string m_backgroundImage;
			std::string m_image;
			std::string m_sound;
			InfoConfig(	const std::string& backgroundImage, 
						const std::string& image, 
						const std::string& sound)
				:	m_backgroundImage(backgroundImage), 
					m_image(image),
					m_sound(sound)
			{}
			InfoConfig() = default;
		};
		/*
			@brief ��������� ���� ������������
			@param config ���� � ����� ������������
		*/
		Config(const char* config);
		/*
			@brief ������ ��������� ������
			@ret   ��������� ������
		*/
		const ScreenConfig& getScreenConfig() const
		{ return m_screenConfig; }
		/*
			@brief ������ ��������� ����
			@ret   ��������� ����
		*/
		const MenuConfig& getMenuConfig() const
		{ return m_menuConfig; }
		/*
			@brief ��������� ��������� �������
			@ret   ��������� �������
		*/
		const LevelsConfig& getLevelsConfig() const
		{ return m_levelsConfig; }
		/*
			@brief ��������� ���� ��������
		*/
		const InfoConfig& getWinConfig() const
		{ return m_winConfig; }
		/*
			@brief ��������� ���� ���������
		*/
		const InfoConfig& getFailConfig() const
		{ return m_failConfig; }
		/*
		@brief �������� ������� ��� ����������
		*/
		void markLevelAsCompleted(const std::string& levelFile);
	private:
		std::string m_configName;

		ScreenConfig m_screenConfig; // ��������� ����
		MenuConfig m_menuConfig; // ��������� ������ ����
		LevelsConfig m_levelsConfig; // ��������� ������ ������ ������
		InfoConfig m_winConfig; // ��������� ������ ��������
		InfoConfig m_failConfig; // ��������� ������ ���������
		
		void readScreenConfig(TiXmlElement* rootElement);
		void readMenuConfig(TiXmlElement* rootElement);
		void readLevelsConfig(TiXmlElement* rootElement);
		void readInfoConfig(TiXmlElement* rootElement, const std::string& info, InfoConfig& result);
		/*
			@brief ������ �������� �� XML
			@param element ������� �� �������� ������� ������
			@param name ��� ��������� ��� ������
			@ret   ��������� ��������
		*/
		std::string readValFromXml(TiXmlElement* element, const std::string& name) const;
	};
}

#endif // !CONFIG_H
