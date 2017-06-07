#ifndef UICONTROLLER_HPP
# define UICONTROLLER_HPP

# include "QDrun.hpp"

class UIController
{
	public:
		UIController();
		~UIController();

		GameUIObject			*ScoreFond;
		GameTextObject			*ScoreTextLabel;
		GameTextObject			*ScoreTextValue;

		GameUIObject			*LifePic;
		GameTextObject			*LifeValue;

		GameUIObject			*CoinPic;
		GameTextObject			*CoinValue;

		void					InitUI();
		void					HideUI();
		void					ShowUI();

		void					UpdateUIValues(t_GameDatas &gameDatas);
};

#endif