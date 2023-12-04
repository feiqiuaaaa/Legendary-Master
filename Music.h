#pragma once
class Music
{
public:
	void playFightMusic();
	void playIniMusic();
	void playFailMusic();
	void playSuccessMusic();
	void closeMusic();
};

void Music::playFightMusic()
{
	mciSendString(_T("open fightingMusic.mp3 alias bkmusic"), NULL, 0, NULL);//≤•∑≈“Ù¿÷
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//—≠ª∑≤•∑≈
}

void Music::playIniMusic()
{
	mciSendString(_T("open chooseMusic.mp3 alias bkmusic"), NULL, 0, NULL);//≤•∑≈“Ù¿÷
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//—≠ª∑≤•∑≈
}

void Music::playFailMusic()
{
	mciSendString(_T("open failingMusic.mp3 alias bkmusic"), NULL, 0, NULL);//≤•∑≈“Ù¿÷
	//mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//—≠ª∑≤•∑≈
}

void Music::playSuccessMusic()
{
	mciSendString(_T("open successMusic.mp3 alias bkmusic"), NULL, 0, NULL);//≤•∑≈“Ù¿÷
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//—≠ª∑≤•∑≈
}

void Music::closeMusic()
{
	mciSendString(_T("close bkmusic"), NULL, 0, NULL);
}