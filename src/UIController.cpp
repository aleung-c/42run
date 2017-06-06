#include "../includes/QDrun.hpp"

// --------------------------------------------------------------------	//
//																		//
//	Ui elements Controller												//
//																		//
// --------------------------------------------------------------------	//

UIController::UIController()
{

}

UIController::~UIController()
{

}

void		UIController::InitUI()
{
	// score fond
	ScoreFond = new GameUIObject("ScoreFond", "./ressources/ui_imgs/score_fond.bmp");
	ScoreFond->Transform.Position.x = 820.0;
	ScoreFond->Transform.Position.y = 650.0;

	// score label
	ScoreTextLabel = new GameTextObject("ScoreTextLabel", "Score:");
	ScoreTextLabel->Color = glm::vec3(1.0, 1.0, 1.0);
	ScoreTextLabel->Transform.Position.x = 950.0;
	ScoreTextLabel->Transform.Position.y = 670.0;

	// score value
	ScoreTextValue = new GameTextObject("ScoreTextValue", "00000");
	ScoreTextValue->Color = glm::vec3(1.0, 1.0, 1.0);
	ScoreTextValue->Transform.Position.x = 1100.0;
	ScoreTextValue->Transform.Position.y = 670.0;

	// life picture
	LifePic = new GameUIObject("LifePic", "./ressources/ui_imgs/life_pic.bmp");
	LifePic->Transform.Position.x = 80.0;
	LifePic->Transform.Position.y = 40.0;

	// life text value
	LifeValue = new GameTextObject("LifeValue", "0");
	LifeValue->Transform.Position.x = 150.0;
	LifeValue->Transform.Position.y = 50.0;

	// Coin picture
	CoinPic = new GameUIObject("CoinPic", "./ressources/ui_imgs/Coin_pic.bmp");
	CoinPic->Transform.Position.x = 200.0;
	CoinPic->Transform.Position.y = 40.0;

	// Coin text value
	CoinValue = new GameTextObject("CoinValue", "0");
	CoinValue->Transform.Position.x = 270.0;
	CoinValue->Transform.Position.y = 50.0;

}
