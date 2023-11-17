#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <qapplication.h>
#include <qstring.h>

class Automata
{
  //init Source String
  private :
    QString InString; //input unicode
    QString tmpString; //Temporary String, not build completly yet.

    QList<QChar> jongList;

    //cho, jung, jong status, if activity is 1, otherwise 0. init 0;
    unsigned int cho; 
    unsigned int jung;
    unsigned int jong;
    unsigned int doublejong;

    //if setting is over, end will be 1. then cho,jung,jong had to be changed set 0;
    unsigned int end;

  public :
    //outString was overed to assem as the korean char.
    QString outString;
	int changed; //초성에서 중성으로 바뀌였음을 알려준다. 0 -> 1
  
  public :
	void SettingTable();
	unsigned short chosung[19];
	unsigned short jungsung[21];
	unsigned short jongsung[28];
    //init funtion; setting all status
    Automata();

    //InputString
    void InputString(const QString& str);

    //Over to compose
    void Reset();
  private :
	  int unreal;
	  ushort findjong(ushort arg);
	  ushort findjung(ushort arg);
	  ushort findcho(ushort arg);

    void Compare(); //compare to cho,jung,jong
    
    //composer as cho, jung, jong///////
    void OutStringAsCho(QChar cha);
    void OutStringAsJung(QChar cha);
    void OutStringAsJong(QChar cha);
    void OutStringAsDoubleJong(QChar cha);
    ////////////////////////////////////////


    //Exeption status if contiuing Jung and Jong inputed.
    void ExJungJong();
    ///////////////////////////////////////////////////////// not build, yet

};


#endif
